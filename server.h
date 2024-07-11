#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <vector>
#include "game.h"
using namespace std;
class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    void start ();
private :
    // int lastGivenID ;
    vector<QTcpSocket*> que;
    // vector<QTcpSocket*> vec;
    // vector<Game*> games;
    QTcpServer server;
public slots :
    void newConnection ();
    // void matchConnection ();
    // void giveID (QTcpSocket* socket);

signals:

};

#endif // SERVER_H
