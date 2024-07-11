#include "timer.h"

Timer::Timer() {
    isRunning = true;
}

void Timer::run()
{
    this->isRunning = true;
    for (int i = 100; i >= 0 && isRunning; i --){
        emit updateTime(i);
        QThread::msleep(200);
    }
    qDebug() << "time out reached";
    if(isRunning){
        qDebug() << "emiting timeout";
        emit timeout();
    }
}

void Timer::stop()
{
    this->isRunning = false;
}
