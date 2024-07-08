#include "multiplechoicequestion.h"

MultipleChoiceQuestion::MultipleChoiceQuestion(QString title, QString category, QString option1, QString option2, QString option3, QString option4, int answer)
    : Question(title, category)
{
    this->answer = answer;
    this->option1 = option1;
    this->option2 = option2;
    this->option3 = option3;
    this->option4 = option4;
}

int MultipleChoiceQuestion::getAnswer () {
    return this->answer;
}
