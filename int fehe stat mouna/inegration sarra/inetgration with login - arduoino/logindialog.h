#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

namespace Ui {
class LoginDialog;
}

struct UserInfo {
    int id;
    QString nom;
    QString prenom;
    QString poste;
    QString email;
};

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    UserInfo getCurrentUser() const;
    bool isAuthenticated() const { return authenticated; }

private slots:
    void on_pushButtonLogin_clicked();
    void on_pushButtonForgot_clicked();
    void on_pushButtonReset_clicked();
    void on_pushButtonBack_clicked();
    void on_btnpage2vente_clicked();

private:
    Ui::LoginDialog *ui;
    UserInfo currentUser;
    bool authenticated;

    QString hashPassword(const QString &password);
    bool verifyUser(const QString &employeeId, const QString &password);
    bool resetPassword(const QString &employeeId, const QString &securityAnswer,
                       const QString &newPassword);
};

#endif // LOGINDIALOG_H
