#ifndef USERSINFO_H
#define USERSINFO_H

#include "loginpage.h"
#include "signuppage.h"
#include <QString>
#include <QFile>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QIODevice>
#include <QDebug>
#include <QObject>

class UsersInfo : public QObject
{
    Q_OBJECT
public:
    UsersInfo();
    void IsExist(QString username, QString pass);
private:
    int users=0;
    QJsonArray usersInfo;
public slots:
    void checkSignedupInfo(const QString &username,const QString& password,const QString& email);
signals:
    void sendSignupErrors(QString error);
    void sendLoginErrors(QString error);
    void openUserPage();
    void showUserInfo(QJsonObject user);
};

bool IsValidPass(QString pass);

#endif // USERSINFO_H
