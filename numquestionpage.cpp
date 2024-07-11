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
    ui->widget_3->hide();
    ui->widget_3->setStyleSheet("background:rgb(85, 170, 127)");
    QObject::connect(&t, &Timer::updateTime, this, &NumQuestionPage::updateProgressBar);
}

NumQuestionPage::~NumQuestionPage()
{
    delete ui;
}

void NumQuestionPage::showQuestion(const QJsonObject& question)
{
    this->t.start();
    row = question["row"].toInt();
    col = question["col"].toInt();
    QString Question(question["questionText"].toString());
    QString title(question["category"].toString());
    QString type(question["kind"].toString());
    ui->question->setText(Question);
    ui->title->setText(title);
    ui->type->setText(type);
}

void NumQuestionPage::updateProgressBar(int time)
{
    ui->progressBar->setValue(time);
}


void NumQuestionPage::on_submitButton_clicked()
{
    t.stop();
    QJsonObject req;
    req["title"] = "check";
    req["row"] = row;
    req["col"] = col;
    req["ans"] = ui->spinBox->value();
    emit answer(req);
}

void NumQuestionPage::showSkipWidget()
{

    ui->widget_3->show();
    ui->pushButton->setEnabled(true);
    // ui->widget->setEnabled(false);
    ui->submitButton->setEnabled(false);
    ui->skipButton->setEnabled(false);
    ui->widget_2->setEnabled(false);
    ui->widget_3->setEnabled(true);
    ui->pushButton->setEnabled(true);
}

void NumQuestionPage::hideSkipWidget()
{
    ui->widget_3->hide();
    ui->pushButton->setEnabled(false);
    // ui->widget->setEnabled(true);
    ui->widget_2->setEnabled(true);
    ui->widget_3->setEnabled(false);
    ui->submitButton->setEnabled(true);
    ui->skipButton->setEnabled(true);

}

void NumQuestionPage::on_pushButton_clicked()
{
    hideSkipWidget();
}

void NumQuestionPage::on_skipButton_clicked()
{
    QJsonObject req;
    req["title"] = "skip";
    req["row"] = row;
    req["col"] = col;
    emit skip(req);
}

void NumQuestionPage::timeout()
{
    QJsonObject req;
    req["title"] = "timeout";
    req["row"] = row;
    req["col"] = col;
    emit timeoutSignal(req);
}
