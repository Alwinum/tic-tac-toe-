#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QDialog>
#include <QObject>
#include <QFile>
#include <QString>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

namespace Ui {
class LoginPage;
}

class LoginPage : public QDialog
{
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = nullptr);
    ~LoginPage();

public slots:
    void on_backButton_clicked();
    void on_loginPushButton_clicked();
    void showErrors(QString error);

private:
    Ui::LoginPage *ui;
signals:
    void IsExist(QString username, QString pass);
    void openUserPage();
    void showInfo(QJsonObject user);
    void openMainWindow();
};

#endif // LOGINPAGE_H
