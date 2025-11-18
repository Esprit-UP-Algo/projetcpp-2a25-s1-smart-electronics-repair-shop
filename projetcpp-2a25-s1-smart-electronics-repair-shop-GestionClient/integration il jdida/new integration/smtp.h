#ifndef SMTP_H
#define SMTP_H

#include <QObject>
#include <QtNetwork/QSslSocket>
#include <QString>
#include <QTextStream>
#include <QDebug>

class Smtp : public QObject
{
    Q_OBJECT

public:
    Smtp(const QString &user, const QString &pass, const QString &host = "smtp.gmail.com", int port = 465, int timeout = 30000);
    ~Smtp();

    void sendMail(const QString &from, const QString &to, const QString &subject, const QString &body);

private slots:
    void stateChanged(QAbstractSocket::SocketState socketState);
    void errorReceived(QAbstractSocket::SocketError socketError);
    void disconnected();
    void connected();
    void readyRead();

private:
    QString message;
    QTextStream *t;
    QSslSocket *socket;
    QString from;
    QString rcpt;
    QString response;
    QString user;
    QString pass;
    QString host;
    int port;
    int timeout;
    enum states { Tls, HandShake, Auth, User, Pass, Rcpt, Mail, Data, Init, Body, Quit, Close };
    int state;
};

#endif
