#include "gamepage.h"
#include "ui_gamepage.h"

GamePage::GamePage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GamePage)
{
    ui->setupUi(this);
    ui->mainWidget->setStyleSheet("background:rgb(108, 108, 108)");
    ui->pushButton_1->setStyleSheet("background:rgb(255, 170, 127)");
    ui->pushButton_2->setStyleSheet("background:rgb(255, 170, 127)");
    ui->pushButton_3->setStyleSheet("background:rgb(255, 170, 127)");
    ui->pushButton_4->setStyleSheet("background:rgb(255, 170, 127)");
    ui->pushButton_5->setStyleSheet("background:rgb(255, 170, 127)");
    ui->pushButton_6->setStyleSheet("background:rgb(255, 170, 127)");
    ui->pushButton_7->setStyleSheet("background:rgb(255, 170, 127)");
    ui->pushButton_8->setStyleSheet("background:rgb(255, 170, 127)");
    ui->pushButton_9->setStyleSheet("background:rgb(255, 170, 127)");
}

GamePage::~GamePage()
{
    delete ui;
}
