#ifndef NUMQUESTIONPAGE_H
#define NUMQUESTIONPAGE_H
#include "timer.h"

#include <QDialog>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>

namespace Ui {
class NumQuestionPage;
}

class NumQuestionPage : public QDialog
{
    Q_OBJECT

public:
    explicit NumQuestionPage(QWidget *parent = nullptr);
    ~NumQuestionPage();
    Timer t;

private:
    Ui::NumQuestionPage *ui;
    int row;
    int col;

public slots:
    void showQuestion(const QJsonObject& question);
    void updateProgressBar(int time);
    void on_submitButton_clicked();
    void on_pushButton_clicked();
    void on_skipButton_clicked();
    void showSkipWidget();
    void hideSkipWidget();
    void timeout();

signals:
    void answer(QJsonObject req);
    void skip(QJsonObject req);
    void timeoutSignal(QJsonObject req);



};

#endif // NUMQUESTIONPAGE_H
