#ifndef SIGNUPPAGE_H
#define SIGNUPPAGE_H

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
class SignupPage;
}

class SignupPage : public QDialog
{
    Q_OBJECT

public:
    explicit SignupPage(QWidget *parent = nullptr);
    ~SignupPage();

public slots:
    void on_signupPushButton_clicked();
    void showErrors(QString error);
signals:
    void checkInfo(const QString &username,const QString &password,const QString &email);
    void openMainWindow();

private slots:
    void on_backButton_clicked();

private:
    Ui::SignupPage *ui;
};

#endif // SIGNUPPAGE_H
