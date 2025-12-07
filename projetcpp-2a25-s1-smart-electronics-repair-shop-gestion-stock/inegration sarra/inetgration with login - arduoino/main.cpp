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

    // Main application loop for login/logout
    while (true) {
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
                                             .arg(user.poste));

                // Run the application - when main window closes, we return here
                a.exec();

                // When we get here, the main window has been closed (logout)
                // The loop will continue and show login dialog again
            }
        } else {
            // User cancelled login - exit application completely
            break;
        }
    }

    return 0;
}
