#ifndef CLIENT_H
#define CLIENT_H
#include <QTcpSocket>
#include <QFile>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QIODevice>
#include <QObject>
#include <QFileInfo>
#include "gamepage.h"
class Client : public QObject
{
    Q_OBJECT
public:
    Client(QJsonObject information);
    Client ();
    void sendQuestion (QJsonObject ans);
    GamePage gamePage;
    int skips;
    QString username;

public slots :
    void sendRequest (QJsonObject req);
    void handleAnswer ();
    void disconnect ();
    void saveChanges(QJsonObject ans);
signals :
    void sendData (QJsonObject req);
    void newMultipleQuestion (QJsonObject que);
    void newNumberQuestion (QJsonObject que);
    void newShortQuestion (QJsonObject que);
    void wonGame (QJsonObject ans);
    void lostGame (QJsonObject ans);
    void drawGame (QJsonObject ans);
    void introduce (QJsonObject req);
    void waiting();
    void endWait ();
    void cantSkip();
private :
    QTcpSocket* socket;
    int wins = 0;
    int losts = 0;
    int draws = 0;
    QJsonArray games;
};

#endif // CLIENT_H
