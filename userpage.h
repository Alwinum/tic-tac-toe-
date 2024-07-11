#ifndef USERPAGE_H
#define USERPAGE_H

#include <QDialog>
#include <QObject>
#include <QFile>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QIODevice>
#include <QString>


namespace Ui {
class UserPage;
}

class UserPage : public QDialog
{
    Q_OBJECT

public:
    explicit UserPage(QWidget *parent = nullptr);
    ~UserPage();

signals:
    void openGamePage();
    void runGame(QJsonObject info);
private:
    Ui::UserPage *ui;
    QJsonObject information;
    QJsonArray lastGames;
public slots:
    void showUserInfo(QJsonObject user);
    void hideWaitingWindow();
    void showWaitingWindow();
private slots:
    void on_runGameButton_clicked();
};

#endif // USERPAGE_H
