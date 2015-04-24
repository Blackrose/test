#include <QApplication>
#include <QtGui>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
int main(int argc, char* argv[])
{
    QApplication *app = new QApplication(argc, argv);
    QWidget *window = new QWidget;
    window->setWindowTitle("Go to Call");

    QLabel *lable = new QLabel("&Call location");
    QLineEdit * edit= new QLineEdit;
    lable->setBuddy(edit);
    QHBoxLayout* layout =new QHBoxLayout;
    layout->addWidget(lable);
    layout->addWidget(edit);

    QPushButton *okButton =new QPushButton("OK");
    QPushButton *CancelButton = new QPushButton("Cancel");
    okButton->setDefault(true);
    QObject::connect(okButton,SIGNAL(clicked()), app,SLOT(quit()));


    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(okButton);
    bottomLayout->addWidget(CancelButton);

    QVBoxLayout *VLayout = new QVBoxLayout;
    VLayout->addLayout(layout);
    VLayout->addLayout(bottomLayout);
    window->setLayout(VLayout);
    window->show();
    return app->exec();
}
