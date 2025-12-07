#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

class Connection
{
private:
    QSqlDatabase db;
    Connection();    // Objet de connexion à la base de données
    ~Connection();
    Connection(const Connection&)=delete;
    Connection& operator=(const Connection&)=delete;
public:
    static Connection& createInstance();
    bool createconnect();  // Ouvre la connexion
};

#endif // CONNECTION_H
