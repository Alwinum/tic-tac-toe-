#include "questionfactory.h"
#include "shortanswerquestion.h"
#include "numberquestion.h"
#include "multiplechoicequestion.h"
QuestionFactory::QuestionFactory()
{

}
// /*
void QuestionFactory:: sendRequest (QString kind)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request(QUrl("https://questionbank.liara.run/api/QXJzaGl5YSBEb29zdGksU2FoYXIgR2hhc2VtaSxxcEUzUkt2TlUzODI/question?type=" + kind));
    QNetworkReply *reply = manager->get(request);

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response_data = reply->readAll();
        QJsonObject json = QJsonDocument::fromJson(response_data).object();
        // Process the JSON object here
        this->que = json;
        createQuestion();
    }
    reply->deleteLater();

}
// */
void QuestionFactory::createQuestion ()
{
    if (que["type"] == "number") {
        this->question =new NumberQuestion(que["questionText"].toString(), que["category"].toString(), que["answer"].toInt());
    }
    else if (que["type"] == "short") {
        this->question = new ShortAnswerQuestion(que["questionText"].toString(), que["category"].toString(), que["answer"].toString());
    }
    else if (que["type"] == "multiple") {
        QString op1, op2, op3, op4;
        int ans;
        op1 = que["answers"].toArray()[0].toObject()["text"].toString();
        op2 = que["answers"].toArray()[1].toObject()["text"].toString();
        op3 = que["answers"].toArray()[2].toObject()["text"].toString();
        op4 = que["answers"].toArray()[3].toObject()["text"].toString();
        for (int i = 0; i < 4; i ++ ){
            if (que["answers"].toArray()[i].toObject()["isCorrect"].toBool()) {
                ans = i;
            }
        }
        this->question = new MultipleChoiceQuestion(que["questionText"].toString(), que["category"].toString(), op1, op2, op3, op4, ans);
    }
}

Question* QuestionFactory::getQuestion() {
    // qDebug () << this->que;
    return this->question;
}

QJsonObject QuestionFactory::getObject ()
{
    return this->que;
}
