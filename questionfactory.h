#ifndef QUESTIONFACTORY_H
#define QUESTIONFACTORY_H

#include "question.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QString>
#include <QEventLoop>
#include "multiplechoicequestion.h"
#include "numberquestion.h"
#include "shortanswerquestion.h"
class QuestionFactory : public QObject
{

    Q_OBJECT
public:
    QuestionFactory();
    void createQuestion ();
    Question* getQuestion ();
    QJsonObject getObject();
    void sendRequest (QString kind);
private :
    Question* question;
    QJsonObject que;
};

#endif // QUESTIONFACTORY_H
