#ifndef MULTIQUESTIONPAGE_H
#define MULTIQUESTIONPAGE_H
#include "timer.h"

#include <QDialog>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>

namespace Ui {
class MultiQuestionPage;
}

class MultiQuestionPage : public QDialog
{
    Q_OBJECT

public:
    explicit MultiQuestionPage(QWidget *parent = nullptr);
    ~MultiQuestionPage();
    Timer t;

private:
    Ui::MultiQuestionPage *ui;
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

#endif // MULTIQUESTIONPAGE_H
