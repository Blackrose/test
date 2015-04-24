#ifndef GOTOCALL_D_H
#define GOTOCALL_D_H

#include <QDialog>

namespace Ui {
class GoToCall_d;
}

class GoToCall_d : public QDialog
{
    Q_OBJECT
    
public:
    explicit GoToCall_d(QWidget *parent = 0);
    ~GoToCall_d();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::GoToCall_d *ui;
};

#endif // GOTOCALL_D_H
