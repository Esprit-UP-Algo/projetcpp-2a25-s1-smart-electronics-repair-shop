#ifndef SMTP_H
#define SMTP_H

#include <QObject>
#include <QtNetwork/QSslSocket>

class Smtp : public QObject
{
    Q_OBJECT

public:
    explicit Smtp(QObject *parent = nullptr);

    void setUser(const QString &user);
    void setPassword(const QString &password);

    void sendMail(const QString &from,
                  const QString &to,
                  const QString &subject,
                  const QString &body);

private slots:
    void readyRead();

private:
    QSslSocket *socket;
    QString m_user;
    QString m_password;
};

#endif // SMTP_H
