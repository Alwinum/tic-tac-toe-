#ifndef MULTIQUESTIONPAGE_H
#define MULTIQUESTIONPAGE_H

#include <QDialog>

namespace Ui {
class MultiQuestionPage;
}

class MultiQuestionPage : public QDialog
{
    Q_OBJECT

public:
    explicit MultiQuestionPage(QWidget *parent = nullptr);
    ~MultiQuestionPage();

private:
    Ui::MultiQuestionPage *ui;
};

#endif // MULTIQUESTIONPAGE_H
