#include <QApplication>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QSlider>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget *window = new QWidget();
    QSpinBox *spinBox = new QSpinBox();
    QSlider *slider = new QSlider(Qt::Horizontal);
//    QHBoxLayout *layout = new QHBoxLayout;

    window->setWindowTitle("Age test.....");

    slider->setRange(0, 130);
    spinBox->setRange(0,130);
    QObject::connect(spinBox, SIGNAL(valueChanged(int)),
                     slider, SLOT(setValue(int)));

    QObject::connect(slider, SIGNAL(valueChanged(int)),
                     spinBox, SLOT(setValue(int)));
    spinBox->setValue(34);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(spinBox);
    layout->addWidget(slider);


    window->setLayout(layout);
    window->show();

    return app.exec();
}
