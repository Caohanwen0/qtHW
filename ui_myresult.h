/********************************************************************************
** Form generated from reading UI file 'myresult.ui'
**
** Created by: Qt User Interface Compiler version 6.1.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYRESULT_H
#define UI_MYRESULT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_myResult
{
public:
    QLabel *resLabel;
    QPushButton *pushButton;

    void setupUi(QDialog *myResult)
    {
        if (myResult->objectName().isEmpty())
            myResult->setObjectName(QString::fromUtf8("myResult"));
        myResult->resize(400, 160);
        myResult->setMinimumSize(QSize(400, 160));
        myResult->setMaximumSize(QSize(400, 160));
        myResult->setStyleSheet(QString::fromUtf8("background:url(:/png/19.jpg);"));
        resLabel = new QLabel(myResult);
        resLabel->setObjectName(QString::fromUtf8("resLabel"));
        resLabel->setGeometry(QRect(130, 60, 121, 31));
        resLabel->setStyleSheet(QString::fromUtf8("background:rgba(192, 196, 196,0);\n"
"color:rgb(251, 255, 255);\n"
"font: 24pt \"Andale Mono\";"));
        pushButton = new QPushButton(myResult);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(140, 120, 112, 32));
        pushButton->setStyleSheet(QString::fromUtf8("background:rgb(255, 255, 255);\n"
"color:rgb(0, 0, 0);\n"
"font: 13pt \"Andale Mono\";"));

        retranslateUi(myResult);

        QMetaObject::connectSlotsByName(myResult);
    } // setupUi

    void retranslateUi(QDialog *myResult)
    {
        myResult->setWindowTitle(QCoreApplication::translate("myResult", "Dialog", nullptr));
        resLabel->setText(QCoreApplication::translate("myResult", "You Win!", nullptr));
        pushButton->setText(QCoreApplication::translate("myResult", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class myResult: public Ui_myResult {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYRESULT_H
