#include "connection.h"
#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection &c=Connection::createInstance();
    bool test =c.createconnect();
    MainWindow w;
    if (test) {
        w.show();
        QMessageBox::information(nullptr, QObject::tr("Database Connection"),
                                 QObject::tr("✅ Connexion réussie à la base de données."),
                                 QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Database Connection"),
                              QObject::tr("❌ Échec de la connexion à la base de données.\n"
                                          "Vérifiez votre DSN et vos identifiants."),
                              QMessageBox::Cancel);

    }




    return a.exec();
}
