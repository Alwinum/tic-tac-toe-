#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QDebug>
#include <QCoreApplication>
#include <QObject>
#include <QApplication>
#include <QCoreApplication>
#include "server.h"
// #include "gameboard.h"
// #include "questionfactory.h"
// #include "requestsender.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    // GameBoard game;
    // for (int i = 0 ;i < 3; i ++) {
    //     for (int j = 0; j < 3; j ++) {
    //         qDebug() << i << " " << j;
    //         qDebug() << game.getKind(i, j);
    //         qDebug() << "\n\n";
    //     }
    // }
    // qDebug() << game.getObject(1, 1);
    Server server;

    server.start();
    // QuestionFactory fac;
    // fac.sendRequest("multiple");
    // fac.getObject();
    // fac.getQuestion();
    // MultipleChoiceQuestion* multi = dynamic_cast<MultipleChoiceQuestion*>(fac.getQuestion());
    // qDebug() << multi->getAnswer();
    // qDebug() << fac.getObject();
    // RequestSender req;
    // QJsonObject ans;
    // req.sendRequest("multiple");
    // qDebug() << "s;flja";
    // qDebug() << req.que;
    // qDebug () << ans;
    return a.exec();
}
