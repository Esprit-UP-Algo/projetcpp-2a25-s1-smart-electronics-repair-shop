#include "smtp.h"
#include <QMessageBox>

Smtp::Smtp(const QString &user, const QString &pass, const QString &host, int port, int timeout) :
    user(user), pass(pass), host(host), port(port), timeout(timeout)
{
    socket = new QSslSocket(this);

    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChanged(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), this, SLOT(errorReceived(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

Smtp::~Smtp()
{
    delete t;
    delete socket;
}

void Smtp::sendMail(const QString &from, const QString &to, const QString &subject, const QString &body)
{
    this->from = from;
    rcpt = to;
    message = "To: " + to + "\n";
    message.append("From: " + from + "\n");
    message.append("Subject: " + subject + "\n");
    message.append("MIME-Version: 1.0\n");
    message.append("Content-Type: text/html; charset=utf-8\n\n");
    message.append(body);
    message.replace(QString::fromLatin1("\n"), QString::fromLatin1("\r\n"));
    message.replace(QString::fromLatin1("\r\n.\r\n"), QString::fromLatin1("\r\n..\r\n"));

    state = Init;
    socket->connectToHostEncrypted(host, port);
    if (!socket->waitForConnected(timeout)) {
        qDebug() << "Connection failed:" << socket->errorString();
    }

    t = new QTextStream(socket);
}

void Smtp::stateChanged(QAbstractSocket::SocketState socketState)
{
    qDebug() << "State changed:" << socketState;
}

void Smtp::errorReceived(QAbstractSocket::SocketError socketError)
{
    qDebug() << "Error:" << socketError;
}

void Smtp::disconnected()
{
    qDebug() << "Disconnected";
}

void Smtp::connected()
{
    qDebug() << "Connected";
}

void Smtp::readyRead()
{
    response = QString::fromUtf8(socket->readAll());
    qDebug() << "Response:" << response;

    if (state != Close) {
        switch (state) {
        case Init:
            *t << "EHLO localhost\r\n";
            t->flush();
            state = HandShake;
            break;
        case HandShake:
            if (response.startsWith("250")) {
                *t << "AUTH LOGIN\r\n";
                t->flush();
                state = Auth;
            }
            break;
        case Auth:
            if (response.startsWith("334")) {
                *t << user.toUtf8().toBase64() << "\r\n";
                t->flush();
                state = User;
            }
            break;
        case User:
            if (response.startsWith("334")) {
                *t << pass.toUtf8().toBase64() << "\r\n";
                t->flush();
                state = Pass;
            }
            break;
        case Pass:
            if (response.startsWith("235")) {
                *t << "MAIL FROM: <" << from << ">\r\n";
                t->flush();
                state = Mail;
            }
            break;
        case Mail:
            if (response.startsWith("250")) {
                *t << "RCPT TO: <" << rcpt << ">\r\n";
                t->flush();
                state = Rcpt;
            }
            break;
        case Rcpt:
            if (response.startsWith("250")) {
                *t << "DATA\r\n";
                t->flush();
                state = Data;
            }
            break;
        case Data:
            if (response.startsWith("354")) {
                *t << message << "\r\n.\r\n";
                t->flush();
                state = Body;
            }
            break;
        case Body:
            if (response.startsWith("250")) {
                *t << "QUIT\r\n";
                t->flush();
                state = Quit;
            }
            break;
        case Quit:
            if (response.startsWith("221")) {
                state = Close;
                socket->disconnectFromHost();
            }
            break;
        default:
            break;
        }
    }
}
