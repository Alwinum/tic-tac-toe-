#include "client.h"

Client::Client(QJsonObject information) {

    this->username = information["username"].toString();
    qDebug() << "USERERERE : " << this->username;
    this->skips = 2;
    // this->gamePage.show();
    this->socket = new QTcpSocket();
    socket->connectToHost("127.0.0.1", 5555);
    socket->waitForConnected(-1);
    qDebug() << "connected";
    QObject::connect(this->socket, &QTcpSocket::disconnected, this, &Client::disconnect);
    QObject::connect(this, &Client::sendData, this, &Client::sendRequest);
    QObject::connect(this->socket, &QTcpSocket::readyRead, this, &Client::handleAnswer);
    QObject::connect(&this->gamePage, &GamePage::click, this, &Client::sendRequest);
    QObject::connect(this, &Client::introduce, this, &Client::sendRequest);
    QObject::connect(this, &Client::wonGame, this, &Client::saveChanges);
    QObject::connect(this, &Client::lostGame, this, &Client::saveChanges);
    QObject::connect(this, &Client::drawGame, this, &Client::saveChanges);

    QFileInfo myGames("D:\\"+username+".json");
    if (myGames.exists() && myGames.isFile()){
        QFile info("D:\\"+username+".json");
        info.open(QIODevice::ReadOnly);
        QJsonDocument doc = QJsonDocument::fromJson(info.readAll());
        wins = doc["win"].toInt();
        losts = doc["lost"].toInt();
        draws = doc["draw"].toInt();
        games = doc["games"].toArray();
    }
}

Client::Client()
{
    this->username = "empty";
}

void Client:: sendRequest (QJsonObject req) {
    if (req["title"].toString()=="skip" && skips == 0){
        emit cantSkip();
        return ;
    }
    qDebug() << req << "\n";
    QJsonDocument doc(req);
    QByteArray data = doc.toJson();
    socket->write(data);
    socket->waitForBytesWritten();
    qDebug() << "writing ended";

}

void Client::sendQuestion (QJsonObject ans)
{
    if (ans["type"].toString() == "multiple") {
        qDebug() << "emitted multiple question";
        emit this->newMultipleQuestion(ans);
    }
    else if (ans["type"].toString() == "short") {
        emit this->newShortQuestion(ans);
    }
    else if (ans["type"].toString() == "number") {
        emit this->newNumberQuestion(ans);
    }
}

void Client::handleAnswer ()
{
    // QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    // if (socket) {
    QByteArray data1 = socket->readAll();
    QJsonDocument doc1 = QJsonDocument::fromJson(data1);
    QJsonObject ans = doc1.object();

    qDebug() << ans << "\n";
    // معرفی اسم حریف

    // حریف سوالش رو اسکیپ کرد
    if (ans["name"].toString() == "opponent skip question") {
        // هیچکاری نباید بکنه
    }
    // حریف در حال جواب دادن به سوال میباشد
    else if (ans["name"].toString() == "opponent answering") {
        gamePage.changeState(ans["row"].toInt(), ans["col"].toInt(), "opponent Answering");
    }
    // نتیجه جواب خودم به سوال اومده
    else if (ans["name"].toString() == "question answer") {
        if (ans["won"].toBool()) {
            emit wonGame(ans);
        }
        else if (ans["lost"].toBool()) {
            emit lostGame (ans);
        }
        else if (ans["correct"].toBool() == true) {
            gamePage.changeState(ans["row"].toInt(), ans["col"].toInt(), "won");
        }
        else if (ans["correct"].toBool() == false) {
            gamePage.changeState(ans["row"].toInt(), ans["col"].toInt(), "lock");
        }
    }
    // نتیجه جواب حریف به یک سوال اومده
    else if (ans["name"].toString() == "opponent question answer") {
        if(ans["result"].toString() == "nothing") {
            qDebug() << "heree";
            if(ans["correct"].toBool()) {
                gamePage.changeState(ans["row"].toInt(), ans["col"].toInt(), "lost");
            }
            else {
                qDebug() << "answer was not correct for opponent";
                gamePage.changeState(ans["row"].toInt(), ans["col"].toInt(), "change normal");
            }
        }
        else if (ans["result"].toString() == "won") {
            emit wonGame (ans);
        }
        else if (ans["result"].toString() == "lost") {
            emit lostGame(ans);
        }
    }
    // سوال جدید برای کاربر ارسال شده
    else if (ans["name"].toString() == "new question") {
        qDebug() << "new Question";
        qDebug () << ans;
        if (ans["Allowed"].toBool()) {
            sendQuestion(ans);
        }
        else {
            // هیچکاری نکن
        }
    }
    // نتیجه بازی اعلام شده
    else if (ans["name"] == "game result") {
        if (ans["result"].toString() == "won") {
            emit wonGame(ans);
        }
        else if(ans["result"].toString() == "lost") {
            emit lostGame(ans);
        }
        else if (ans["result"].toString() == "draw") {
            emit drawGame (ans);
        }
    }
    // اسکیپ کردن سوال
    else if (ans["name"].toString() == "skip question") {
        if (skips != 0) {
            sendQuestion(ans);
            this->skips--;
        }
        else {
            // کاربر امکان رد کردن سوال رو نداره
        }
    }
    else if (ans["name"].toString() == "wait") {
        qDebug() << "emiting wait signal";
        emit waiting();
    }
    else if (ans["name"].toString() == "game started") {
        qDebug () << "introducing";
        QJsonObject req;
        req["title"] = "introduction";
        req["username"] = this->username;
        qDebug() << req;
        QJsonDocument doc2(req);
        QByteArray data2 = doc2.toJson();
        socket->write(data2);
        socket->waitForBytesWritten();
        // emit introduce(req);
        emit endWait();
    }
}

void Client::saveChanges(QJsonObject ans)
{
    if (ans["result"].toString() == "won"){
        wins++;
        QJsonObject obj;
        obj["me"] = username;
        obj["opponent"] = ans["opponent"].toString();
        obj["winner"] = username;
        games.append(obj);
    }
    else if (ans["result"].toString() == "lost"){
        losts++;
        QJsonObject obj;
        obj["me"] = username;
        obj["opponent"] = ans["opponent"].toString();
        obj["winner"] = ans["opponent"].toString();
        games.append(obj);
    }
    else{
        draws++;
        QJsonObject obj;
        obj["me"] = username;
        obj["opponent"] = ans["opponent"].toString();
        obj["winner"] = "---";
        games.append(obj);
    }
    QJsonObject changes;
    changes["won"] = wins;
    changes["lost"] = losts;
    changes["draw"] = draws;
    changes["games"] = games;
    QJsonDocument doc3(changes);
    QFile info("D:\\"+username+".json");
    info.open(QIODevice::WriteOnly);
    info.write(doc3.toJson());
}

void Client::disconnect()
{
    QJsonObject res;
    res["opponent"] = "bad connection";
    emit lostGame(res);
    qDebug () << "Disconnected from the server";
}

