#include "connection.h"
#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Test database connection
    Connection &c = Connection::createInstance();
    bool test = c.createconnect();

    if (!test) {
        QMessageBox::critical(nullptr, "Erreur de connexion",
                              "❌ Échec de la connexion à la base de données.\n"
                              "Vérifiez votre configuration.", QMessageBox::Cancel);
        return -1;
    }

    // Show login dialog
    LoginDialog loginDialog;
    if (loginDialog.exec() == QDialog::Accepted) {
        if (loginDialog.isAuthenticated()) {
            // Create main window with user info
            UserInfo user = loginDialog.getCurrentUser();
            MainWindow w(user);
            w.show();

            QMessageBox::information(nullptr, "Connexion réussie",
                                     QString("✅ Bienvenue %1 %2!\nRôle: %3")
                                         .arg(user.prenom)
                                         .arg(user.nom)
                                         .arg(user.poste), QMessageBox::Ok);

            return a.exec();
        }
    }

    // If login failed or dialog was cancelled
    return 0;
}
