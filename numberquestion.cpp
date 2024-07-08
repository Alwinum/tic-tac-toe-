#include "numberquestion.h"

NumberQuestion::NumberQuestion(QString title, QString category, int answer)
    :Question(title, category)
{
    this->answer = answer;
}

int NumberQuestion::getAnswer()
{
    return this->answer;
}
