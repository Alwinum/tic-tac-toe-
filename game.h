#ifndef GAME_H
#define GAME_H
#include <QThread>
#include "gameboard.h"
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
class Game : public QThread
{
    Q_OBJECT
public:
    Game(QTcpSocket* one, QTcpSocket* two);
    void run () override;
    std::pair<QJsonObject, QJsonObject> correctAnswer (int x, int y, int self, int opponent);
    std::pair<QJsonObject, QJsonObject> wrongAnswer (int x, int y, int self, int opponent);
    void handleRequest(QTcpSocket* player, QTcpSocket* enemy, int self, int opponent);
    bool checkDraw ();
    ~Game ();
    // int winner = 0;

private :
    GameBoard board;
    QTcpSocket* playerOne;
    QTcpSocket* playerTwo;
    QString userOne;
    QString userTwo;

private slots:
    void playerOneWins ();
    void playerTwoWins ();
    void playerOneReq ();
    void playerTwoReq ();

};

#endif // GAME_H
