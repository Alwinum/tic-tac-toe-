#include "usersinfo.h"

UsersInfo::UsersInfo()
{
    QFile myFile("D:\\info.json");
    myFile.open(QIODevice::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromJson(myFile.readAll());
    usersInfo = doc["users"].toArray();
    users = usersInfo.size();
    for (int i = 0; i < usersInfo.size(); i ++) {
        qDebug() << usersInfo[i].toObject()["username"].toString() << usersInfo[i].toObject()["password"].toString();
    }
    myFile.close();

}

void UsersInfo::checkSignedupInfo(const QString &username,const QString& password,const QString& email)
{
    qDebug()<<"uhlh";
    int newMember = 1;
    if(!IsValidPass(password)){
        newMember = 0;
        emit sendSignupErrors("invalid password!");
    }
    if (username.length() < 4){
        newMember = 0;
        emit sendSignupErrors("username is not long enough");
    }
    for (int i=0 ; i<usersInfo.size() ; i++){
        QJsonObject obj(usersInfo[i].toObject());
        if (email == obj["email"].toString()){
            newMember = 0;
            emit sendSignupErrors("this email already exists!");
        }
        if(username == obj["username"].toString()){
            newMember = 0;
            emit sendSignupErrors("this username is already tooken");
        }
    }
    if(newMember == 1){
        emit sendSignupErrors("account created successfully");
        QFile myFile("D:\\info.json");
        myFile.open(QIODevice::WriteOnly);
        QJsonObject newObject;
        newObject["username"] = username;
        newObject["password"] = password;
        newObject["email"] = email;
        usersInfo.append(newObject);
        users++;
        QJsonObject emptyObject;
        QJsonDocument emptyDoc(emptyObject);
        myFile.write(emptyDoc.toJson());
        myFile.close();
        myFile.open(QIODevice::WriteOnly);
        QJsonObject newUsers;
        newUsers["users"] = usersInfo;
        QJsonDocument doc2(newUsers);
        myFile.write(doc2.toJson());
        myFile.close();
    }
}

bool IsValidPass(QString pass)
{
    std::string password = pass.toStdString();
    int num = 0;
    int character = 0;
    if (password.length() <8)
        return false;
    for (int i=0 ; i < password.length() ; i++){
        if(password[i]>=65 && password[i]<=90)
            character++;
        else if(password[i]>=97 && password[i]<=122)
            character++;
        else if(password[i]>=48 && password[i]<=57)
            num++;
    }
    if(num==0 || character==0)
        return false;
    return true;
}

void UsersInfo::IsExist(QString username, QString pass)
{
    int check = 0;
    for (int i=0 ; i<usersInfo.size() ; i++){
        QJsonObject obj = usersInfo[i].toObject();
        if (obj["username"].toString() == username && obj["password"].toString() == pass){
            emit openUserPage();
            emit showUserInfo(obj);
            check = 1;
            break;
        }
    }
    if (!check)
        emit sendLoginErrors("you havn't an account yet! \nplease signup");
}
