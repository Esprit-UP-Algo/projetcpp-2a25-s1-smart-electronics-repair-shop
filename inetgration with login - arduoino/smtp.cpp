#include "smtp.h"
#include <QDebug>
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
Smtp::Smtp(QObject *parent) : QObject(parent)
{
    socket = new QSslSocket(this);
    connect(socket, &QSslSocket::readyRead, this, &Smtp::readyRead);
}

void Smtp::setUser(const QString &user)
{
    m_user = user;
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
void Smtp::sendMail2(const QString &from, const QString &to, const QString &subject, const QString &body)
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

    // HTML formatted email message
    QString msg;
    msg += "From: <" + from + ">\r\n";
    msg += "To: <" + to + ">\r\n";
    msg += "Subject: " + subject + "\r\n";
    msg += "MIME-Version: 1.0\r\n";
    msg += "Content-Type: text/html; charset=UTF-8\r\n";
    msg += "\r\n"; // Empty line to separate headers from body

    // HTML content with professional design
    msg += "<!DOCTYPE html>\r\n";
    msg += "<html>\r\n";
    msg += "<head>\r\n";
    msg += "    <meta charset='UTF-8'>\r\n";
    msg += "    <style>\r\n";
    msg += "        body { font-family: Arial, sans-serif; line-height: 1.6; color: #333; max-width: 600px; margin: 0 auto; background-color: #f5f5f5; padding: 20px; }\r\n";
    msg += "        .email-container { background: white; border-radius: 10px; overflow: hidden; box-shadow: 0 4px 6px rgba(0,0,0,0.1); }\r\n";
    msg += "        .header { background: #2c3e50; color: white; padding: 25px; text-align: center; position: relative; }\r\n";
    msg += "        .company-name-border { \r\n";
    msg += "            border: 3px solid #e74c3c; \r\n";
    msg += "            padding: 15px 30px; \r\n";
    msg += "            display: inline-block; \r\n";
    msg += "            margin: 10px 0; \r\n";
    msg += "            border-radius: 8px; \r\n";
    msg += "            background: rgba(255,255,255,0.1); \r\n";
    msg += "            box-shadow: 0 2px 4px rgba(0,0,0,0.2); \r\n";
    msg += "        }\r\n";
    msg += "        .company-name { font-size: 28px; font-weight: bold; margin: 0; letter-spacing: 1px; text-transform: uppercase; }\r\n";
    msg += "        .tagline { font-size: 14px; opacity: 0.9; margin: 10px 0 0 0; font-style: italic; }\r\n";
    msg += "        .content { padding: 30px; }\r\n";
    msg += "        .message { background: #f8f9fa; padding: 20px; border-radius: 8px; border-left: 5px solid #3498db; margin: 20px 0; line-height: 1.8; }\r\n";
    msg += "        .footer { text-align: center; padding: 20px; font-size: 12px; color: #7f8c8d; border-top: 1px solid #ecf0f1; margin-top: 20px; background: #f8f9fa; }\r\n";
    msg += "        .contact-info { background: #e8f4fd; padding: 15px; border-radius: 8px; margin: 20px 0; font-size: 14px; border: 1px solid #b3e0ff; }\r\n";
    msg += "        .highlight { color: #e74c3c; font-weight: bold; }\r\n";
    msg += "        .services { background: #fff3cd; padding: 15px; border-radius: 8px; margin: 15px 0; border: 1px solid #ffeaa7; }\r\n";
    msg += "        .services h3 { color: #856404; margin-top: 0; }\r\n";
    msg += "    </style>\r\n";
    msg += "</head>\r\n";
    msg += "<body>\r\n";

    // Email container
    msg += "    <div class='email-container'>\r\n";

    // Header section with bordered company name
    msg += "        <div class='header'>\r\n";
    msg += "            <div class='company-name-border'>\r\n";
    msg += "                <div class='company-name'>SMART ELECTRONIQUE</div>\r\n";
    msg += "            </div>\r\n";
    msg += "            <div class='tagline'>Repair Shop - Your Trusted Electronics Partner</div>\r\n";
    msg += "        </div>\r\n";

    // Content section
    msg += "        <div class='content'>\r\n";
    msg += "            <div class='message'>\r\n";

    // Fix: Properly handle the body text with line breaks
    QString formattedBody = body;
    formattedBody.replace("\n", "<br>");
    msg += "                " + formattedBody + "\r\n";

    msg += "            </div>\r\n";

    // Services section
    msg += "            <div class='services'>\r\n";
    msg += "                <h3>🛠️ Our Services:</h3>\r\n";
    msg += "                • Smartphone & Tablet Repair<br>\r\n";
    msg += "                • Laptop & Computer Services<br>\r\n";
    msg += "                • TV & Home Electronics<br>\r\n";
    msg += "                • Gaming Console Repair<br>\r\n";
    msg += "                • Audio Equipment Service\r\n";
    msg += "            </div>\r\n";

    // Contact information
    msg += "            <div class='contact-info'>\r\n";
    msg += "                <strong>📞 Contact Us:</strong><br>\r\n";
    msg += "                Phone: <span class='highlight'>+216 98 952 656</span><br>\r\n";
    msg += "                Email: <span class='highlight'>contact@smartelectronique.com</span><br>\r\n";
    msg += "                Website: <span class='highlight'>www.smartelectronique.com</span><br>\r\n";
    msg += "                Address: Ariana, Tunis\r\n";
    msg += "            </div>\r\n";
    msg += "        </div>\r\n";

    // Footer section
    msg += "        <div class='footer'>\r\n";
    msg += "            Thank you for choosing <strong>SMART ELECTRONIQUE</strong><br>\r\n";
    msg += "            &copy; 2024 SMART ELECTRONIQUE Repair Shop. All rights reserved.\r\n";
    msg += "        </div>\r\n";
    msg += "    </div>\r\n";

    msg += "</body>\r\n";
    msg += "</html>\r\n";
    msg += "\r\n.\r\n"; // End of DATA command

    socket->write(msg.toUtf8());
    socket->waitForBytesWritten();
    socket->waitForReadyRead();
    qDebug() << socket->readAll();

    send("QUIT");
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
