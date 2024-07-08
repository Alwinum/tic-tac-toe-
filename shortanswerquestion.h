#ifndef SHORTANSWERQUESTION_H
#define SHORTANSWERQUESTION_H
#include <QString>
#include "question.h"
class ShortAnswerQuestion : public Question
{
public:
    ShortAnswerQuestion(QString title, QString category, QString answer);
    QString getAnswer();

private:
    QString answer;
};

#endif // SHORTANSWERQUESTION_H
