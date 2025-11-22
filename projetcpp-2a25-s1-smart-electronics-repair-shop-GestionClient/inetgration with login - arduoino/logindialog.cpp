#include "logindialog.h"
#include "ui_logindialog.h"
#include <QCryptographicHash>
#include <QDebug>
#include <QSqlRecord>  // Add this include

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),
    authenticated(false)
{
    ui->setupUi(this);

    // Initialize currentUser
    currentUser.id = 0;
    currentUser.nom = "";
    currentUser.prenom = "";
    currentUser.poste = "";
    currentUser.email = "";

    // Connect signals and slots
    connect(ui->pushButtonLogin, &QPushButton::clicked, this, &LoginDialog::on_pushButtonLogin_clicked);
    connect(ui->pushButtonForgot, &QPushButton::clicked, this, &LoginDialog::on_pushButtonForgot_clicked);
    connect(ui->pushButtonReset, &QPushButton::clicked, this, &LoginDialog::on_pushButtonReset_clicked);
    connect(ui->pushButtonBack, &QPushButton::clicked, this, &LoginDialog::on_pushButtonBack_clicked);

    // Set focus to employee ID field
    ui->lineEditID->setFocus();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

UserInfo LoginDialog::getCurrentUser() const
{
    return currentUser;
}

QString LoginDialog::hashPassword(const QString &password)
{
    return QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5).toHex());
}

bool LoginDialog::verifyUser(const QString &employeeId, const QString &password)
{
    QSqlQuery query;

    qDebug() << "=== LOGIN ATTEMPT ===";
    qDebug() << "ID:" << employeeId << "Password:" << password;

    // First, let's check what employees exist and their passwords
    QSqlQuery debugQuery("SELECT ID, NOM, PRENOM, POST, PWD FROM EMPLOYES");
    qDebug() << "=== DATABASE CONTENTS ===";
    while (debugQuery.next()) {
        qDebug() << "ID:" << debugQuery.value("ID").toInt()
        << "Name:" << debugQuery.value("NOM").toString()
        << debugQuery.value("PRENOM").toString()
        << "Post:" << debugQuery.value("POST").toString()
        << "PWD:" << debugQuery.value("PWD").toString();
    }

    // Try different query approaches
    bool success = false;

    // Approach 1: Check if user exists first
    query.prepare("SELECT ID, NOM, PRENOM, POST, ADRESSE, PWD FROM EMPLOYES WHERE ID = ?");
    query.addBindValue(employeeId.toInt());

    if (query.exec() && query.next()) {
        QString storedPassword = query.value("PWD").toString();
        qDebug() << "Found user - Stored PWD:" << storedPassword;
        qDebug() << "Password comparison:" << (password == storedPassword);

        if (password == storedPassword) {
            currentUser.id = query.value("ID").toInt();
            currentUser.nom = query.value("NOM").toString().trimmed();
            currentUser.prenom = query.value("PRENOM").toString().trimmed();
            currentUser.poste = query.value("POST").toString().trimmed();
            currentUser.email = query.value("ADRESSE").toString().trimmed();
            success = true;
        }
    } else {
        qDebug() << "User not found with ID:" << employeeId;
    }

    qDebug() << "Login result:" << (success ? "SUCCESS" : "FAILED");
    return success;
}

bool LoginDialog::resetPassword(const QString &employeeId, const QString &securityAnswer,
                                const QString &newPassword)
{
    qDebug() << "=== RESET PASSWORD DEBUG ===";
    qDebug() << "Employee ID:" << employeeId;
    qDebug() << "Security Answer:" << securityAnswer;
    qDebug() << "New Password:" << newPassword;

    // Validate inputs
    if (employeeId.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID employé.");
        return false;
    }

    if (newPassword.length() < 4) {
        QMessageBox::warning(this, "Erreur", "Le mot de passe doit contenir au moins 4 caractères.");
        return false;
    }

    // First, check if employee exists
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT ID, NOM, PRENOM, ADRESSE, SALAIRE FROM EMPLOYES WHERE ID = ?");
    checkQuery.addBindValue(employeeId.toInt());

    if (!checkQuery.exec()) {
        qDebug() << "Query error:" << checkQuery.lastError().text();
        QMessageBox::warning(this, "Erreur", "Erreur de base de données.");
        return false;
    }

    if (checkQuery.next()) {
        // Employee exists
        QString nom = checkQuery.value("NOM").toString();
        QString prenom = checkQuery.value("PRENOM").toString();
        QString expectedAdresse = checkQuery.value("ADRESSE").toString().trimmed();
        double expectedSalaire = checkQuery.value("SALAIRE").toDouble();
        QString expectedAnswer = QString("%1 = %2").arg(expectedAdresse).arg(expectedSalaire, 0, 'f', 1);

        qDebug() << "Employee found:" << nom << prenom;
        qDebug() << "Security verification:";
        qDebug() << "  Expected answer:" << expectedAnswer;
        qDebug() << "  User answer:" << securityAnswer;
        qDebug() << "  Match:" << (securityAnswer == expectedAnswer);

        if (securityAnswer == expectedAnswer) {
            // Update password
            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE EMPLOYES SET PWD = ? WHERE ID = ?");
            updateQuery.addBindValue(newPassword);
            updateQuery.addBindValue(employeeId.toInt());

            if (updateQuery.exec()) {
                qDebug() << "Password updated successfully for employee ID:" << employeeId;
                QMessageBox::information(this, "Succès",
                                         QString("Mot de passe réinitialisé avec succès pour %1 %2!")
                                             .arg(prenom)
                                             .arg(nom));
                return true;
            } else {
                qDebug() << "Update error:" << updateQuery.lastError().text();
                QMessageBox::warning(this, "Erreur", "Erreur lors de la mise à jour du mot de passe.");
            }
        }
    } else {
        qDebug() << "No employee found with ID:" << employeeId;

        // Show available IDs for help
        QSqlQuery idQuery("SELECT ID FROM EMPLOYES ORDER BY ID");
        QString availableIds;
        while (idQuery.next()) {
            availableIds += idQuery.value("ID").toString() + ", ";
        }

        QMessageBox::warning(this, "Erreur",
                             QString("Aucun employé trouvé avec l'ID: %1\n\nIDs disponibles: %2")
                                 .arg(employeeId)
                                 .arg(availableIds));
    }

    return false;
}



void LoginDialog::on_pushButtonLogin_clicked()
{
    QString employeeId = ui->lineEditID->text().trimmed();
    QString password = ui->lineEditPassword->text();

    qDebug() << "=== LOGIN BUTTON CLICKED ===";
    qDebug() << "Input - ID:" << employeeId << "Password:" << password;

    if (employeeId.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs.");
        return;
    }

    // Test with hardcoded values first
    if (employeeId == "123" && password == "aymen") {
        qDebug() << "Hardcoded test passed!";
    }

    if (verifyUser(employeeId, password)) {
        authenticated = true;
        qDebug() << "=== LOGIN SUCCESSFUL ===";
        qDebug() << "User:" << currentUser.prenom << currentUser.nom;
        qDebug() << "Role:" << currentUser.poste;
        accept();
    } else {
        QMessageBox::warning(this, "Erreur", "ID employé ou mot de passe incorrect.");

        // Show available IDs
        QSqlQuery idQuery("SELECT ID FROM EMPLOYES ORDER BY ID");
        QString availableIds;
        while (idQuery.next()) {
            availableIds += idQuery.value("ID").toString() + ", ";
        }
        qDebug() << "Available employee IDs:" << availableIds;

        ui->lineEditPassword->clear();
        ui->lineEditPassword->setFocus();
    }
}

void LoginDialog::on_pushButtonForgot_clicked()
{
    ui->loginGroup->setVisible(false);
    ui->forgotGroup->setVisible(true);
    ui->lineEditForgotID->setFocus();
}

void LoginDialog::on_pushButtonReset_clicked()
{
    QString employeeId = ui->lineEditForgotID->text().trimmed();
    QString securityAnswer = ui->lineEditSecurityAnswer->text().trimmed();
    QString newPassword = ui->lineEditNewPassword->text();

    qDebug() << "=== RESET BUTTON CLICKED ===";
    qDebug() << "Employee ID:" << employeeId;
    qDebug() << "Security Answer:" << securityAnswer;
    qDebug() << "New Password:" << newPassword;

    if (employeeId.isEmpty() || securityAnswer.isEmpty() || newPassword.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs.");
        return;
    }

    if (resetPassword(employeeId, securityAnswer, newPassword)) {
        on_pushButtonBack_clicked();
    }
}

void LoginDialog::on_pushButtonBack_clicked()
{
    ui->forgotGroup->setVisible(false);
    ui->loginGroup->setVisible(true);
    ui->lineEditSecurityAnswer->clear();
    ui->lineEditNewPassword->clear();
    ui->lineEditForgotID->clear();
}
