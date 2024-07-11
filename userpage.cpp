#include "userpage.h"
#include "ui_userpage.h"

UserPage::UserPage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UserPage)
{
    ui->setupUi(this);
    ui->background1->setStyleSheet("background:rgb(218, 123, 59)");
    ui->background2->setStyleSheet("background:rgb(255, 170, 127)");
    ui->background3->setStyleSheet("background:rgb(218, 123, 59)");
    ui->background4->setStyleSheet("background:rgb(108, 108, 108)");
    ui->runGameButton->setStyleSheet("background:rgb(255, 170, 127)");
    ui->widget->setStyleSheet("background:rgb(85, 170, 127)");
    QJsonObject obj;
    obj["me"] = "------------";
    obj["opponent"] = "------------";
    obj["winner"] = "------------";
    lastGames.append(obj);
    lastGames.append(obj);
    lastGames.append(obj);
    ui->widget->hide();
}

UserPage::~UserPage()
{
    delete ui;
}

void UserPage::showUserInfo(QJsonObject user)
{
    qDebug() << "--------- " << user;
    information = user;
    QFile info("D:\\"+information["username"].toString()+".json");
    info.open(QIODevice::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromJson(info.readAll());
    QJsonArray games = doc["games"].toArray();
    for (int i=games.size()-1,j=0 ; i>=0 && j<3 ; i--,j++){
        lastGames[j] = games[i];
    }
    qDebug() << "00000\n";
    ui->username->setText(information["username"].toString());
    ui->email->setText(information["email"].toString());
    ui->win->setText(doc["won"].toString());
    ui->lost->setText(doc["lost"].toString());
    ui->draw->setText(doc["draw"].toString());
    ui->player1_1->setText(lastGames[0].toObject()["me"].toString());
    ui->player1_2->setText(lastGames[0].toObject()["opponent"].toString());
    ui->winner1->setText(lastGames[0].toObject()["winner"].toString());
    ui->player2_1->setText(lastGames[1].toObject()["me"].toString());
    ui->player2_2->setText(lastGames[1].toObject()["opponent"].toString());
    ui->winner2->setText(lastGames[1].toObject()["winner"].toString());
    ui->player3_1->setText(lastGames[2].toObject()["me"].toString());
    ui->player3_2->setText(lastGames[2].toObject()["opponent"].toString());
    ui->winner3->setText(lastGames[2].toObject()["winner"].toString());
}


void UserPage::on_runGameButton_clicked()
{
    emit runGame(information);
    // emit openGamePage();
}

void UserPage::hideWaitingWindow()
{
    ui->widget->hide();
    ui->widget_2->setEnabled(true);
    ui->widget->setEnabled(false);
}

void UserPage::showWaitingWindow()
{
    // qDebug() << "called";
    ui->widget_2->setEnabled(false);
    ui->widget->setEnabled(true);
    ui->widget->show();
    ui->runGameButton->setEnabled(false);
}
