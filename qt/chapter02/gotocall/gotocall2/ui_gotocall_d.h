/********************************************************************************
** Form generated from reading UI file 'gotocall_d.ui'
**
** Created: Wed Apr 15 14:14:46 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GOTOCALL_D_H
#define UI_GOTOCALL_D_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_GoToCall_d
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit;
    QLabel *label;

    void setupUi(QDialog *GoToCall_d)
    {
        if (GoToCall_d->objectName().isEmpty())
            GoToCall_d->setObjectName(QString::fromUtf8("GoToCall_d"));
        GoToCall_d->resize(349, 130);
        pushButton = new QPushButton(GoToCall_d);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(120, 80, 98, 27));
        pushButton_2 = new QPushButton(GoToCall_d);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(240, 80, 98, 27));
        lineEdit = new QLineEdit(GoToCall_d);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(200, 20, 113, 27));
        label = new QLabel(GoToCall_d);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 20, 71, 17));

        retranslateUi(GoToCall_d);

        QMetaObject::connectSlotsByName(GoToCall_d);
    } // setupUi

    void retranslateUi(QDialog *GoToCall_d)
    {
        GoToCall_d->setWindowTitle(QApplication::translate("GoToCall_d", "GoToCall_d", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("GoToCall_d", "OK", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("GoToCall_d", "Cancel", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("GoToCall_d", "Call Loacation", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GoToCall_d: public Ui_GoToCall_d {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GOTOCALL_D_H
