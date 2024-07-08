#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->setStyleSheet("background:rgb(108, 108, 108)");
    ui->loginButton->setStyleSheet("background:rgb(255, 170, 127)");
    ui->signupButton->setStyleSheet("background:rgb(255, 170, 127)");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
    emit openLoginPage();
}


void MainWindow::on_signupButton_clicked()
{
    emit openSignupPage();
}

