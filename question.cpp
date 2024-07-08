#include "question.h"

Question::Question(QString title, QString category) {
    this->title = title;
    this->category = category;
}

QString Question :: getTitle() {
    return this->title;
}
