#include "loginpage.h"
#include "ui_loginpage.h"

LoginPage::LoginPage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginPage)
{
    ui->setupUi(this);
    ui->background_2->setStyleSheet("background:rgb(255, 170, 127)");
    ui->background->setStyleSheet("background:rgb(108, 108, 108)");
    ui->username->setStyleSheet("background:rgb(255, 170, 127)");
    ui->password->setStyleSheet("background:rgb(255, 170, 127)");
    ui->loginPushButton->setStyleSheet("background:rgb(108, 108, 108)");
    ui->erorrTextEdit->setStyleSheet("background:rgb(108, 108, 108)");
    ui->backButton->setStyleSheet("background:rgb(255, 170, 127)");
}

LoginPage::~LoginPage()
{
    delete ui;
}

void LoginPage::on_backButton_clicked()
{
    emit openMainWindow();
}


void LoginPage::on_loginPushButton_clicked()
{
    QString username = ui->username->text();
    QString password = ui->password->text();
    emit IsExist(username,password);
}

void LoginPage::showErrors(QString error)
{
    ui->erorrTextEdit->setText(error);
}
