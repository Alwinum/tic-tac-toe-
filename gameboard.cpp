#include "gameboard.h"

GameBoard::GameBoard()
{
    for (int i = 0; i < 10 ; i ++) {
        this->mark[i] = false;
    }
    createBoard();
}
void GameBoard::createBoard()
{

    for (int i = 0; i < 3; i ++) {
        for (int j = 0; j < 3; j ++) {
            board[i][j].setStatus(3);
        }
    }
    for (int i = 0; i < 10; i ++) {
        mark[i] = false;
    }
    for (int j = 0; j < 2; j ++) {
        this->setCell(1, 2);
    }
    for (int j = 0; j < 3; j ++) {
        this->setCell(1, 1);
    }
    for (int j = 0; j < 1; j ++) {
        this->setCell(1, 3);
    }
    for (int j = 0; j < 1; j ++) {
        this->setCell(2, 1);
    }
    for (int j = 0; j < 1; j ++) {
        this->setCell (2, 2);
    }
    for (int j = 0; j < 1; j ++) {
        this->setCell (3, 1);
    }
}
void GameBoard::setCell(int kind , int type)
{
    int cellNum = rand() % 9;
    while (mark[cellNum]) {
        cellNum = rand() % 9;
    }
    this->board[cellNum/3][cellNum%3].setKind(kind);
    this->board[cellNum/3][cellNum%3].setType(type);
    this->mark[cellNum] = true;
}

int GameBoard::getStat(int x, int y) {
    return this->board[x][y].status;
}

QJsonObject GameBoard::getObject(int x, int y)
{
    return this->board[x][y].factory.getObject();
}

Question* GameBoard::getQuestion(int x, int y)
{
    return board[x][y].factory.getQuestion();
}

void GameBoard::changeQuestion(int x, int y)
{
    board[x][y].factory.sendRequest(board[x][y].getKind());
}
QString GameBoard:: getKind (int x, int y) {
    return board[x][y].getKind();
}

QString GameBoard::getType(int x, int y)
{
    return board[x][y].getType();
}

void GameBoard::Lock(int x, int y, int player)
{
    if (player == 1) {
        board[x][y].lockOne = true;
    }
    else {
        board[x][y].lockTwo = true;
    }
}

void GameBoard::Unlock(int x, int y, int player)
{
    if (player == 1) {
        board[x][y].lockOne = false;
    }
    else {
        board[x][y].lockTwo = false;
    }
}

bool GameBoard::isLock(int x, int y, int player)
{
    if (player == 1 && board[x][y].lockOne) {
        return true;
    }
    if (player == 2 && board[x][y].lockTwo) {
        return true;
    }
    return false;
}
