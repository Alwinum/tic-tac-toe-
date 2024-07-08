#include "cell.h"

Cell::Cell(int type, int kind)
{
    this->questionKind = kind;
    this->questionType = type;
}

Cell::Cell ()
{
    this->questionKind = 0;
    this->questionType = 0;
}
void Cell::setType(int type) {
    this->questionType = type;
}
void Cell::setKind(int kind) {
    this->questionKind = kind;
}

void Cell::setStatus(int stat)
{
    this->status = stat;
}

QString Cell::getType ()
{
    QString kind;
    if (this->questionType == 1) {
        kind = "ordinary";
    }
    else if (this->questionType == 2) {
        kind = "bomb";
    }
    else if (this->questionType == 3) {
        kind = "winner";
    }
    return kind;
}

QString Cell::getKind ()
{
    QString kind;
    if (this->questionKind == 1) {
        kind = "multiple";
    }
    else if (this->questionKind == 2) {
        kind = "short";
    }
    else if (this->questionKind == 3) {
        kind = "number";
    }
    return kind;
}

void Cell::createQuestion ()
{

    this->factory.sendRequest(this->getKind());
}
