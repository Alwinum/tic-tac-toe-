#include "systemmanage.h"

systemManage::systemManage()
{
    this->c = new Client();
    w.show();


    QObject::connect(&this->c->gamePage, &GamePage::click, c, &Client::sendRequest);


    //show login & signup pages
    QObject::connect(&w, &MainWindow::openLoginPage, this, &systemManage::openLoginPage);
    QObject::connect(&w, &MainWindow::openLoginPage, this, &systemManage::closeMainWindow);
    QObject::connect(&w, &MainWindow::openSignupPage, this, &systemManage::openSignupPage);
    QObject::connect(&w, &MainWindow::openSignupPage, this, &systemManage::closeMainWindow);
    QObject::connect(&l, &LoginPage::openMainWindow, this, &systemManage::closeLoginPage);
    QObject::connect(&l, &LoginPage::openMainWindow, this, &systemManage::openMainWindow);
    QObject::connect(&s, &SignupPage::openMainWindow, this, &systemManage::closeSignupPage);
    QObject::connect(&s, &SignupPage::openMainWindow, this, &systemManage::openMainWindow);
    //check users info and send errors
    QObject::connect(&uI, &UsersInfo::sendSignupErrors, &s, &SignupPage::showErrors);
    QObject::connect(&uI, &UsersInfo::sendLoginErrors, &l, &LoginPage::showErrors);
    QObject::connect(this, &systemManage::sendSignupErrors, &s, &SignupPage::showErrors);
    QObject::connect(this, &systemManage::sendLoginErrors, &l, &LoginPage::showErrors);
    QObject::connect(&s, &SignupPage::checkInfo, &uI, &UsersInfo::checkSignedupInfo);
    QObject::connect(&l, &LoginPage::IsExist, &uI, &UsersInfo::IsExist);
    QObject::connect(&uI, &UsersInfo::openUserPage, this, &systemManage::closeLoginPage);
    QObject::connect(&uI, &UsersInfo::openUserPage, this, &systemManage::openUserPage);
    //show user info and show user page
    QObject::connect(&uP, &UserPage::openGamePage, this, &systemManage::openGamePage);
    QObject::connect(&uP, &UserPage::openGamePage, this, &systemManage::closeUserPage);
    QObject::connect(&uI, &UsersInfo::showUserInfo, &uP, &UserPage::showUserInfo);
    QObject::connect(&l, &LoginPage::showInfo, &uP, &UserPage::showUserInfo);
    //handling Widgets
    // QObject::connect(c, &Client::waiting, this, &systemManage::openUserPage);

    QEventLoop loop;
    QObject::connect(&uP, &UserPage::runGame, this, &systemManage::createNewClient);
    QObject::connect(&uP, &UserPage::runGame, &loop, &QEventLoop::quit);
    loop.exec();
    loop.quit();
    //Multiple Question
    QObject::connect(c, &Client::newMultipleQuestion, this, &systemManage::closeGamePage);
    QObject::connect(c, &Client::newMultipleQuestion, this, &systemManage::openMultiQuestionPage);
    QObject::connect(this, &systemManage::showMultiQuestion, &mQ, &MultiQuestionPage::showQuestion);
    QObject::connect(&mQ.t, &Timer::updateTime, &mQ, &MultiQuestionPage::updateProgressBar);
    QObject::connect(&mQ.t, &Timer::timeout, &mQ, &MultiQuestionPage::timeout);
    QObject::connect(&mQ, &MultiQuestionPage::answer, this, &systemManage::closeMultiQuestionPage);
    QObject::connect(&mQ, &MultiQuestionPage::answer, this, &systemManage::openGamePage);
    QObject::connect(&mQ, &MultiQuestionPage::timeoutSignal, this, &systemManage::closeMultiQuestionPage);
    QObject::connect(&mQ, &MultiQuestionPage::timeoutSignal, this, &systemManage::openGamePage);
    // NumQuestion
    QObject::connect(c, &Client::newNumberQuestion, this, &systemManage::closeGamePage);
    QObject::connect(c, &Client::newNumberQuestion, this, &systemManage::openNumQuestionPage);
    QObject::connect(this, &systemManage::showNumQuestion, &nQ, &NumQuestionPage::showQuestion);
    QObject::connect(&nQ.t, &Timer::updateTime, &nQ, &NumQuestionPage::updateProgressBar);
    QObject::connect(&nQ.t, &Timer::timeout, &nQ, &NumQuestionPage::timeout);
    QObject::connect(&nQ, &NumQuestionPage::answer, this, &systemManage::closeMultiQuestionPage);
    QObject::connect(&nQ, &NumQuestionPage::answer, this, &systemManage::openGamePage);
    QObject::connect(&nQ, &NumQuestionPage::timeoutSignal, this, &systemManage::closeMultiQuestionPage);
    QObject::connect(&nQ, &NumQuestionPage::timeoutSignal, this, &systemManage::openGamePage);
    //ShortQuestion
    QObject::connect(c, &Client::newShortQuestion, this, &systemManage::closeGamePage);
    QObject::connect(c, &Client::newShortQuestion, this, &systemManage::openShortQuestionPage);
    QObject::connect(this, &systemManage::showShortQuestion, &shQ, &ShortQuestionPage::showQuestion);
    QObject::connect(&t, &Timer::updateTime, &shQ, &ShortQuestionPage::updateProgressBar);
    QObject::connect(&shQ.t, &Timer::timeout, &shQ, &ShortQuestionPage::timeout);
    QObject::connect(&shQ, &ShortQuestionPage::answer, this, &systemManage::closeMultiQuestionPage);
    QObject::connect(&shQ, &ShortQuestionPage::answer, this, &systemManage::openGamePage);
    QObject::connect(&shQ, &ShortQuestionPage::timeoutSignal, this, &systemManage::closeMultiQuestionPage);
    QObject::connect(&shQ, &ShortQuestionPage::timeoutSignal, this, &systemManage::openGamePage);



    // send requests to client
    QObject::connect(&mQ, &MultiQuestionPage::answer, c, &Client::sendRequest);
    QObject::connect(&nQ, &NumQuestionPage::answer, c, &Client::sendRequest);
    QObject::connect(&shQ, &ShortQuestionPage::answer, c, &Client::sendRequest);
    QObject::connect(&mQ, &MultiQuestionPage::skip, c, &Client::sendRequest);
    QObject::connect(&nQ, &NumQuestionPage::skip, c, &Client::sendRequest);
    QObject::connect(&shQ, &ShortQuestionPage::skip, c, &Client::sendRequest);
    QObject::connect(&mQ, &MultiQuestionPage::timeoutSignal, c, &Client::sendRequest);
    QObject::connect(&shQ, &ShortQuestionPage::timeoutSignal, c, &Client::sendRequest);
    QObject::connect(&nQ, &NumQuestionPage::timeoutSignal, c, &Client::sendRequest);


    // waiting process
    QObject::connect(c, &Client::waiting, &uP, &UserPage::showWaitingWindow);
    QObject::connect(c, &Client::endWait, &uP, &UserPage::hideWaitingWindow);

    QObject::connect(c, &Client::endWait, this, &systemManage::closeUserPage);
    QObject::connect(c, &Client::endWait, this, &systemManage::openGamePage);

    // some shit
    QObject::connect(c, &Client::cantSkip, &mQ, &MultiQuestionPage::showSkipWidget);
    QObject::connect(c, &Client::cantSkip, &nQ, &NumQuestionPage::showSkipWidget);
    QObject::connect(c, &Client::cantSkip, &shQ, &ShortQuestionPage::showSkipWidget);
    QObject::connect(c, &Client::wonGame, &this->c->gamePage, &GamePage::showResultWidget);
    QObject::connect(c, &Client::lostGame, &this->c->gamePage, &GamePage::showResultWidget);
    QObject::connect(c, &Client::drawGame, &this->c->gamePage, &GamePage::showResultWidget);




}

void systemManage::openLoginPage()
{
    l.show();
    emit sendLoginErrors("");
}

void systemManage::openSignupPage()
{
    s.show();
    emit sendSignupErrors("");
}

void systemManage::openMainWindow()
{
    w.show();
}

void systemManage::openUserPage()
{
    qDebug() << "open user page called";
    uP.show();
}

void systemManage::openGamePage()
{
    this->c->gamePage.show();
}

void systemManage::openMultiQuestionPage(const QJsonObject& question)
{
    this->c->gamePage.close();
    mQ.show();
    // mQ.t = new Timer;
    // mQ.t.start();
    emit showMultiQuestion(question);
}

void systemManage::openShortQuestionPage(const QJsonObject& question)
{
    this->c->gamePage.close();
    shQ.show();
    // shQ.t = new Timer;
    // shQ.t.start();
    emit showShortQuestion(question);
}

void systemManage::openNumQuestionPage(const QJsonObject& question)
{
    this->c->gamePage.close();
    nQ.show();
    // nQ.t = new Timer;
    // nQ.t.start();
    emit showNumQuestion(question);
}

void systemManage::closeMultiQuestionPage()
{
    mQ.close();
    this->c->gamePage.show();
}

void systemManage::closeShortQuestionPage()
{
    shQ.close();
    this->c->gamePage.show();
}

void systemManage::closeNumQuestionPage()
{
    nQ.close();
    this->c->gamePage.show();

}
void systemManage::closeLoginPage()
{
    l.close();
}

void systemManage::closeSignupPage()
{
    s.close();
}

void systemManage::closeMainWindow()
{
    w.close();
}

void systemManage::closeUserPage()
{
    uP.close();
}

void systemManage::closeGamePage()
{
    this->c->gamePage.show();
}

void systemManage::createNewClient(QJsonObject information)
{
    delete this->c;
    this->c = new Client(information);
    qDebug() << "finished";
}
