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
    ui->widget_3->hide();
    ui->progressBar->setRange(0, 100);
    ui->widget_3->setStyleSheet("background:rgb(85, 170, 127)");
    QObject::connect(&t, &Timer::updateTime, this, &MultiQuestionPage::updateProgressBar);
}

MultiQuestionPage::~MultiQuestionPage()
{
    delete ui;
}

void MultiQuestionPage::showQuestion(const QJsonObject& question)
{
    this->t.start();

    row = question["row"].toInt();
    col = question["col"].toInt();
    QJsonArray options(question["answers"].toArray());
    QJsonObject option1(options[0].toObject());
    QJsonObject option2(options[1].toObject());
    QJsonObject option3(options[2].toObject());
    QJsonObject option4(options[3].toObject());
    QString Question(question["questionText"].toString());
    QString title(question["category"].toString());
    QString type(question["kind"].toString());
    QString op1(option1["text"].toString());
    QString op2(option2["text"].toString());
    QString op3(option3["text"].toString());
    QString op4(option4["text"].toString());
    ui->option_1->setText(op1);
    ui->option_2->setText(op2);
    ui->option_3->setText(op3);
    ui->option_4->setText(op4);
    ui->question->setText(Question);
    ui->title->setText(title);
    ui->type->setText(type);
}

void MultiQuestionPage::updateProgressBar(int time)
{
    ui->progressBar->setValue(time);
}

void MultiQuestionPage::on_submitButton_clicked()
{

    t.stop();

    QJsonObject req;
    req["title"] = "check";
    req["row"] = row;
    req["col"] = col;
    if (ui->option_1->isChecked())
        req["ans"] = 1;
    else if (ui->option_2->isChecked())
        req["ans"] = 2;
    else if (ui->option_3->isChecked())
        req["ans"] = 3;
    else if (ui->option_4->isChecked())
        req["ans"] = 4;
    else
        req["ans"] = 0;
    emit answer(req);
}

void MultiQuestionPage::showSkipWidget()
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

void MultiQuestionPage::hideSkipWidget()
{
    ui->widget_3->hide();
    ui->pushButton->setEnabled(false);
    // ui->widget->setEnabled(true);
    ui->widget_2->setEnabled(true);
    ui->widget_3->setEnabled(false);
    ui->submitButton->setEnabled(true);
    ui->skipButton->setEnabled(true);
}

void MultiQuestionPage::on_pushButton_clicked()
{
    hideSkipWidget();

}

void MultiQuestionPage::on_skipButton_clicked()
{
    QJsonObject req;
    req["title"] = "skip";
    req["row"] = row;
    req["col"] = col;
    emit skip(req);
}

void MultiQuestionPage::timeout()
{
    QJsonObject req;
    req["title"] = "timeout";
    req["row"] = row;
    req["col"] = col;
    emit timeoutSignal(req);
}
