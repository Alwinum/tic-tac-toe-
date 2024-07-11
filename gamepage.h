#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QDialog>
#include <QJsonObject>
#include <map>
// using namespace std;
namespace Ui {
class GamePage;
}

class GamePage : public QDialog
{
    Q_OBJECT

public:
    explicit GamePage(QWidget *parent = nullptr);
    QJsonObject makeClickRequest (int x, int y);
    void disableButton (int x, int y);
    void changeState (int x, int y, QString state);
    void newQuestion (QJsonObject question);
    ~GamePage();


signals :
    void click(QJsonObject req);
    void newMultipleQuestion (QJsonObject que);
    void newNumberQuestion (QJsonObject que);
    void newShortQuestion (QJsonObject que);
private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_clicked();
public slots:
    void showResultWidget(QJsonObject ans);
    void hideResultWidget();
private:
    Ui::GamePage *ui;
    std::map<std::pair<int,int>, QPushButton*> buttons;
};

#endif // GAMEPAGE_H
