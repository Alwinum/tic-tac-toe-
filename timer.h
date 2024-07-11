#ifndef TIMER_H
#define TIMER_H
#include <QThread>
#include <QTime>

class Timer : public QThread
{
    Q_OBJECT

public:
    Timer();
    bool isRunning;
    void stop();
protected:
    void run() override;

signals:
    void updateTime(int time);
    void timeout();
};

#endif // TIMER_H
