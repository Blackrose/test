#include <QtGui/QApplication>
#include "gotocall_d.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GoToCall_d w;
    w.show();
    
    return a.exec();
}
