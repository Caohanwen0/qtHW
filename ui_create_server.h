/********************************************************************************
** Form generated from reading UI file 'create_server.ui'
**
** Created by: Qt User Interface Compiler version 6.1.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATE_SERVER_H
#define UI_CREATE_SERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_create_server
{
public:
    QLabel *label;
    QLabel *IP;
    QLabel *status;
    QPushButton *createBtn;
    QPushButton *cancelBtn;

    void setupUi(QDialog *create_server)
    {
        if (create_server->objectName().isEmpty())
            create_server->setObjectName(QString::fromUtf8("create_server"));
        create_server->resize(400, 300);
        create_server->setMinimumSize(QSize(400, 300));
        create_server->setMaximumSize(QSize(400, 300));
        create_server->setStyleSheet(QString::fromUtf8("background:url(:/png/19.jpg);"));
        label = new QLabel(create_server);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 110, 81, 16));
        label->setStyleSheet(QString::fromUtf8("background:rgba(251, 255, 255, 0);\n"
"font: 15pt \"Andale Mono\";\n"
"color:rgb(255, 255, 255);"));
        IP = new QLabel(create_server);
        IP->setObjectName(QString::fromUtf8("IP"));
        IP->setGeometry(QRect(190, 110, 161, 20));
        IP->setStyleSheet(QString::fromUtf8("background:rgba(251, 255, 255, 0);\n"
"font: 15pt \"Andale Mono\";\n"
"color:rgb(255, 255, 255);"));
        status = new QLabel(create_server);
        status->setObjectName(QString::fromUtf8("status"));
        status->setGeometry(QRect(160, 161, 71, 20));
        status->setStyleSheet(QString::fromUtf8("background:rgba(251, 255, 255, 0);\n"
"font: 13pt \"Andale Mono\";\n"
"color:rgb(255, 255, 255);"));
        createBtn = new QPushButton(create_server);
        createBtn->setObjectName(QString::fromUtf8("createBtn"));
        createBtn->setGeometry(QRect(70, 230, 112, 32));
        createBtn->setStyleSheet(QString::fromUtf8("background:rgb(255, 255, 255);\n"
"color:rgb(0, 0, 0);\n"
"font: 13pt \"Andale Mono\";"));
        cancelBtn = new QPushButton(create_server);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
        cancelBtn->setGeometry(QRect(220, 230, 112, 32));
        cancelBtn->setStyleSheet(QString::fromUtf8("background:rgb(255, 255, 255);\n"
"color:rgb(0, 0, 0);\n"
"font: 13pt \"Andale Mono\";"));

        retranslateUi(create_server);
        QObject::connect(cancelBtn, &QPushButton::clicked, create_server, qOverload<>(&QDialog::close));
        QObject::connect(createBtn, SIGNAL(clicked()), create_server, SLOT(sendRightCreate()));

        QMetaObject::connectSlotsByName(create_server);
    } // setupUi

    void retranslateUi(QDialog *create_server)
    {
        create_server->setWindowTitle(QCoreApplication::translate("create_server", "Create the Connection...", nullptr));
        label->setText(QCoreApplication::translate("create_server", "Host IP:", nullptr));
        IP->setText(QCoreApplication::translate("create_server", "TextLabel", nullptr));
        status->setText(QString());
        createBtn->setText(QCoreApplication::translate("create_server", "Create", nullptr));
#if QT_CONFIG(shortcut)
        createBtn->setShortcut(QCoreApplication::translate("create_server", "Return", nullptr));
#endif // QT_CONFIG(shortcut)
        cancelBtn->setText(QCoreApplication::translate("create_server", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class create_server: public Ui_create_server {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATE_SERVER_H
