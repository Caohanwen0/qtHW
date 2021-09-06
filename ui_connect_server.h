/********************************************************************************
** Form generated from reading UI file 'connect_server.ui'
**
** Created by: Qt User Interface Compiler version 6.1.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECT_SERVER_H
#define UI_CONNECT_SERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_connect_server
{
public:
    QLineEdit *ipInput;
    QLabel *label;
    QPushButton *num1;
    QPushButton *num2;
    QPushButton *num3;
    QPushButton *num4;
    QPushButton *num5;
    QPushButton *num6;
    QPushButton *num7;
    QPushButton *num8;
    QPushButton *num0;
    QPushButton *numDelete;
    QPushButton *num9;
    QPushButton *numBlank;
    QLabel *wrongMsg;
    QPushButton *connectBtn;
    QPushButton *cancelBtn;

    void setupUi(QDialog *connect_server)
    {
        if (connect_server->objectName().isEmpty())
            connect_server->setObjectName(QString::fromUtf8("connect_server"));
        connect_server->resize(400, 300);
        connect_server->setMinimumSize(QSize(400, 300));
        connect_server->setMaximumSize(QSize(400, 300));
        connect_server->setStyleSheet(QString::fromUtf8("background:url(:/png/19.jpg);"));
        ipInput = new QLineEdit(connect_server);
        ipInput->setObjectName(QString::fromUtf8("ipInput"));
        ipInput->setGeometry(QRect(200, 70, 113, 21));
        ipInput->setStyleSheet(QString::fromUtf8("background:rgb(230, 234, 234)"));
        label = new QLabel(connect_server);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 70, 111, 21));
        QFont font;
        font.setFamilies({QString::fromUtf8("Andale Mono")});
        font.setPointSize(13);
        font.setBold(false);
        font.setItalic(false);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("background:rgba(45, 46, 50,0);\n"
"color:rgb(230, 234, 234);\n"
"font: 13pt \"Andale Mono\";"));
        num1 = new QPushButton(connect_server);
        num1->setObjectName(QString::fromUtf8("num1"));
        num1->setGeometry(QRect(70, 105, 80, 25));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(num1->sizePolicy().hasHeightForWidth());
        num1->setSizePolicy(sizePolicy);
        num1->setMinimumSize(QSize(80, 25));
        num1->setMaximumSize(QSize(80, 25));
        num1->setSizeIncrement(QSize(15, 0));
        num1->setFont(font);
        num1->setStyleSheet(QString::fromUtf8("background:rgb(255, 255, 255);\n"
"color:rgb(0, 0, 0);\n"
"font: 13pt \"Andale Mono\";"));
        num2 = new QPushButton(connect_server);
        num2->setObjectName(QString::fromUtf8("num2"));
        num2->setGeometry(QRect(160, 105, 80, 25));
        sizePolicy.setHeightForWidth(num2->sizePolicy().hasHeightForWidth());
        num2->setSizePolicy(sizePolicy);
        num2->setMinimumSize(QSize(80, 25));
        num2->setMaximumSize(QSize(80, 25));
        num2->setSizeIncrement(QSize(15, 0));
        num2->setFont(font);
        num2->setStyleSheet(QString::fromUtf8("background:rgb(255, 255, 255);\n"
"color:rgb(0, 0, 0);\n"
"font: 13pt \"Andale Mono\";"));
        num3 = new QPushButton(connect_server);
        num3->setObjectName(QString::fromUtf8("num3"));
        num3->setGeometry(QRect(250, 105, 80, 25));
        sizePolicy.setHeightForWidth(num3->sizePolicy().hasHeightForWidth());
        num3->setSizePolicy(sizePolicy);
        num3->setMinimumSize(QSize(80, 25));
        num3->setMaximumSize(QSize(80, 25));
        num3->setSizeIncrement(QSize(15, 0));
        num3->setFont(font);
        num3->setStyleSheet(QString::fromUtf8("background:rgb(255, 255, 255);\n"
"color:rgb(0, 0, 0);\n"
"font: 13pt \"Andale Mono\";"));
        num4 = new QPushButton(connect_server);
        num4->setObjectName(QString::fromUtf8("num4"));
        num4->setGeometry(QRect(70, 130, 80, 25));
        sizePolicy.setHeightForWidth(num4->sizePolicy().hasHeightForWidth());
        num4->setSizePolicy(sizePolicy);
        num4->setMinimumSize(QSize(80, 25));
        num4->setMaximumSize(QSize(80, 23));
        num4->setSizeIncrement(QSize(15, 0));
        num4->setFont(font);
        num4->setStyleSheet(QString::fromUtf8("background:rgb(255, 255, 255);\n"
"color:rgb(0, 0, 0);\n"
"font: 13pt \"Andale Mono\";"));
        num5 = new QPushButton(connect_server);
        num5->setObjectName(QString::fromUtf8("num5"));
        num5->setGeometry(QRect(160, 130, 80, 25));
        sizePolicy.setHeightForWidth(num5->sizePolicy().hasHeightForWidth());
        num5->setSizePolicy(sizePolicy);
        num5->setMinimumSize(QSize(80, 25));
        num5->setMaximumSize(QSize(80, 25));
        num5->setSizeIncrement(QSize(15, 0));
        num5->setFont(font);
        num5->setStyleSheet(QString::fromUtf8("background:rgb(255, 255, 255);\n"
"color:rgb(0, 0, 0);\n"
"font: 13pt \"Andale Mono\";"));
        num6 = new QPushButton(connect_server);
        num6->setObjectName(QString::fromUtf8("num6"));
        num6->setGeometry(QRect(250, 130, 80, 25));
        sizePolicy.setHeightForWidth(num6->sizePolicy().hasHeightForWidth());
        num6->setSizePolicy(sizePolicy);
        num6->setMinimumSize(QSize(80, 25));
        num6->setMaximumSize(QSize(80, 25));
        num6->setSizeIncrement(QSize(15, 0));
        num6->setFont(font);
        num6->setStyleSheet(QString::fromUtf8("background:rgb(255, 255, 255);\n"
"color:rgb(0, 0, 0);\n"
"font: 13pt \"Andale Mono\";"));
        num7 = new QPushButton(connect_server);
        num7->setObjectName(QString::fromUtf8("num7"));
        num7->setGeometry(QRect(70, 155, 80, 25));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(80);
        sizePolicy1.setVerticalStretch(30);
        sizePolicy1.setHeightForWidth(num7->sizePolicy().hasHeightForWidth());
        num7->setSizePolicy(sizePolicy1);
        num7->setMinimumSize(QSize(80, 25));
        num7->setMaximumSize(QSize(80, 25));
        num7->setSizeIncrement(QSize(15, 0));
        num7->setFont(font);
        num7->setStyleSheet(QString::fromUtf8("background:rgb(255, 255, 255);\n"
"color:rgb(0, 0, 0);\n"
"font: 13pt \"Andale Mono\";"));
        num8 = new QPushButton(connect_server);
        num8->setObjectName(QString::fromUtf8("num8"));
        num8->setGeometry(QRect(160, 155, 80, 25));
        sizePolicy.setHeightForWidth(num8->sizePolicy().hasHeightForWidth());
        num8->setSizePolicy(sizePolicy);
        num8->setMinimumSize(QSize(80, 25));
        num8->setMaximumSize(QSize(80, 25));
        num8->setSizeIncrement(QSize(15, 0));
        num8->setFont(font);
        num8->setStyleSheet(QString::fromUtf8("background:rgb(255, 255, 255);\n"
"color:rgb(0, 0, 0);\n"
"font: 13pt \"Andale Mono\";"));
        num0 = new QPushButton(connect_server);
        num0->setObjectName(QString::fromUtf8("num0"));
        num0->setGeometry(QRect(160, 180, 80, 25));
        sizePolicy.setHeightForWidth(num0->sizePolicy().hasHeightForWidth());
        num0->setSizePolicy(sizePolicy);
        num0->setMinimumSize(QSize(80, 25));
        num0->setMaximumSize(QSize(80, 25));
        num0->setSizeIncrement(QSize(15, 0));
        num0->setFont(font);
        num0->setStyleSheet(QString::fromUtf8("background:rgb(255, 255, 255);\n"
"color:rgb(0, 0, 0);\n"
"font: 13pt \"Andale Mono\";"));
        numDelete = new QPushButton(connect_server);
        numDelete->setObjectName(QString::fromUtf8("numDelete"));
        numDelete->setGeometry(QRect(70, 180, 80, 25));
        sizePolicy.setHeightForWidth(numDelete->sizePolicy().hasHeightForWidth());
        numDelete->setSizePolicy(sizePolicy);
        numDelete->setMinimumSize(QSize(80, 25));
        numDelete->setMaximumSize(QSize(80, 25));
        numDelete->setSizeIncrement(QSize(15, 0));
        numDelete->setFont(font);
        numDelete->setStyleSheet(QString::fromUtf8("background:rgb(255, 255, 255);\n"
"color:rgb(0, 0, 0);\n"
"font: 13pt \"Andale Mono\";"));
        num9 = new QPushButton(connect_server);
        num9->setObjectName(QString::fromUtf8("num9"));
        num9->setGeometry(QRect(250, 155, 80, 25));
        sizePolicy.setHeightForWidth(num9->sizePolicy().hasHeightForWidth());
        num9->setSizePolicy(sizePolicy);
        num9->setMinimumSize(QSize(80, 25));
        num9->setMaximumSize(QSize(80, 25));
        num9->setSizeIncrement(QSize(15, 0));
        num9->setFont(font);
        num9->setStyleSheet(QString::fromUtf8("background:rgb(255, 255, 255);\n"
"color:rgb(0, 0, 0);\n"
"font: 13pt \"Andale Mono\";"));
        numBlank = new QPushButton(connect_server);
        numBlank->setObjectName(QString::fromUtf8("numBlank"));
        numBlank->setGeometry(QRect(250, 180, 80, 25));
        sizePolicy.setHeightForWidth(numBlank->sizePolicy().hasHeightForWidth());
        numBlank->setSizePolicy(sizePolicy);
        numBlank->setMinimumSize(QSize(80, 25));
        numBlank->setMaximumSize(QSize(80, 25));
        numBlank->setSizeIncrement(QSize(15, 0));
        numBlank->setFont(font);
        numBlank->setStyleSheet(QString::fromUtf8("background:rgb(255, 255, 255);\n"
"color:rgb(0, 0, 0);\n"
"font: 13pt \"Andale Mono\";"));
        wrongMsg = new QLabel(connect_server);
        wrongMsg->setObjectName(QString::fromUtf8("wrongMsg"));
        wrongMsg->setGeometry(QRect(140, 30, 121, 20));
        wrongMsg->setStyleSheet(QString::fromUtf8("background:rgba(45, 46, 50,0);\n"
"color:rgb(230, 234, 234);\n"
"font: 13pt \"Andale Mono\";"));
        connectBtn = new QPushButton(connect_server);
        connectBtn->setObjectName(QString::fromUtf8("connectBtn"));
        connectBtn->setGeometry(QRect(50, 230, 112, 32));
        connectBtn->setStyleSheet(QString::fromUtf8("background:rgb(255, 255, 255);\n"
"color:rgb(0, 0, 0);\n"
"font: 13pt \"Andale Mono\";"));
        cancelBtn = new QPushButton(connect_server);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
        cancelBtn->setGeometry(QRect(230, 230, 112, 32));
        cancelBtn->setStyleSheet(QString::fromUtf8("background:rgb(255, 255, 255);\n"
"color:rgb(0, 0, 0);\n"
"font: 13pt \"Andale Mono\";"));

        retranslateUi(connect_server);
        QObject::connect(connectBtn, SIGNAL(clicked()), connect_server, SLOT(sendRightConnect()));
        QObject::connect(cancelBtn, &QPushButton::clicked, connect_server, qOverload<>(&QDialog::close));

        QMetaObject::connectSlotsByName(connect_server);
    } // setupUi

    void retranslateUi(QDialog *connect_server)
    {
        connect_server->setWindowTitle(QCoreApplication::translate("connect_server", "Connect to server...", nullptr));
        label->setText(QCoreApplication::translate("connect_server", "Enter Your IP:", nullptr));
        num1->setText(QCoreApplication::translate("connect_server", "1", nullptr));
        num2->setText(QCoreApplication::translate("connect_server", "2", nullptr));
        num3->setText(QCoreApplication::translate("connect_server", "3", nullptr));
        num4->setText(QCoreApplication::translate("connect_server", "4", nullptr));
        num5->setText(QCoreApplication::translate("connect_server", "5", nullptr));
        num6->setText(QCoreApplication::translate("connect_server", "6", nullptr));
        num7->setText(QCoreApplication::translate("connect_server", "7", nullptr));
        num8->setText(QCoreApplication::translate("connect_server", "8", nullptr));
        num0->setText(QCoreApplication::translate("connect_server", "0", nullptr));
        numDelete->setText(QCoreApplication::translate("connect_server", "Delete", nullptr));
        num9->setText(QCoreApplication::translate("connect_server", "9", nullptr));
        numBlank->setText(QCoreApplication::translate("connect_server", "Space", nullptr));
        wrongMsg->setText(QString());
        connectBtn->setText(QCoreApplication::translate("connect_server", "Connect", nullptr));
#if QT_CONFIG(shortcut)
        connectBtn->setShortcut(QCoreApplication::translate("connect_server", "Return", nullptr));
#endif // QT_CONFIG(shortcut)
        cancelBtn->setText(QCoreApplication::translate("connect_server", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class connect_server: public Ui_connect_server {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECT_SERVER_H
