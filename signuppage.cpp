#include "signuppage.h"
#include "ui_signuppage.h"

SignupPage::SignupPage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SignupPage)
{
    ui->setupUi(this);
    ui->background_2->setStyleSheet("background:rgb(255, 170, 127)");
    ui->background->setStyleSheet("background:rgb(108, 108, 108)");
    ui->erorrTextEdit->setStyleSheet("background:rgb(108, 108, 108)");
    ui->username->setStyleSheet("background:rgb(255, 170, 127)");
    ui->password->setStyleSheet("background:rgb(255, 170, 127)");
    ui->email->setStyleSheet("background:rgb(255, 170, 127)");
    ui->signupPushButton->setStyleSheet("background:rgb(108, 108, 108)");
    ui->backButton->setStyleSheet("background:rgb(255, 170, 127)");
}

SignupPage::~SignupPage()
{
    delete ui;
}

void SignupPage::on_signupPushButton_clicked()
{
    qDebug() << "clicked";
    QString username = ui->username->text();
    QString password = ui->password->text();
    QString email = ui->email->text();
    qDebug() << "going to emit";
    emit checkInfo(username,password,email);
    qDebug() << "signal emited";

}

void SignupPage::showErrors(QString error)
{
    ui->erorrTextEdit->setText(error);
}

void SignupPage::on_backButton_clicked()
{
    emit openMainWindow();
}

