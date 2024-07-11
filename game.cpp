#include "game.h"
#include "multiplechoicequestion.h"

Game::Game(QTcpSocket* one, QTcpSocket* two) {

    // for (int i = 0 ;i < 3; i ++) {
    //     for (int j = 0; j < 3; j ++) {
    //         qDebug() << i << " " << j;
    //         qDebug() << board.getKind(i, j);
    //         qDebug() << board.getObject(i, j);
    //         qDebug() << "\n";
    //     }
    // }
    qDebug() << "Entered this fucking game";

    QJsonObject ans;
    ans["name"] = "game started";
    this->playerOne = one;
    this->playerTwo = two;
    QJsonDocument document(ans);
    QByteArray datum = document.toJson();
    playerOne->write(datum);
    playerOne->waitForBytesWritten();
    QObject::connect(playerOne, &QTcpSocket::disconnected, this, &Game::playerTwoWins);
    QObject::connect(playerTwo, &QTcpSocket::disconnected, this, &Game::playerOneWins);
    playerTwo->write(datum);
    playerTwo->waitForBytesWritten();


}

void Game::run ()
{
    QObject::connect(playerOne, &QTcpSocket::readyRead, this, &Game::playerOneReq);
    QObject::connect(playerTwo, &QTcpSocket::readyRead, this, &Game::playerTwoReq);
}

std::pair<QJsonObject, QJsonObject> Game::correctAnswer (int x, int y, int self, int opponent)
{
    QJsonObject ans;
    QJsonObject res;
    board.setState(x, y, self);
    ans["name"] = "question answer";
    ans["correct"] = true;
    ans["row"] = x;
    ans["col"] = y;
    ans["result"] = "nothing";

    res["name"] = "opponent question answer";
    res["correct"] = true;
    res["row"] = x;
    res["col"] = y;
    res["result"] = "nothing";
    board.setState(x, y, self);
    if (board.getType(x, y) == "won") {
        ans["result"] = "won";
        res["result"] = "lost";
    }

    return {ans, res};
}

std::pair<QJsonObject, QJsonObject> Game::wrongAnswer (int x, int y, int self, int opponent)
{
    QJsonObject ans;
    QJsonObject res;
    board.setState(x, y, 3);
    ans["name"] = "question answer";
    ans["correct"] = false;
    ans["result"] = "nothing";
    ans["row"] = x;
    ans["col"] = y;

    res["name"] = "opponent question answer";
    res["correct"] = false;
    res["result"] = "nothing";
    res["row"] = x;
    res["col"] = y;
    if (board.getType(x, y) == "bomb") {
        ans["result"] = "lost";
        res["result"] = "won";
    }
    else {
        board.Lock(x, y, self);
        ans["row"] = x;
        ans["col"] = y;
    }
    return {ans, res};
}

Game::~Game()
{
    qDebug() << "Destructor called";
}

void Game::playerOneWins()
{
    QJsonObject ans;
    ans["name"] = "game result";
    ans["result"] = "won";
    QJsonDocument document(ans);
    QByteArray datum = document.toJson();
    playerOne->write(datum);
    playerOne->waitForBytesWritten();
}


void Game::playerTwoWins()
{
    QJsonObject ans;
    ans["name"] = "game result";
    ans["result"] = "won";
    QJsonDocument document(ans);
    QByteArray datum = document.toJson();
    playerTwo->write(datum);
    playerTwo->waitForBytesWritten();

}


bool Game:: checkDraw ()
{
    for (int i = 0; i < 3; i ++) {
        std::vector<int> states;
        for (int j = 0; j < 3; j ++) {
            if (board.getStat(i, j) < 3) {
                states.push_back(board.getStat(i, j));
            }
        }
        bool flag = true;
        for (int j = 0; j < int(states.size()) - 1; j ++) {
            if(states[j] != states[j + 1]) {
                flag = false;
            }
        }
        if (flag) {
            return false;
        }
    }
    for (int i = 0; i < 3; i ++) {
        std::vector<int> states;
        for (int j = 0; j < 3; j ++) {
            if (board.getStat(j, i) < 3) {
                states.push_back(board.getStat(j, i));
            }
        }
        bool flag = true;
        for (int j = 0; j < int(states.size()) - 1; j ++) {
            if(states[j] != states[j + 1]) {
                flag = false;
            }
        }
        if (flag) {
            return false;
        }
    }
    std::vector<int> states;
    for (int i = 0 ; i < 3; i ++) {
        if (board.getStat(i, i) < 3) {
            states.push_back(board.getStat(i, i));
        }
    }
    bool flag = true;
    for (int j = 0 ; j < int(states.size()) -  1;  j ++) {
        if (states[j] != states[j + 1]) {
            flag = false;
        }
    }
    if (flag) {
        return false;
    }

    states.clear();
    for (int i = 0; i < 3; i ++) {
        if (board.getStat(0 + i, 2 - i) < 3) {
            states.push_back(board.getStat(0 + i, 2 - i));
        }
    }
    flag = true;
    for (int j = 0 ; j < int(states.size()) -  1;  j ++) {
        if (states[j] != states[j + 1]) {
            flag = false;
        }
    }
    if (flag) {
        return false;
    }
    return true;
}

void Game::playerOneReq()
{
    handleRequest (playerOne, playerTwo, 1, 2);
}
void Game::playerTwoReq()
{
    handleRequest (playerTwo, playerOne, 2, 1);
}

void Game::handleRequest (QTcpSocket* player, QTcpSocket* enemy, int self, int opponent)
{
    qDebug() << "Handeling some Request";
    QByteArray data = player->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject req = doc.object();

    // title -> نوع درخواست
    QJsonObject ans;
    QJsonObject res;
    if (req["title"].toString() == "introduction") {
        qDebug() << "introduction‌ : " << req["username"].toString();

        if (self == 1) {
            this->userOne = req["username"].toString();
        }
        else {
            this->userTwo = req["username"].toString();
        }
    }

    else if (req["title"].toString() == "click") {
        qDebug () << "new Question asked";
        int x = req["row"].toInt(), y = req["col"].toInt();

        ans = board.getObject(x, y);



        if (board.getStat(x, y) == 3) {
            ans = board.getObject(x, y);

            qDebug() << ans;
            ans["Allowed"] = true;
            res["Allowed"] = true;

            board.setState(x, y, self + 3);
        }
        else if (board.getStat(x, y) == 1 || board.getStat(x, y) == 2) {
            ans["Allowed"] = false;
            ans["Message"] = "Occupied before";
            res["Allowed"] = false;
        }
        else {
            ans["Allowed"] = false;
            ans["Message"] = "Opponent is answering";
            res["Allowed"] = false;
        }
        ans["row"] = x;
        ans["col"] = y;
        res["row"] = x;
        res["col"] = y;
        ans["name"] = "new question";
        res["name"] = "opponent answering";
        ans["kind"] = board.getType(x, y);
    }

    else if (req["title"].toString() == "skip") {
        int x = req["row"].toInt(), y = req["col"].toInt();
        board.changeQuestion(x, y);
        ans = board.getObject(x, y);
        ans["name"] = "skip question";
        ans["Allowed"] = true;
        ans["row"] = x;
        ans["col"] = y;
        ans["Message"] = "Question Changed at cell";
        res["name"] = "opponent skip question";
        ans["kind"] = board.getType(x, y);
    }

    else if (req["title"] == "timeout") {
        int x = req["row"].toInt(), y = req["col"].toInt();
        std::pair<QJsonObject, QJsonObject> p = wrongAnswer(x, y, self, opponent);
        ans = p.first;
        res = p.second;
    }
    else if (req["title"].toString() == "check") {
        int x = req["row"].toInt(), y = req["col"].toInt();
        qDebug() << "in check : " << x << " " << y << "\n";
        QString kind = board.getKind(x, y); // multiple or number or short
        Question* question = board.getQuestion(x, y);
        qDebug() << "reached 1";
        std::pair<QJsonObject, QJsonObject> p;
        if (kind == "multiple") {
            MultipleChoiceQuestion* multiple = dynamic_cast<MultipleChoiceQuestion*>(question);
            qDebug() << "reached 2";
            int choice = req["ans"].toInt ();
            qDebug() << "reached 3";
            if (choice == multiple->getAnswer()) {
                qDebug() << "reached 4";
                p = correctAnswer(x, y, self, opponent);
            }
            else {
                qDebug() << "reached 4";
                p = wrongAnswer(x, y, self, opponent);
            }
            qDebug() << "reached 5";
        }
        else if (kind == "number") {
            NumberQuestion* number = dynamic_cast<NumberQuestion*>(question);
            int choice = req["ans"].toInt();
            if (choice == number->getAnswer()) {
                p = correctAnswer(x, y, self, opponent);
            }
            else {
                p = wrongAnswer(x, y, self, opponent);
            }
        }
        else if (kind == "short") {
            ShortAnswerQuestion* shor = dynamic_cast<ShortAnswerQuestion*>(question);
            QString choice = req["ans"].toString();
            if (choice == shor->getAnswer()) {
                p = correctAnswer(x, y, self, opponent);
            }
            else {
                p = wrongAnswer(x, y, self, opponent);
            }
        }

        ans = p.first;
        res = p.second;
    }



    for (int i = 0; i < 3; i ++) {
        if (board.getStat(i, 0) == board.getStat(i, 1) == board.getStat(i, 2)) {
            if (board.getStat(i, 0) == self) {
                ans["name"] = "game result";
                ans["result"] = "won";
                // ans["opponent"]
                res["name"] = "game result";
                res["result"] = "lost";
            }
            else if (board.getStat(i, 0) == opponent) {
                ans["name"] = "game result";
                ans["result"] = "won";
                res["name"] = "game result";
                res["result"] = "lost";
            }
        }
    }

    for (int j = 0; j < 3; j ++) {
        if (board.getStat(0, j) == board.getStat(1, j) == board.getStat(2, j)) {
            if (board.getStat(0, j) == self) {
                ans["name"] = "game result";
                ans["result"] = "won";
                res["name"] = "game result";
                ans["result"] = "lost";
            }
            else if (board.getStat(0, j) == opponent) {
                ans["name"] = "game result";
                ans["result"] = "lost";
                res["name"] = "game result";
                ans["result"] = "won";
            }
        }
    }

    if (board.getStat(0, 0) == board.getStat(1, 1) == board.getStat(2, 2)) {
        if (board.getStat(0, 0) == self) {
            ans["name"] = "game result";
            ans["result"] = "won";
            res["name"] = "game result";
            ans["result"] = "lost";
        }
        else if (board.getStat(0, 0) == opponent) {
            ans["name"] = "game result";
            ans["result"] = "lost";
            res["name"] = "game result";
            ans["result"] = "won";
        }
    }

    if (board.getStat(0, 2) == board.getStat(1, 1) == board.getStat(2, 0)) {
        if (board.getStat(0, 2) == self) {
            ans["name"] = "game result";
            ans["result"] = "won";
            res["name"] = "game result";
            res["result"] = "lost";
        }
        else if (board.getStat(0, 2) == opponent) {
            ans["name"] = "game result";
            ans["result"] = "lost";
            res["name"] = "game result";
            res["result"] = "won";
        }
    }


    if (checkDraw()) {
        ans["name"] = "game result";
        ans["result"] = "draw";
        res["name"] = "game result";
        ans["result"] = "draw";
    }

    if (self == 1) {
        ans["opponent"] = userTwo;
        res["opponent"] = userOne;
    }
    else {
        ans["opponent"] = userOne;
        res["opponent"] = userTwo;
    }

    QJsonDocument document(ans);
    QByteArray datum = document.toJson();
    player->write(datum);
    player->waitForBytesWritten();

    QJsonDocument pocument(res);
    QByteArray patum = pocument.toJson();
    enemy->write(patum);
    enemy->waitForBytesWritten();



}

