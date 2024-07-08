#ifndef CELL_H
#define CELL_H

#include "questionfactory.h"

class Cell
{
public:
    Cell(int kind, int );
    Cell ();

    void setType(int type);
    void setKind(int kind);
    void setStatus (int stat);
    void createQuestion ();
    QString getKind ();
    QString getType ();
    int get;
    int questionType;
    // 1. ordinary
    // 2. bomb
    // 3. winner
    int questionKind;
    // 1. multiple
    // 2. short
    // 3. number;
    int status;
    // 1. player one
    // 2. player two
    // 3. available for click
    // 4. player one is answering
    // 5. player two is answering
    bool lockOne = false;
    bool lockTwo = false;
    QuestionFactory factory;
};

#endif // CELL_H
