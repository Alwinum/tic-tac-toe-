#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QDialog>

namespace Ui {
class GamePage;
}

class GamePage : public QDialog
{
    Q_OBJECT

public:
    explicit GamePage(QWidget *parent = nullptr);
    ~GamePage();

private:
    Ui::GamePage *ui;
};

#endif // GAMEPAGE_H
