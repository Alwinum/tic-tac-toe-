#ifndef NUMQUESTIONPAGE_H
#define NUMQUESTIONPAGE_H

#include <QDialog>

namespace Ui {
class NumQuestionPage;
}

class NumQuestionPage : public QDialog
{
    Q_OBJECT

public:
    explicit NumQuestionPage(QWidget *parent = nullptr);
    ~NumQuestionPage();

private:
    Ui::NumQuestionPage *ui;
};

#endif // NUMQUESTIONPAGE_H
