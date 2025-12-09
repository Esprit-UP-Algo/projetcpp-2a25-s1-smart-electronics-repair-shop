#include "logindialog.h"
#include "ui_logindialog.h"
#include <QCryptographicHash>
#include <QDebug>
#include <QSqlRecord>
#include <QTimer>
#include <QRegularExpression>
#include <QThread> // ADDED for QThread::msleep

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),
    authenticated(false),
    cardScanningActive(false),
    cardCheckTimer(nullptr)
{
    ui->setupUi(this);

    // Initialize currentUser
    currentUser.id = 0;
    currentUser.nom = "";
    currentUser.prenom = "";
    currentUser.poste = "";
    currentUser.email = "";
    currentUser.card_uid = "";

    // Connect signals and slots
    connect(ui->pushButtonLogin, &QPushButton::clicked, this, &LoginDialog::on_pushButtonLogin_clicked);
    connect(ui->pushButtonForgot, &QPushButton::clicked, this, &LoginDialog::on_pushButtonForgot_clicked);
    connect(ui->pushButtonReset, &QPushButton::clicked, this, &LoginDialog::on_pushButtonReset_clicked);
    connect(ui->pushButtonBack, &QPushButton::clicked, this, &LoginDialog::on_pushButtonBack_clicked);

    // Setup Arduino for card reading
    QTimer::singleShot(500, this, [this]() {
        reconnectArduino(); // CHANGED from setupArduino
    });

    // Set focus to employee ID field
    ui->lineEditID->setFocus();
}

LoginDialog::~LoginDialog()
{
    // Stop the timer first
    if (cardCheckTimer && cardCheckTimer->isActive()) {
        cardCheckTimer->stop();
    }

    // Stop scanning
    cardScanningActive = false;

    // Send a reset command to Arduino before closing
    if (arduino.getserial() && arduino.getserial()->isOpen()) {
        arduino.write_to_arduino(QByteArray("RESET\n"));
        QThread::msleep(100);
        arduino.close_arduino();
    }

    delete ui;
}

void LoginDialog::reconnectArduino()
{
    // Close any existing connection first
    if (arduino.getserial() && arduino.getserial()->isOpen()) {
        arduino.close_arduino();
    }

    // Clear any pending data
    QThread::msleep(500);

    // Try to reconnect
    if (setupArduino()) {
        qDebug() << "RFID Card Reader: Reconnected successfully";
        startCardScanning();
    } else {
        qDebug() << "RFID Card Reader: Reconnection failed - manual login only";
    }
}

bool LoginDialog::setupArduino()
{
    int connectionResult = arduino.connect_arduino();
    if (connectionResult == 0) {
        qDebug() << "RFID Card Reader: Connected on port" << arduino.getarduino_port_name();
        return true;
    } else {
        qDebug() << "RFID Card Reader: Connection failed (code" << connectionResult << ")";
        return false;
    }
}

void LoginDialog::startCardScanning()
{
    if (!cardCheckTimer) {
        cardCheckTimer = new QTimer(this);
        connect(cardCheckTimer, &QTimer::timeout, this, &LoginDialog::checkForCard);
    }

    cardScanningActive = true;

    if (!cardCheckTimer->isActive()) {
        cardCheckTimer->start(300);
        qDebug() << "✓ Card scanning started";
    } else {
        qDebug() << "✓ Card scanning already active";
    }
}

void LoginDialog::stopCardScanning()
{
    if (cardScanningActive) {
        cardScanningActive = false;
        if (cardCheckTimer && cardCheckTimer->isActive()) {
            cardCheckTimer->stop();
        }
        qDebug() << "✓ Card scanning stopped";
    }
}

void LoginDialog::checkForCard()
{
    if (!cardScanningActive) {
        return;
    }

    QByteArray cardData = arduino.read_from_arduino();

    if (!cardData.isEmpty()) {
        QString cardUid = QString::fromUtf8(cardData).trimmed();

        // Filter out system messages
        if (cardUid == "READY" || cardUid == "HEARTBEAT" ||
            cardUid == "DOOR_OPENED" || cardUid == "DOOR_CLOSED" ||
            cardUid == "PONG" || cardUid == "READER_RESET" ||
            cardUid.contains("DOOR:")) {
            return;
        }

        cardUid.replace("\r", "");
        cardUid.replace("\n", "");
        cardUid.replace("\t", "");
        cardUid.replace(" ", "");

        if (cardUid.length() >= 4 && cardUid.length() <= 20) {
            bool isValidHex = true;
            for (int i = 0; i < cardUid.length(); i++) {
                QChar c = cardUid.at(i).toUpper();
                if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F'))) {
                    isValidHex = false;
                    break;
                }
            }

            if (isValidHex) {
                qDebug() << "=== VALID CARD DETECTED ===" << cardUid;

                // DON'T stop scanning here - let loginWithCard decide
                // stopCardScanning();

                if (!loginWithCard(cardUid)) {
                    // If login failed, wait a bit before accepting next card
                    // to prevent spam if user holds card there
                    qDebug() << "Login failed, waiting before next scan...";
                    cardScanningActive = false;
                    QTimer::singleShot(2000, this, [this]() {
                        cardScanningActive = true;
                        qDebug() << "Ready for next card scan";
                    });
                }
                // If login succeeded, scanning is already stopped in loginWithCard
            }
        }
    }
}
bool LoginDialog::loginWithCard(QString cardUid)
{
    if (cardUid.isEmpty() || cardUid.length() < 4) {
        return false;
    }

    cardUid = cardUid.trimmed().toUpper();

    qDebug() << "Checking authorization for Card:" << cardUid;

    QSqlQuery query;
    query.prepare("SELECT ID, NOM, PRENOM, POST, ADRESSE, PWD, CARD_UID "
                  "FROM EMPLOYES WHERE CARD_UID = :card_uid");
    query.bindValue(":card_uid", cardUid);

    if (!query.exec()) {
        arduino.write_to_arduino(QByteArray("ACCESS_DENIED\n"));
        QMessageBox::critical(this, "Database Error", query.lastError().text());

        // Resume scanning after error
        startCardScanning();
        return false;
    }

    if (query.next()) {
        // ✅ AUTHORIZED
        currentUser.id = query.value("ID").toInt();
        currentUser.nom = query.value("NOM").toString().trimmed();
        currentUser.prenom = query.value("PRENOM").toString().trimmed();
        currentUser.poste = query.value("POST").toString().trimmed();
        currentUser.email = query.value("ADRESSE").toString().trimmed();
        currentUser.card_uid = query.value("CARD_UID").toString().trimmed();

        authenticated = true;

        qDebug() << "=== ✅ ACCESS GRANTED ===" << currentUser.prenom << currentUser.nom;

        // Send door open command
        arduino.write_to_arduino(QByteArray("ACCESS_GRANTED\n"));

        ui->lineEditID->setText(QString::number(currentUser.id));

        // Stop scanning only on successful login
        stopCardScanning();

        QMessageBox::information(this, "✓ Access Granted",
                                 QString("Welcome %1 %2!\n\n🔓 Door opening...")
                                     .arg(currentUser.prenom)
                                     .arg(currentUser.nom));

        QTimer::singleShot(100, this, [this]() {
            this->accept();
        });

        return true;
    }
    else {
        // ❌ NOT AUTHORIZED
        qDebug() << "=== ❌ ACCESS DENIED ===";
        arduino.write_to_arduino(QByteArray("ACCESS_DENIED\n"));

        QMessageBox::warning(this, "✗ Access Denied",
                             QString("Card: %1\n\n🔒 Not authorized")
                                 .arg(cardUid));

        // IMPORTANT: Keep scanning for next card
        // Don't stop scanning on failed login
        return false;
    }
}

// Helper function to log card access attempts (add this to your class)
void LoginDialog::logCardAccess(int employeeId, QString cardUid, bool success)
{
    QSqlQuery logQuery;

    // Create a log table if it doesn't exist (run this once in your database setup)
    /*
    CREATE TABLE CARD_ACCESS_LOG (
        LOG_ID NUMBER GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
        EMPLOYEE_ID NUMBER,
        CARD_UID VARCHAR2(50),
        ACCESS_TIME TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
        SUCCESS CHAR(1),
        IP_ADDRESS VARCHAR2(50)
    );
    */

    logQuery.prepare("INSERT INTO CARD_ACCESS_LOG (EMPLOYEE_ID, CARD_UID, SUCCESS, ACCESS_TIME) "
                     "VALUES (:emp_id, :card_uid, :success, CURRENT_TIMESTAMP)");

    logQuery.bindValue(":emp_id", employeeId > 0 ? employeeId : QVariant(QVariant::Int));
    logQuery.bindValue(":card_uid", cardUid);
    logQuery.bindValue(":success", success ? "Y" : "N");

    if (!logQuery.exec()) {
        qDebug() << "Failed to log card access:" << logQuery.lastError().text();
        // Don't show error to user - logging failure shouldn't prevent login
    } else {
        qDebug() << "Card access logged successfully";
    }
}

// Optional: Add function to check if card exists and get employee name (without logging in)
bool LoginDialog::checkCardExists(QString cardUid, QString& employeeName)
{
    cardUid = cardUid.trimmed().toUpper();

    QSqlQuery query;
    query.prepare("SELECT ID, NOM, PRENOM FROM EMPLOYES WHERE CARD_UID = :card_uid");
    query.bindValue(":card_uid", cardUid);

    if (query.exec() && query.next()) {
        employeeName = QString("%1 %2")
        .arg(query.value("PRENOM").toString())
            .arg(query.value("NOM").toString());
        return true;
    }

    return false;
}

// Optional: Function to register a new card for an employee
bool LoginDialog::registerCardForEmployee(int employeeId, QString cardUid)
{
    // Validate inputs
    if (employeeId <= 0 || cardUid.isEmpty()) {
        return false;
    }

    cardUid = cardUid.trimmed().toUpper();

    // Check if card is already assigned
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT ID, NOM, PRENOM FROM EMPLOYES WHERE CARD_UID = :card_uid");
    checkQuery.bindValue(":card_uid", cardUid);

    if (checkQuery.exec() && checkQuery.next()) {
        int existingId = checkQuery.value("ID").toInt();
        if (existingId != employeeId) {
            QString existingName = QString("%1 %2")
            .arg(checkQuery.value("PRENOM").toString())
                .arg(checkQuery.value("NOM").toString());

            QMessageBox::warning(this, "Card Already Registered",
                                 QString("This card is already assigned to:\n%1 (ID: %2)")
                                     .arg(existingName)
                                     .arg(existingId));
            return false;
        }
    }

    // Register the card
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE EMPLOYES SET CARD_UID = :card_uid WHERE ID = :id");
    updateQuery.bindValue(":card_uid", cardUid);
    updateQuery.bindValue(":id", employeeId);

    if (updateQuery.exec()) {
        qDebug() << "Card registered successfully for employee ID:" << employeeId;
        return true;
    } else {
        qDebug() << "Failed to register card:" << updateQuery.lastError().text();
        return false;
    }
}

QString LoginDialog::hashPassword(const QString &password)
{
    return QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5).toHex());
}

bool LoginDialog::verifyUser(const QString &employeeId, const QString &password)
{
    QSqlQuery query;
    query.prepare("SELECT ID, NOM, PRENOM, POST, ADRESSE, PWD, CARD_UID FROM EMPLOYES WHERE ID = :id");
    query.bindValue(":id", employeeId.toInt());

    if (query.exec() && query.next()) {
        QString storedPassword = query.value("PWD").toString();

        if (password == storedPassword) {
            currentUser.id = query.value("ID").toInt();
            currentUser.nom = query.value("NOM").toString().trimmed();
            currentUser.prenom = query.value("PRENOM").toString().trimmed();
            currentUser.poste = query.value("POST").toString().trimmed();
            currentUser.email = query.value("ADRESSE").toString().trimmed();
            currentUser.card_uid = query.value("CARD_UID").toString().trimmed();
            return true;
        }
    }

    return false;
}

bool LoginDialog::resetPassword(const QString &employeeId, const QString &securityAnswer,
                                const QString &newPassword)
{
    if (employeeId.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter Employee ID.");
        return false;
    }

    if (newPassword.length() < 4) {
        QMessageBox::warning(this, "Error", "Password must be at least 4 characters.");
        return false;
    }

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT ID, NOM, PRENOM, ADRESSE, SALAIRE FROM EMPLOYES WHERE ID = :id");
    checkQuery.bindValue(":id", employeeId.toInt());

    if (!checkQuery.exec()) {
        QMessageBox::warning(this, "Error", "Database error.");
        return false;
    }

    if (checkQuery.next()) {
        QString nom = checkQuery.value("NOM").toString();
        QString prenom = checkQuery.value("PRENOM").toString();
        QString expectedAdresse = checkQuery.value("ADRESSE").toString().trimmed();
        double expectedSalaire = checkQuery.value("SALAIRE").toDouble();
        QString expectedAnswer = QString("%1 = %2").arg(expectedAdresse).arg(expectedSalaire, 0, 'f', 1);

        if (securityAnswer == expectedAnswer) {
            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE EMPLOYES SET PWD = :pwd WHERE ID = :id");
            updateQuery.bindValue(":pwd", newPassword);
            updateQuery.bindValue(":id", employeeId.toInt());

            if (updateQuery.exec()) {
                QMessageBox::information(this, "Success",
                                         QString("Password reset successfully for %1 %2!")
                                             .arg(prenom)
                                             .arg(nom));
                return true;
            } else {
                QMessageBox::warning(this, "Error", "Error updating password.");
            }
        }
    }

    return false;
}

void LoginDialog::on_pushButtonLogin_clicked()
{
    QString employeeId = ui->lineEditID->text().trimmed();
    QString password = ui->lineEditPassword->text();

    if (employeeId.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill all fields.");
        return;
    }

    if (verifyUser(employeeId, password)) {
        authenticated = true;
        accept();
    } else {
        QMessageBox::warning(this, "Error", "Invalid Employee ID or Password.");
        ui->lineEditPassword->clear();
        ui->lineEditPassword->setFocus();
    }
}

void LoginDialog::on_pushButtonForgot_clicked()
{
    stopCardScanning();
    ui->loginGroup->setVisible(false);
    ui->forgotGroup->setVisible(true);
    ui->lineEditForgotID->setFocus();
}

void LoginDialog::on_pushButtonReset_clicked()
{
    QString employeeId = ui->lineEditForgotID->text().trimmed();
    QString securityAnswer = ui->lineEditSecurityAnswer->text().trimmed();
    QString newPassword = ui->lineEditNewPassword->text();

    if (employeeId.isEmpty() || securityAnswer.isEmpty() || newPassword.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill all fields.");
        return;
    }

    if (resetPassword(employeeId, securityAnswer, newPassword)) {
        on_pushButtonBack_clicked();
    }
}

void LoginDialog::on_pushButtonBack_clicked()
{
    if (arduino.getserial() && arduino.getserial()->isOpen()) {
        startCardScanning();
    }

    ui->forgotGroup->setVisible(false);
    ui->loginGroup->setVisible(true);
    ui->lineEditSecurityAnswer->clear();
    ui->lineEditNewPassword->clear();
    ui->lineEditForgotID->clear();
}

