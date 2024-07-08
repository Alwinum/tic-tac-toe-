#ifndef QUESTION_H
#define QUESTION_H
#include <QString>
class Question
{
public:
    Question(QString title, QString category);
    virtual QString getTitle ();
protected:
    QString title;
    QString category;

};

#endif // QUESTION_H
