#include "multiquestionpage.h"
#include "ui_multiquestionpage.h"

MultiQuestionPage::MultiQuestionPage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MultiQuestionPage)
{
    ui->setupUi(this);
    ui->widget->setStyleSheet("background:rgb(108, 108, 108)");
    ui->widget_2->setStyleSheet("background:rgb(255, 170, 127)");
    ui->submitButton->setStyleSheet("background:rgb(255, 170, 127)");
    ui->skipButton->setStyleSheet("background:rgb(255, 170, 127)");
    ui->question->setStyleSheet("background:rgb(108, 108, 108)");
}

MultiQuestionPage::~MultiQuestionPage()
{
    delete ui;
}
