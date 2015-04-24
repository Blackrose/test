#include "gotocall_d.h"
#include "ui_gotocall_d.h"

GoToCall_d::GoToCall_d(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GoToCall_d)
{
    ui->setupUi(this);
}

GoToCall_d::~GoToCall_d()
{
    delete ui;
}

void GoToCall_d::on_pushButton_clicked()
{

}
