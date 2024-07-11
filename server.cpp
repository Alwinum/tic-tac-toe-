#include "server.h"

Server::Server(QObject *parent)
    : QObject{parent}
{
    // this->server = new QTcpServer ();

    connect(&server, &QTcpServer::newConnection, this, &Server::newConnection);
}

void Server::start()
{
    if (!this->server.listen(QHostAddress::Any, 5555)) {
        qDebug () << "Server is not listening\n";
        return;
    }
    qDebug() << "waiting for new client connection ... ";
}

void Server::newConnection ()
{
    qDebug () << "-Handling the new connection-";
    QTcpSocket* socket = this->server.nextPendingConnection();
    qDebug() << "Client Found ---";

    // QObject::connect(socket, &QTcpSocket::readyread, this, &Server::)
        // giveID (socket);
    que.push_back(socket);
    if (que.size() == 2) {
        qDebug() << "game Started";
        Game *game = new Game(que[0], que[1]);
        // games.push_back(game);
        game->start();
    }
    else {
        QJsonObject ans;
        ans["name"] =  "wait";
        QJsonDocument document(ans);
        QByteArray datum = document.toJson();
        socket->write(datum);
        socket->waitForBytesWritten();
    }

}


// void Server::giveID(QTcpSocket* socket)
// {
//     // socket->write(QString::number(this->lastGivenID));
//     // socket->flush();
//     int numberToSend = ++this->lastGivenID;
//     QByteArray data;
//     QDataStream stream(&data, QIODevice::WriteOnly);
//     stream << numberToSend;

//     socket->write(data);
//     socket->waitForBytesWritten();
// }
