#include "gamepage.h"
#include "ui_gamepage.h"

GamePage::GamePage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GamePage)
{
    ui->setupUi(this);
    ui->resultWidget->hide();
    ui->resultWidget->setStyleSheet("background:rgb(85, 170, 127)");
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

    buttons[{0, 0}] = ui->pushButton_1;
    buttons[{0, 1}] = ui->pushButton_2;
    buttons[{0, 2}] = ui->pushButton_3;
    buttons[{1, 0}] = ui->pushButton_4;
    buttons[{1, 1}] = ui->pushButton_5;
    buttons[{1, 2}] = ui->pushButton_6;
    buttons[{2, 0}] = ui->pushButton_7;
    buttons[{2, 1}] = ui->pushButton_8;
    buttons[{2, 2}] = ui->pushButton_9;




}

QJsonObject GamePage::makeClickRequest(int x, int y)
{
    QJsonObject req;
    req["title"] = "click";
    req["row"] = x;
    req["col"] = y;

    return req;
}

void GamePage::disableButton(int x, int y)
{
    // qDebug() << "function called";
    buttons[{x, y}]->setEnabled(false);
}

void GamePage::changeState(int x, int y, QString state)
{
    QPushButton* button = buttons[{x, y}];
    // حریف داره جواب میده
    if (state == "opponent Answering") {
        if (button->text() == "🔒") {

        }
        else
            button->setText("🗿");
    }
    // خونه رو من گرفتم
    else if (state == "won") {
        button->setText("🏆");
        disableButton(x, y);
    }
    // خونه قفل شده
    else if (state == "lock") {
        button->setText("🔒");
        disableButton(x, y);
    }
    // حریف خونه رو گرفته
    else if (state == "lost") {
        button->setText("🪦");
        disableButton(x, y);
    }
    // آزاد کردن خوونه
    else if (state == "change normal") {
        if (button->text() == "🔒") { }
        else {button->setText("🆓");}
    }

}

GamePage::~GamePage()
{
    delete ui;
}

void GamePage::showResultWidget(QJsonObject ans)
{
    ui->resultWidget->show();
    // ui->mainWidget->setEnabled(false);
    for (int i = 0; i < 3; i ++) {
        for (int j = 0; j < 3; j ++) {
            this->disableButton(i, j);
        }
    }
    ui->resultWidget->setEnabled(true);
    if (ans["result"].toString() == "won"){
        ui->result->setText("you won the game!");
    }
    else if (ans["result"].toString() == "lost"){
        ui->result->setText("you lost the game!");
    }
    else{
        ui->result->setText("the game is draw!");
    }
}
void GamePage::hideResultWidget()
{
    ui->resultWidget->hide();
    ui->mainWidget->setEnabled(true);
    ui->resultWidget->setEnabled(false);
}

void GamePage::on_pushButton_1_clicked()
{
    QJsonObject req = makeClickRequest(0, 0);
    qDebug() << req;
    emit this->click(req);
}

void GamePage::on_pushButton_2_clicked()
{
    QJsonObject req = makeClickRequest(0, 1);
    emit this->click(req);
}

void GamePage::on_pushButton_3_clicked()
{
    QJsonObject req = makeClickRequest(0, 2);
    emit this->click(req);
}

void GamePage::on_pushButton_4_clicked()
{
    QJsonObject req = makeClickRequest(1, 0);
    emit this->click(req);
}

void GamePage::on_pushButton_5_clicked()
{
    QJsonObject req = makeClickRequest(1, 1);
    emit this->click(req);
}

void GamePage::on_pushButton_6_clicked()
{
    QJsonObject req = makeClickRequest(1, 2);
    emit this->click(req);
}

void GamePage::on_pushButton_7_clicked()
{
    QJsonObject req = makeClickRequest(2, 0);
    emit this->click(req);
}

void GamePage::on_pushButton_8_clicked()
{
    QJsonObject req = makeClickRequest(2, 1);
    emit this->click(req);
}

void GamePage::on_pushButton_9_clicked()
{
    QJsonObject req = makeClickRequest(2, 2);
    emit this->click(req);
}

void GamePage::on_pushButton_clicked()
{
    hideResultWidget();
}

