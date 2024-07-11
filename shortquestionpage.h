#ifndef SHORTQUESTIONPAGE_H
#define SHORTQUESTIONPAGE_H
#include "timer.h"

#include <QDialog>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>

namespace Ui {
class ShortQuestionPage;
}

class ShortQuestionPage : public QDialog
{
    Q_OBJECT

public:
    explicit ShortQuestionPage(QWidget *parent = nullptr);
    ~ShortQuestionPage();
    Timer t;

private:
    Ui::ShortQuestionPage *ui;
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

#endif // SHORTQUESTIONPAGE_H
