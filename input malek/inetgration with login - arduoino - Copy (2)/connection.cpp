#include "connection.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
Connection::Connection()
{
    // Initialisation du type de base de données (QODBC ici)
    db = QSqlDatabase::addDatabase("QODBC");

}
Connection::~Connection()
{
    if(db.isOpen()) db.close();
}
Connection& Connection::createInstance()
{
    static Connection instance ;
    return instance;
}
bool Connection::createconnect()
{
    db.setDatabaseName("smartelectronique");
    db.setUserName("elyes");
    db.setPassword("esprit18");
    if (db.open()) {
        qDebug() << "✅ Connexion établie avec succès à la base de données.";
        return true;
    } else {
        qDebug() << "❌ Échec de la connexion:" << db.lastError().text();
        return false;
    }
}

