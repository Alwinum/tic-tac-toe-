#ifndef SHORTQUESTIONPAGE_H
#define SHORTQUESTIONPAGE_H

#include <QDialog>

namespace Ui {
class ShortQuestionPage;
}

class ShortQuestionPage : public QDialog
{
    Q_OBJECT

public:
    explicit ShortQuestionPage(QWidget *parent = nullptr);
    ~ShortQuestionPage();

private:
    Ui::ShortQuestionPage *ui;
};

#endif // SHORTQUESTIONPAGE_H
