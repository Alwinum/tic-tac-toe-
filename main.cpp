#include "systemmanage.h"
#include "userpage.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    systemManage w;
    // UserPage p;
    // p.show();
    // p.showWaitingWindow();
    return a.exec();
}
