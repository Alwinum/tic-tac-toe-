#ifndef MULTIPLECHOICEQUESTION_H
#define MULTIPLECHOICEQUESTION_H
#include "question.h"
#include <QString>
class MultipleChoiceQuestion : public Question
{
public:
    MultipleChoiceQuestion(QString title, QString category, QString option1, QString option2,
                           QString option3, QString option4, int answer);
    int getAnswer();
private:
    QString option1, option2, option3, option4;
    int answer;
};

#endif // MULTIPLECHOICEQUESTION_H
