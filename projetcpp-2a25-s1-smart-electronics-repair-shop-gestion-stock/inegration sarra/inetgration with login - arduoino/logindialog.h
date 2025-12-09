#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QTimer>
#include "arduino.h"

namespace Ui {
class LoginDialog;
}

struct UserInfo {
    int id;
    QString nom;
    QString prenom;
    QString poste;
    QString email;
    QString card_uid;
};

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    UserInfo getCurrentUser() const { return currentUser; }  // INLINE implementation
    bool isAuthenticated() const { return authenticated; }

private slots:
    void on_pushButtonLogin_clicked();
    void on_pushButtonForgot_clicked();
    void on_pushButtonReset_clicked();
    void on_pushButtonBack_clicked();


    // Card scanning slot
    void checkForCard();

private:
    Ui::LoginDialog *ui;
    UserInfo currentUser;
    bool authenticated;
    Arduino arduino;
    QTimer *cardCheckTimer;
    bool cardScanningActive;

    QString hashPassword(const QString &password);
    bool verifyUser(const QString &employeeId, const QString &password);
    bool resetPassword(const QString &employeeId, const QString &securityAnswer,
                       const QString &newPassword);

    // Card-related methods
    bool loginWithCard(QString cardUid);
    void logCardAccess(int employeeId, QString cardUid, bool success);

    // Helper functions
    bool checkCardExists(QString cardUid, QString& employeeName);
    bool registerCardForEmployee(int employeeId, QString cardUid);
    bool setupArduino();
    void stopCardScanning();
    void startCardScanning();
    void reconnectArduino(); // ADDED
};

#endif // LOGINDIALOG_H
