#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include "cell.h"
#include <QJsonObject>
// #include <vector>
class GameBoard
{
public:
    GameBoard();
    void setCell (int kind, int type);
    void createBoard();
    int getStat (int x, int y);
    QJsonObject getObject (int x, int y);
    Question* getQuestion (int x, int y);
    void changeQuestion(int x, int y);
    QString getKind(int x, int y);
    QString getType (int x, int y);
    void Lock (int x, int y, int player);
    void Unlock (int x, int y, int player);
    bool isLock(int x, int y, int player);
private :
    // std::vector<std::vector<Cell>> board;
    Cell board[4][4];
    bool mark[10];
};

#endif // GAMEBOARD_H
