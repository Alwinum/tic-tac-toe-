#include "shortquestionpage.h"
#include "ui_shortquestionpage.h"

ShortQuestionPage::ShortQuestionPage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ShortQuestionPage)
{
    ui->setupUi(this);
    ui->widget->setStyleSheet("background:rgb(108, 108, 108)");
    ui->widget_2->setStyleSheet("background:rgb(255, 170, 127)");
    ui->submitButton->setStyleSheet("background:rgb(255, 170, 127)");
    ui->skipButton->setStyleSheet("background:rgb(255, 170, 127)");
    ui->question->setStyleSheet("background:rgb(108, 108, 108)");
    ui->widget_3->hide();
    ui->widget_3->setStyleSheet("background:rgb(85, 170, 127)");
    QObject::connect(&t, &Timer::updateTime, this, &ShortQuestionPage::updateProgressBar);
}

ShortQuestionPage::~ShortQuestionPage()
{
    delete ui;
}

void ShortQuestionPage::showQuestion(const QJsonObject& question)
{
    t.start();
    row = question["row"].toInt();
    col = question["col"].toInt();
    QString Question(question["questionText"].toString());
    QString title(question["category"].toString());
    QString type(question["kind"].toString());
    ui->question->setText(Question);
    ui->title->setText(title);
    ui->type->setText(type);
}

void ShortQuestionPage::updateProgressBar(int time)
{
    ui->progressBar->setValue(time);
}

void ShortQuestionPage::on_submitButton_clicked()
{
    t.stop();

    QJsonObject req;
    req["title"] = "check";
    req["row"] = row;
    req["col"] = col;
    req["ans"] = ui->answer->text();
    emit answer(req);
}

void ShortQuestionPage::showSkipWidget()
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

void ShortQuestionPage::hideSkipWidget()
{
    ui->widget_3->hide();
    ui->pushButton->setEnabled(false);
    // ui->widget->setEnabled(true);
    ui->widget_2->setEnabled(true);
    ui->widget_3->setEnabled(false);
    ui->submitButton->setEnabled(true);
    ui->skipButton->setEnabled(true);
}

void ShortQuestionPage::on_pushButton_clicked()
{
    hideSkipWidget();
}

void ShortQuestionPage::on_skipButton_clicked()
{
    QJsonObject req;
    req["title"] = "skip";
    req["row"] = row;
    req["col"] = col;
    emit skip(req);
}

void ShortQuestionPage::timeout()
{
    QJsonObject req;
    req["title"] = "timeout";
    req["row"] = row;
    req["col"] = col;
    emit timeoutSignal(req);
}
