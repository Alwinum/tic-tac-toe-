#include "shortanswerquestion.h"
ShortAnswerQuestion::ShortAnswerQuestion(QString title, QString category, QString answer)
    : Question(title, category)
{
    this->answer = answer;
}

QString ShortAnswerQuestion::getAnswer()
{
    return this->answer;
}

