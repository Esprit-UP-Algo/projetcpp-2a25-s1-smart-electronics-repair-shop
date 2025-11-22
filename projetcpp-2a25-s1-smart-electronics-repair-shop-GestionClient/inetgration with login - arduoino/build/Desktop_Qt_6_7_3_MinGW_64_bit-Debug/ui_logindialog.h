/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QSpacerItem *verticalSpacer;
    QGroupBox *loginGroup;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLineEdit *lineEditID;
    QLabel *label_2;
    QLineEdit *lineEditPassword;
    QPushButton *pushButtonLogin;
    QPushButton *pushButtonForgot;
    QGroupBox *forgotGroup;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEditForgotID;
    QLabel *label_4;
    QLabel *labelSecurityQuestion;
    QLabel *label_6;
    QLineEdit *lineEditSecurityAnswer;
    QLabel *label_5;
    QLineEdit *lineEditNewPassword;
    QPushButton *pushButtonReset;
    QPushButton *pushButtonBack;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName("LoginDialog");
        LoginDialog->resize(400, 450);
        LoginDialog->setStyleSheet(QString::fromUtf8("\n"
"QDialog {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #1e2a36, stop:1 #2c3e50);\n"
"    border-radius: 15px;\n"
"    color: #ecf0f1;\n"
"    border: 2px solid #1abc9c;\n"
"}\n"
"\n"
"QGroupBox {\n"
"    background: #34495e;\n"
"    border: 2px solid #1abc9c;\n"
"    border-radius: 10px;\n"
"    margin-top: 10px;\n"
"    padding-top: 10px;\n"
"    font-weight: bold;\n"
"    color: #ecf0f1;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QLineEdit {\n"
"    border: 2px solid #7f8c8d;\n"
"    border-radius: 8px;\n"
"    padding: 10px;\n"
"    font-size: 14px;\n"
"    background: #2c3e50;\n"
"    color: #ecf0f1;\n"
"    selection-background-color: #1abc9c;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border-color: #1abc9c;\n"
"    background: #34495e;\n"
"}\n"
"\n"
"QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #1abc9c, stop:1 #16a085);\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 12px;\n"
"    fo"
                        "nt-weight: bold;\n"
"    font-size: 14px;\n"
"    min-height: 20px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #16a085, stop:1 #1abc9c);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background: #1abc9c;\n"
"}\n"
"\n"
"QLabel {\n"
"    color: #ecf0f1;\n"
"    font-weight: bold;\n"
"    font-size: 12px;\n"
"}\n"
"\n"
"#titleLabel {\n"
"    font-size: 24px;\n"
"    color: #1abc9c;\n"
"    font-weight: bold;\n"
"    padding: 10px;\n"
"}\n"
"\n"
"QPushButton#pushButtonForgot {\n"
"    background: transparent;\n"
"    color: #1abc9c;\n"
"    text-decoration: underline;\n"
"    border: none;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton#pushButtonForgot:hover {\n"
"    color: #16a085;\n"
"    background: transparent;\n"
"}\n"
"   "));
        verticalLayout = new QVBoxLayout(LoginDialog);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(LoginDialog);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        verticalSpacer = new QSpacerItem(20, 30, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        loginGroup = new QGroupBox(LoginDialog);
        loginGroup->setObjectName("loginGroup");
        verticalLayout_2 = new QVBoxLayout(loginGroup);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(loginGroup);
        label->setObjectName("label");

        verticalLayout_2->addWidget(label);

        lineEditID = new QLineEdit(loginGroup);
        lineEditID->setObjectName("lineEditID");

        verticalLayout_2->addWidget(lineEditID);

        label_2 = new QLabel(loginGroup);
        label_2->setObjectName("label_2");

        verticalLayout_2->addWidget(label_2);

        lineEditPassword = new QLineEdit(loginGroup);
        lineEditPassword->setObjectName("lineEditPassword");
        lineEditPassword->setEchoMode(QLineEdit::Password);

        verticalLayout_2->addWidget(lineEditPassword);

        pushButtonLogin = new QPushButton(loginGroup);
        pushButtonLogin->setObjectName("pushButtonLogin");

        verticalLayout_2->addWidget(pushButtonLogin);

        pushButtonForgot = new QPushButton(loginGroup);
        pushButtonForgot->setObjectName("pushButtonForgot");

        verticalLayout_2->addWidget(pushButtonForgot);


        verticalLayout->addWidget(loginGroup);

        forgotGroup = new QGroupBox(LoginDialog);
        forgotGroup->setObjectName("forgotGroup");
        forgotGroup->setVisible(false);
        verticalLayout_3 = new QVBoxLayout(forgotGroup);
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_3 = new QLabel(forgotGroup);
        label_3->setObjectName("label_3");

        verticalLayout_3->addWidget(label_3);

        lineEditForgotID = new QLineEdit(forgotGroup);
        lineEditForgotID->setObjectName("lineEditForgotID");

        verticalLayout_3->addWidget(lineEditForgotID);

        label_4 = new QLabel(forgotGroup);
        label_4->setObjectName("label_4");

        verticalLayout_3->addWidget(label_4);

        labelSecurityQuestion = new QLabel(forgotGroup);
        labelSecurityQuestion->setObjectName("labelSecurityQuestion");
        labelSecurityQuestion->setStyleSheet(QString::fromUtf8("color: #1abc9c; font-weight: bold; font-size: 12px;"));

        verticalLayout_3->addWidget(labelSecurityQuestion);

        label_6 = new QLabel(forgotGroup);
        label_6->setObjectName("label_6");
        label_6->setStyleSheet(QString::fromUtf8("color: #bdc3c7; font-size: 10px; font-style: italic;"));

        verticalLayout_3->addWidget(label_6);

        lineEditSecurityAnswer = new QLineEdit(forgotGroup);
        lineEditSecurityAnswer->setObjectName("lineEditSecurityAnswer");

        verticalLayout_3->addWidget(lineEditSecurityAnswer);

        label_5 = new QLabel(forgotGroup);
        label_5->setObjectName("label_5");

        verticalLayout_3->addWidget(label_5);

        lineEditNewPassword = new QLineEdit(forgotGroup);
        lineEditNewPassword->setObjectName("lineEditNewPassword");
        lineEditNewPassword->setEchoMode(QLineEdit::Password);

        verticalLayout_3->addWidget(lineEditNewPassword);

        pushButtonReset = new QPushButton(forgotGroup);
        pushButtonReset->setObjectName("pushButtonReset");

        verticalLayout_3->addWidget(pushButtonReset);

        pushButtonBack = new QPushButton(forgotGroup);
        pushButtonBack->setObjectName("pushButtonBack");

        verticalLayout_3->addWidget(pushButtonBack);


        verticalLayout->addWidget(forgotGroup);

        verticalSpacer_2 = new QSpacerItem(20, 30, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Connexion - Smart Electronics", nullptr));
        titleLabel->setText(QCoreApplication::translate("LoginDialog", "\360\237\224\220 SMART ELECTRONICS", nullptr));
        loginGroup->setTitle(QCoreApplication::translate("LoginDialog", "Connexion", nullptr));
        label->setText(QCoreApplication::translate("LoginDialog", "ID Employ\303\251:", nullptr));
        lineEditID->setPlaceholderText(QCoreApplication::translate("LoginDialog", "Entrez votre ID", nullptr));
        label_2->setText(QCoreApplication::translate("LoginDialog", "Mot de passe:", nullptr));
        lineEditPassword->setPlaceholderText(QCoreApplication::translate("LoginDialog", "Entrez votre mot de passe", nullptr));
        pushButtonLogin->setText(QCoreApplication::translate("LoginDialog", "Se Connecter", nullptr));
        pushButtonForgot->setText(QCoreApplication::translate("LoginDialog", "Mot de passe oubli\303\251 ?", nullptr));
        forgotGroup->setTitle(QCoreApplication::translate("LoginDialog", "R\303\251cup\303\251ration de mot de passe", nullptr));
        label_3->setText(QCoreApplication::translate("LoginDialog", "ID Employ\303\251:", nullptr));
        lineEditForgotID->setPlaceholderText(QCoreApplication::translate("LoginDialog", "Entrez votre ID", nullptr));
        label_4->setText(QCoreApplication::translate("LoginDialog", "Question de s\303\251curit\303\251:", nullptr));
        labelSecurityQuestion->setText(QCoreApplication::translate("LoginDialog", "V\303\251rification: adresse = salaire", nullptr));
        label_6->setText(QCoreApplication::translate("LoginDialog", "Format: votre_adresse = votre_salaire", nullptr));
        lineEditSecurityAnswer->setPlaceholderText(QCoreApplication::translate("LoginDialog", "Ex: Tunis = 1500.0", nullptr));
        label_5->setText(QCoreApplication::translate("LoginDialog", "Nouveau mot de passe:", nullptr));
        lineEditNewPassword->setPlaceholderText(QCoreApplication::translate("LoginDialog", "Nouveau mot de passe", nullptr));
        pushButtonReset->setText(QCoreApplication::translate("LoginDialog", "R\303\251initialiser le mot de passe", nullptr));
        pushButtonBack->setText(QCoreApplication::translate("LoginDialog", "Retour \303\240 la connexion", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
