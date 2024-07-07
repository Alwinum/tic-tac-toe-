#include "numquestionpage.h"
#include "ui_numquestionpage.h"

NumQuestionPage::NumQuestionPage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NumQuestionPage)
{
    ui->setupUi(this);
    ui->widget->setStyleSheet("background:rgb(108, 108, 108)");
    ui->widget_2->setStyleSheet("background:rgb(255, 170, 127)");
    ui->submitButton->setStyleSheet("background:rgb(255, 170, 127)");
    ui->skipButton->setStyleSheet("background:rgb(255, 170, 127)");
    ui->question->setStyleSheet("background:rgb(108, 108, 108)");
}

NumQuestionPage::~NumQuestionPage()
{
    delete ui;
}
