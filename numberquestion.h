#ifndef NUMBERQUESTION_H
#define NUMBERQUESTION_H
#include "question.h"
#include <QString>
class NumberQuestion : public Question
{
public:
    NumberQuestion(QString title, QString category, int answer);
    int getAnswer();
private:
    int answer;
};

#endif // NUMBERQUESTION_H
