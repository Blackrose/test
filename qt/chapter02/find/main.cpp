#include<QApplication>
#include"find.h"
int main(int argc, char *argv[])
{
    QApplication *app = new QApplication(argc, argv);
    FindDialog *dialog = new FindDialog;
    dialog->show();

    return app->exec();
}


