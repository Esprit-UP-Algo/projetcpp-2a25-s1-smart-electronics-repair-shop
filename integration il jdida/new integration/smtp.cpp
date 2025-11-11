#include "smtp.h"
#include <QDebug>

Smtp::Smtp(QObject *parent) : QObject(parent)
{
    socket = new QSslSocket(this);
    connect(socket, &QSslSocket::readyRead, this, &Smtp::readyRead);
}

void Smtp::setUser(const QString &user)
{
    m_user = user;
}

void Smtp::setPassword(const QString &password)
{
    m_password = password;
}

void Smtp::sendMail(const QString &from,
                    const QString &to,
                    const QString &subject,
                    const QString &body)
{
    socket->connectToHostEncrypted("smtp.gmail.com", 465);

    if (!socket->waitForEncrypted(5000)) {
        qDebug() << "❌ SSL connection failed!";
        return;
    }

    QByteArray user64 = m_user.toUtf8().toBase64();
    QByteArray pass64 = m_password.toUtf8().toBase64();

    auto send = [&](QString cmd) {
        socket->write(cmd.toUtf8() + "\r\n");
        socket->waitForBytesWritten();
        socket->waitForReadyRead();
        qDebug() << socket->readAll();
    };

    send("EHLO localhost");
    send("AUTH LOGIN");
    send(user64);
    send(pass64);
    send("MAIL FROM:<" + from + ">");
    send("RCPT TO:<" + to + ">");
    send("DATA");

    QString msg;
    msg += "From: <" + from + ">\r\n";
    msg += "To: <" + to + ">\r\n";
    msg += "Subject: " + subject + "\r\n";
    msg += "Content-Type: text/plain; charset=UTF-8\r\n\r\n";
    msg += body + "\r\n.\r\n";

    socket->write(msg.toUtf8());
    socket->waitForBytesWritten();
    socket->waitForReadyRead();
    qDebug() << socket->readAll();

    send("QUIT");
}

void Smtp::readyRead()
{
    QByteArray resp = socket->readAll();
    qDebug() << resp;
}
