#ifndef SYSTEMMANAGE_H
#define SYSTEMMANAGE_H

#include <QObject>
#include <QEventLoop>
#include "usersinfo.h"
#include "mainwindow.h"
#include "userpage.h"
#include "gamepage.h"
#include "multiquestionpage.h"
#include "shortquestionpage.h"
#include "numquestionpage.h"
#include "client.h"

class systemManage : public QObject
{
    Q_OBJECT
private:
    LoginPage l;
    SignupPage s;
    UsersInfo uI;
    MainWindow w;
    UserPage uP;
    GamePage g;
    MultiQuestionPage mQ;
    ShortQuestionPage shQ;
    NumQuestionPage nQ;
    Timer t;
    Client *c;

public:
    systemManage();
private slots:
    void openLoginPage();
    void openSignupPage();
    void openMainWindow();
    void openUserPage();
    void openGamePage();
    void openMultiQuestionPage(const QJsonObject& question);
    void openShortQuestionPage(const QJsonObject& question);
    void openNumQuestionPage(const QJsonObject& question);
    void closeLoginPage();
    void closeSignupPage();
    void closeMainWindow();
    void closeUserPage();
    void closeGamePage();
    void createNewClient(QJsonObject information);
    void closeMultiQuestionPage ();
    void closeNumQuestionPage();
    void closeShortQuestionPage();
signals:
    void sendSignupErrors(QString error);
    void sendLoginErrors(QString error);
    void showMultiQuestion(const QJsonObject& question);
    void showShortQuestion(const QJsonObject& question);
    void showNumQuestion(const QJsonObject& question);
    void hideWatingWindow();
};

#endif // SYSTEMMANAGE_H
