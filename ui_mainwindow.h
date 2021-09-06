/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.1.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "mybutton.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actConnect;
    QAction *actCreate;
    QWidget *centralwidget;
    QToolButton *admitDefeat;
    QToolButton *newGame;
    QLabel *titleNewGame;
    QLabel *admit;
    QLabel *warningText;
    QLabel *blankBoard;
    QLabel *countDown;
    QLabel *notice;
    QLabel *youAre;
    QLabel *remainTime;
    myButton *A1;
    myButton *A1_2;
    myButton *A1_3;
    myButton *A1_4;
    myButton *A1_5;
    myButton *A1_6;
    myButton *A1_7;
    myButton *A1_8;
    myButton *A1_9;
    myButton *A1_10;
    myButton *A1_11;
    myButton *A1_12;
    myButton *A1_13;
    myButton *A1_14;
    myButton *A1_15;
    myButton *A1_16;
    myButton *A1_17;
    myButton *A1_18;
    myButton *A1_19;
    myButton *A1_20;
    myButton *A1_23;
    myButton *A1_24;
    myButton *A1_25;
    myButton *A1_26;
    myButton *A1_27;
    myButton *A1_28;
    myButton *A1_29;
    myButton *A1_30;
    myButton *A1_31;
    myButton *A1_32;
    myButton *A1_33;
    myButton *A1_34;
    myButton *A1_35;
    myButton *A1_36;
    myButton *A1_37;
    myButton *A1_38;
    myButton *A1_39;
    myButton *A1_40;
    myButton *A1_41;
    myButton *A1_42;
    myButton *A1_43;
    myButton *A1_44;
    myButton *A1_45;
    myButton *A1_46;
    myButton *A1_47;
    myButton *A1_48;
    myButton *A1_49;
    myButton *A1_50;
    QLabel *sec;
    myButton *A1_21;
    myButton *A1_22;
    myButton *B1;
    myButton *B1_2;
    myButton *B1_3;
    myButton *B1_4;
    myButton *B1_5;
    myButton *B1_6;
    myButton *B1_7;
    myButton *B1_8;
    myButton *B1_9;
    myButton *B1_10;
    QLabel *theme;
    QLabel *severState;
    QLabel *label1;
    QLabel *label3;
    QLabel *label2;
    QLabel *roundCount;
    QLabel *timeoutCount;
    QPushButton *quit;
    QMenuBar *menu;
    QMenu *menuService;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(500, 722);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(500, 700));
        MainWindow->setMaximumSize(QSize(500, 722));
        MainWindow->setStyleSheet(QString::fromUtf8("background:rgb(54, 59, 63)"));
        actConnect = new QAction(MainWindow);
        actConnect->setObjectName(QString::fromUtf8("actConnect"));
        actCreate = new QAction(MainWindow);
        actCreate->setObjectName(QString::fromUtf8("actCreate"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setMinimumSize(QSize(500, 700));
        centralwidget->setMaximumSize(QSize(500, 700));
        admitDefeat = new QToolButton(centralwidget);
        admitDefeat->setObjectName(QString::fromUtf8("admitDefeat"));
        admitDefeat->setGeometry(QRect(150, 10, 41, 41));
        admitDefeat->setStyleSheet(QString::fromUtf8("border-image:url(:/icon/Securityclose.png);\n"
"background:rgba(255, 255, 255, 0)"));
        newGame = new QToolButton(centralwidget);
        newGame->setObjectName(QString::fromUtf8("newGame"));
        newGame->setGeometry(QRect(40, 10, 41, 41));
        newGame->setStyleSheet(QString::fromUtf8("border-image:url(:/icon/Newpost.png);\n"
"background:rgba(255, 255, 255, 0);"));
        titleNewGame = new QLabel(centralwidget);
        titleNewGame->setObjectName(QString::fromUtf8("titleNewGame"));
        titleNewGame->setGeometry(QRect(30, 60, 71, 16));
        titleNewGame->setStyleSheet(QString::fromUtf8("background:rgba(255, 255, 255, 0);\n"
"color:rgb(251, 255, 255);\n"
"font: 13pt \"Andale Mono\";"));
        admit = new QLabel(centralwidget);
        admit->setObjectName(QString::fromUtf8("admit"));
        admit->setGeometry(QRect(120, 60, 101, 21));
        admit->setStyleSheet(QString::fromUtf8("background:rgba(255, 255, 255, 0);\n"
"color:rgb(251, 255, 255);\n"
"font: 13pt \"Andale Mono\";"));
        warningText = new QLabel(centralwidget);
        warningText->setObjectName(QString::fromUtf8("warningText"));
        warningText->setGeometry(QRect(620, 350, 161, 211));
        warningText->setStyleSheet(QString::fromUtf8("background:rgba(255, 255, 255, 0);"));
        blankBoard = new QLabel(centralwidget);
        blankBoard->setObjectName(QString::fromUtf8("blankBoard"));
        blankBoard->setGeometry(QRect(50, 110, 401, 481));
        blankBoard->setMinimumSize(QSize(0, 0));
        blankBoard->setMaximumSize(QSize(4500, 5500));
        blankBoard->setPixmap(QPixmap(QString::fromUtf8(":/png/9.png")));
        blankBoard->setScaledContents(true);
        countDown = new QLabel(centralwidget);
        countDown->setObjectName(QString::fromUtf8("countDown"));
        countDown->setGeometry(QRect(260, 10, 111, 51));
        countDown->setStyleSheet(QString::fromUtf8("background:rgba(255, 255, 255, 0);\n"
"color:rgb(251, 255, 255);\n"
"font: 40pt \"Andale Mono\";"));
        notice = new QLabel(centralwidget);
        notice->setObjectName(QString::fromUtf8("notice"));
        notice->setGeometry(QRect(50, 610, 401, 61));
        notice->setStyleSheet(QString::fromUtf8("background:rgba(255, 255, 255, 0);\n"
"color:rgb(251, 255, 255);\n"
"font: 20pt \"Andale Mono\";"));
        youAre = new QLabel(centralwidget);
        youAre->setObjectName(QString::fromUtf8("youAre"));
        youAre->setGeometry(QRect(400, 60, 91, 31));
        youAre->setStyleSheet(QString::fromUtf8("background:rgba(255, 255, 255, 0);\n"
"color:rgb(251, 255, 255);\n"
"font: 13pt \"Andale Mono\";"));
        remainTime = new QLabel(centralwidget);
        remainTime->setObjectName(QString::fromUtf8("remainTime"));
        remainTime->setGeometry(QRect(260, 60, 111, 21));
        remainTime->setStyleSheet(QString::fromUtf8("background:rgba(255, 255, 255, 0);\n"
"color:rgb(251, 255, 255);\n"
"font: 13pt \"Andale Mono\";"));
        A1 = new myButton(centralwidget);
        A1->setObjectName(QString::fromUtf8("A1"));
        A1->setGeometry(QRect(53, 116, 70, 30));
        A1_2 = new myButton(centralwidget);
        A1_2->setObjectName(QString::fromUtf8("A1_2"));
        A1_2->setGeometry(QRect(134, 116, 70, 30));
        A1_3 = new myButton(centralwidget);
        A1_3->setObjectName(QString::fromUtf8("A1_3"));
        A1_3->setGeometry(QRect(214, 116, 70, 30));
        A1_4 = new myButton(centralwidget);
        A1_4->setObjectName(QString::fromUtf8("A1_4"));
        A1_4->setGeometry(QRect(295, 116, 70, 30));
        A1_5 = new myButton(centralwidget);
        A1_5->setObjectName(QString::fromUtf8("A1_5"));
        A1_5->setGeometry(QRect(377, 116, 70, 30));
        A1_6 = new myButton(centralwidget);
        A1_6->setObjectName(QString::fromUtf8("A1_6"));
        A1_6->setGeometry(QRect(53, 148, 70, 30));
        A1_7 = new myButton(centralwidget);
        A1_7->setObjectName(QString::fromUtf8("A1_7"));
        A1_7->setGeometry(QRect(134, 148, 70, 30));
        A1_8 = new myButton(centralwidget);
        A1_8->setObjectName(QString::fromUtf8("A1_8"));
        A1_8->setGeometry(QRect(214, 148, 70, 30));
        A1_9 = new myButton(centralwidget);
        A1_9->setObjectName(QString::fromUtf8("A1_9"));
        A1_9->setGeometry(QRect(295, 148, 70, 30));
        A1_10 = new myButton(centralwidget);
        A1_10->setObjectName(QString::fromUtf8("A1_10"));
        A1_10->setGeometry(QRect(377, 148, 70, 30));
        A1_11 = new myButton(centralwidget);
        A1_11->setObjectName(QString::fromUtf8("A1_11"));
        A1_11->setGeometry(QRect(53, 181, 70, 30));
        A1_12 = new myButton(centralwidget);
        A1_12->setObjectName(QString::fromUtf8("A1_12"));
        A1_12->setGeometry(QRect(214, 181, 70, 30));
        A1_13 = new myButton(centralwidget);
        A1_13->setObjectName(QString::fromUtf8("A1_13"));
        A1_13->setGeometry(QRect(377, 181, 70, 30));
        A1_14 = new myButton(centralwidget);
        A1_14->setObjectName(QString::fromUtf8("A1_14"));
        A1_14->setGeometry(QRect(53, 215, 70, 30));
        A1_15 = new myButton(centralwidget);
        A1_15->setObjectName(QString::fromUtf8("A1_15"));
        A1_15->setGeometry(QRect(134, 215, 70, 30));
        A1_16 = new myButton(centralwidget);
        A1_16->setObjectName(QString::fromUtf8("A1_16"));
        A1_16->setGeometry(QRect(295, 215, 70, 30));
        A1_17 = new myButton(centralwidget);
        A1_17->setObjectName(QString::fromUtf8("A1_17"));
        A1_17->setGeometry(QRect(377, 215, 70, 30));
        A1_18 = new myButton(centralwidget);
        A1_18->setObjectName(QString::fromUtf8("A1_18"));
        A1_18->setGeometry(QRect(53, 248, 70, 30));
        A1_19 = new myButton(centralwidget);
        A1_19->setObjectName(QString::fromUtf8("A1_19"));
        A1_19->setGeometry(QRect(214, 248, 70, 30));
        A1_20 = new myButton(centralwidget);
        A1_20->setObjectName(QString::fromUtf8("A1_20"));
        A1_20->setGeometry(QRect(377, 248, 70, 30));
        A1_23 = new myButton(centralwidget);
        A1_23->setObjectName(QString::fromUtf8("A1_23"));
        A1_23->setGeometry(QRect(214, 280, 70, 30));
        A1_24 = new myButton(centralwidget);
        A1_24->setObjectName(QString::fromUtf8("A1_24"));
        A1_24->setGeometry(QRect(295, 280, 70, 30));
        A1_25 = new myButton(centralwidget);
        A1_25->setObjectName(QString::fromUtf8("A1_25"));
        A1_25->setGeometry(QRect(377, 280, 70, 30));
        A1_26 = new myButton(centralwidget);
        A1_26->setObjectName(QString::fromUtf8("A1_26"));
        A1_26->setGeometry(QRect(53, 386, 70, 30));
        A1_27 = new myButton(centralwidget);
        A1_27->setObjectName(QString::fromUtf8("A1_27"));
        A1_27->setGeometry(QRect(134, 386, 70, 30));
        A1_28 = new myButton(centralwidget);
        A1_28->setObjectName(QString::fromUtf8("A1_28"));
        A1_28->setGeometry(QRect(214, 386, 70, 30));
        A1_29 = new myButton(centralwidget);
        A1_29->setObjectName(QString::fromUtf8("A1_29"));
        A1_29->setGeometry(QRect(295, 386, 70, 30));
        A1_30 = new myButton(centralwidget);
        A1_30->setObjectName(QString::fromUtf8("A1_30"));
        A1_30->setGeometry(QRect(377, 386, 70, 30));
        A1_31 = new myButton(centralwidget);
        A1_31->setObjectName(QString::fromUtf8("A1_31"));
        A1_31->setGeometry(QRect(53, 420, 70, 30));
        A1_32 = new myButton(centralwidget);
        A1_32->setObjectName(QString::fromUtf8("A1_32"));
        A1_32->setGeometry(QRect(214, 420, 70, 30));
        A1_33 = new myButton(centralwidget);
        A1_33->setObjectName(QString::fromUtf8("A1_33"));
        A1_33->setGeometry(QRect(377, 420, 70, 30));
        A1_34 = new myButton(centralwidget);
        A1_34->setObjectName(QString::fromUtf8("A1_34"));
        A1_34->setGeometry(QRect(53, 452, 70, 30));
        A1_35 = new myButton(centralwidget);
        A1_35->setObjectName(QString::fromUtf8("A1_35"));
        A1_35->setGeometry(QRect(134, 452, 70, 30));
        A1_36 = new myButton(centralwidget);
        A1_36->setObjectName(QString::fromUtf8("A1_36"));
        A1_36->setGeometry(QRect(295, 452, 70, 30));
        A1_37 = new myButton(centralwidget);
        A1_37->setObjectName(QString::fromUtf8("A1_37"));
        A1_37->setGeometry(QRect(377, 452, 70, 30));
        A1_38 = new myButton(centralwidget);
        A1_38->setObjectName(QString::fromUtf8("A1_38"));
        A1_38->setGeometry(QRect(53, 485, 70, 30));
        A1_39 = new myButton(centralwidget);
        A1_39->setObjectName(QString::fromUtf8("A1_39"));
        A1_39->setGeometry(QRect(214, 485, 70, 30));
        A1_40 = new myButton(centralwidget);
        A1_40->setObjectName(QString::fromUtf8("A1_40"));
        A1_40->setGeometry(QRect(377, 485, 70, 30));
        A1_41 = new myButton(centralwidget);
        A1_41->setObjectName(QString::fromUtf8("A1_41"));
        A1_41->setGeometry(QRect(53, 518, 70, 30));
        A1_42 = new myButton(centralwidget);
        A1_42->setObjectName(QString::fromUtf8("A1_42"));
        A1_42->setGeometry(QRect(134, 518, 70, 30));
        A1_43 = new myButton(centralwidget);
        A1_43->setObjectName(QString::fromUtf8("A1_43"));
        A1_43->setGeometry(QRect(214, 518, 70, 30));
        A1_44 = new myButton(centralwidget);
        A1_44->setObjectName(QString::fromUtf8("A1_44"));
        A1_44->setGeometry(QRect(295, 518, 70, 30));
        A1_45 = new myButton(centralwidget);
        A1_45->setObjectName(QString::fromUtf8("A1_45"));
        A1_45->setGeometry(QRect(377, 518, 70, 30));
        A1_46 = new myButton(centralwidget);
        A1_46->setObjectName(QString::fromUtf8("A1_46"));
        A1_46->setGeometry(QRect(53, 551, 70, 30));
        A1_47 = new myButton(centralwidget);
        A1_47->setObjectName(QString::fromUtf8("A1_47"));
        A1_47->setGeometry(QRect(134, 551, 70, 30));
        A1_48 = new myButton(centralwidget);
        A1_48->setObjectName(QString::fromUtf8("A1_48"));
        A1_48->setGeometry(QRect(214, 551, 70, 30));
        A1_49 = new myButton(centralwidget);
        A1_49->setObjectName(QString::fromUtf8("A1_49"));
        A1_49->setGeometry(QRect(295, 551, 70, 30));
        A1_50 = new myButton(centralwidget);
        A1_50->setObjectName(QString::fromUtf8("A1_50"));
        A1_50->setGeometry(QRect(377, 551, 70, 30));
        sec = new QLabel(centralwidget);
        sec->setObjectName(QString::fromUtf8("sec"));
        sec->setGeometry(QRect(320, 30, 58, 16));
        sec->setStyleSheet(QString::fromUtf8("background:rgba(255, 255, 255, 0);\n"
"color:rgb(251, 255, 255);\n"
"font: 13pt \"Andale Mono\";"));
        A1_21 = new myButton(centralwidget);
        A1_21->setObjectName(QString::fromUtf8("A1_21"));
        A1_21->setGeometry(QRect(53, 280, 70, 30));
        A1_22 = new myButton(centralwidget);
        A1_22->setObjectName(QString::fromUtf8("A1_22"));
        A1_22->setGeometry(QRect(134, 280, 70, 30));
        B1 = new myButton(centralwidget);
        B1->setObjectName(QString::fromUtf8("B1"));
        B1->setGeometry(QRect(134, 181, 70, 30));
        B1_2 = new myButton(centralwidget);
        B1_2->setObjectName(QString::fromUtf8("B1_2"));
        B1_2->setGeometry(QRect(295, 181, 70, 30));
        B1_3 = new myButton(centralwidget);
        B1_3->setObjectName(QString::fromUtf8("B1_3"));
        B1_3->setGeometry(QRect(214, 215, 70, 30));
        B1_4 = new myButton(centralwidget);
        B1_4->setObjectName(QString::fromUtf8("B1_4"));
        B1_4->setGeometry(QRect(134, 248, 70, 30));
        B1_5 = new myButton(centralwidget);
        B1_5->setObjectName(QString::fromUtf8("B1_5"));
        B1_5->setGeometry(QRect(295, 248, 70, 30));
        B1_6 = new myButton(centralwidget);
        B1_6->setObjectName(QString::fromUtf8("B1_6"));
        B1_6->setGeometry(QRect(134, 420, 70, 30));
        B1_7 = new myButton(centralwidget);
        B1_7->setObjectName(QString::fromUtf8("B1_7"));
        B1_7->setGeometry(QRect(295, 420, 70, 30));
        B1_8 = new myButton(centralwidget);
        B1_8->setObjectName(QString::fromUtf8("B1_8"));
        B1_8->setGeometry(QRect(214, 452, 70, 30));
        B1_9 = new myButton(centralwidget);
        B1_9->setObjectName(QString::fromUtf8("B1_9"));
        B1_9->setGeometry(QRect(134, 485, 70, 30));
        B1_10 = new myButton(centralwidget);
        B1_10->setObjectName(QString::fromUtf8("B1_10"));
        B1_10->setGeometry(QRect(295, 485, 70, 30));
        theme = new QLabel(centralwidget);
        theme->setObjectName(QString::fromUtf8("theme"));
        theme->setGeometry(QRect(410, 20, 41, 31));
        severState = new QLabel(centralwidget);
        severState->setObjectName(QString::fromUtf8("severState"));
        severState->setGeometry(QRect(10, 670, 121, 16));
        severState->setStyleSheet(QString::fromUtf8("background:rgba(255, 255, 255, 0);\n"
"color:rgb(251, 255, 255);\n"
"font: 13pt \"Andale Mono\";"));
        label1 = new QLabel(centralwidget);
        label1->setObjectName(QString::fromUtf8("label1"));
        label1->setGeometry(QRect(10, 660, 58, 16));
        label1->setStyleSheet(QString::fromUtf8("background:rgba(255, 255, 255, 0);\n"
"color:rgb(251, 255, 255);\n"
"font: 13pt \"Andale Mono\";"));
        label3 = new QLabel(centralwidget);
        label3->setObjectName(QString::fromUtf8("label3"));
        label3->setGeometry(QRect(10, 680, 161, 16));
        label3->setStyleSheet(QString::fromUtf8("background:rgba(255, 255, 255, 0);\n"
"color:rgb(251, 255, 255);\n"
"font: 13pt \"Andale Mono\";"));
        label2 = new QLabel(centralwidget);
        label2->setObjectName(QString::fromUtf8("label2"));
        label2->setGeometry(QRect(100, 660, 58, 16));
        label2->setStyleSheet(QString::fromUtf8("background:rgba(255, 255, 255, 0);\n"
"color:rgb(251, 255, 255);\n"
"font: 13pt \"Andale Mono\";"));
        roundCount = new QLabel(centralwidget);
        roundCount->setObjectName(QString::fromUtf8("roundCount"));
        roundCount->setGeometry(QRect(70, 660, 21, 16));
        roundCount->setStyleSheet(QString::fromUtf8("background:rgba(255, 255, 255, 0);\n"
"color:rgb(251, 255, 255);\n"
"font: 13pt \"Andale Mono\";"));
        timeoutCount = new QLabel(centralwidget);
        timeoutCount->setObjectName(QString::fromUtf8("timeoutCount"));
        timeoutCount->setGeometry(QRect(170, 680, 21, 16));
        timeoutCount->setStyleSheet(QString::fromUtf8("background:rgba(255, 255, 255, 0);\n"
"color:rgb(251, 255, 255);\n"
"font: 13pt \"Andale Mono\";"));
        quit = new QPushButton(centralwidget);
        quit->setObjectName(QString::fromUtf8("quit"));
        quit->setGeometry(QRect(400, 660, 91, 31));
        quit->setStyleSheet(QString::fromUtf8("border:transparent;\n"
"color:rgb(255, 255, 255);\n"
"font: 13pt \"Andale Mono\";"));
        MainWindow->setCentralWidget(centralwidget);
        menu = new QMenuBar(MainWindow);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu->setGeometry(QRect(0, 0, 500, 22));
        menuService = new QMenu(menu);
        menuService->setObjectName(QString::fromUtf8("menuService"));
        MainWindow->setMenuBar(menu);

        menu->addAction(menuService->menuAction());
        menuService->addAction(actConnect);
        menuService->addAction(actCreate);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Military Chess Game", nullptr));
        actConnect->setText(QCoreApplication::translate("MainWindow", "Connect to Service", nullptr));
#if QT_CONFIG(tooltip)
        actConnect->setToolTip(QCoreApplication::translate("MainWindow", "Connect to a Existed Service", nullptr));
#endif // QT_CONFIG(tooltip)
        actCreate->setText(QCoreApplication::translate("MainWindow", "Create New Service", nullptr));
#if QT_CONFIG(tooltip)
        actCreate->setToolTip(QCoreApplication::translate("MainWindow", "Create a New Service", nullptr));
#endif // QT_CONFIG(tooltip)
        admitDefeat->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        newGame->setText(QString());
        titleNewGame->setText(QCoreApplication::translate("MainWindow", "New Game", nullptr));
        admit->setText(QCoreApplication::translate("MainWindow", "Admit Defeat", nullptr));
        warningText->setText(QString());
        blankBoard->setText(QString());
        countDown->setText(QString());
        notice->setText(QString());
        youAre->setText(QCoreApplication::translate("MainWindow", "Your Are:", nullptr));
        remainTime->setText(QCoreApplication::translate("MainWindow", "Remain Time", nullptr));
        A1->setText(QString());
        A1_2->setText(QString());
        A1_3->setText(QString());
        A1_4->setText(QString());
        A1_5->setText(QString());
        A1_6->setText(QString());
        A1_7->setText(QString());
        A1_8->setText(QString());
        A1_9->setText(QString());
        A1_10->setText(QString());
        A1_11->setText(QString());
        A1_12->setText(QString());
        A1_13->setText(QString());
        A1_14->setText(QString());
        A1_15->setText(QString());
        A1_16->setText(QString());
        A1_17->setText(QString());
        A1_18->setText(QString());
        A1_19->setText(QString());
        A1_20->setText(QString());
        A1_23->setText(QString());
        A1_24->setText(QString());
        A1_25->setText(QString());
        A1_26->setText(QString());
        A1_27->setText(QString());
        A1_28->setText(QString());
        A1_29->setText(QString());
        A1_30->setText(QString());
        A1_31->setText(QString());
        A1_32->setText(QString());
        A1_33->setText(QString());
        A1_34->setText(QString());
        A1_35->setText(QString());
        A1_36->setText(QString());
        A1_37->setText(QString());
        A1_38->setText(QString());
        A1_39->setText(QString());
        A1_40->setText(QString());
        A1_41->setText(QString());
        A1_42->setText(QString());
        A1_43->setText(QString());
        A1_44->setText(QString());
        A1_45->setText(QString());
        A1_46->setText(QString());
        A1_47->setText(QString());
        A1_48->setText(QString());
        A1_49->setText(QString());
        A1_50->setText(QString());
        sec->setText(QCoreApplication::translate("MainWindow", "sec", nullptr));
        A1_21->setText(QString());
        A1_22->setText(QString());
        B1->setText(QString());
        B1_2->setText(QString());
        B1_3->setText(QString());
        B1_4->setText(QString());
        B1_5->setText(QString());
        B1_6->setText(QString());
        B1_7->setText(QString());
        B1_8->setText(QString());
        B1_9->setText(QString());
        B1_10->setText(QString());
        theme->setText(QString());
        severState->setText(QString());
        label1->setText(QCoreApplication::translate("MainWindow", "This is ", nullptr));
        label3->setText(QCoreApplication::translate("MainWindow", "Total timeout count:", nullptr));
        label2->setText(QCoreApplication::translate("MainWindow", "round.", nullptr));
        roundCount->setText(QCoreApplication::translate("MainWindow", "10", nullptr));
        timeoutCount->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        quit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        menuService->setTitle(QCoreApplication::translate("MainWindow", "Service", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
