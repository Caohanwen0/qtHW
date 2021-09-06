#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include <QMainWindow>
#include <QFont>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QPalette>
#include <QKeyEvent>
#include <QPainter>
#include <QGroupBox>
#include <QPainter>
#include <QDir>
#include <QPushButton>
#include <QPixmap>
#include <QtNetwork>

#include "create_server.h"
#include "connect_server.h"
#include "mybutton.h"
#include "myresult.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTcpServer* server = NULL;
    QTcpSocket* socket = NULL;
    create_server* create_Server = NULL;
    connect_server* connect_Server = NULL;
    myResult* m_result;//结果弹窗
    myButton* firstButton;
    QTimer* Timerflush;
    QPixmap* blankboard;
    int time_out_count = 0;
    bool isServer;
    bool isRed;
    int index[50];//储存五十个编号！！
    int result[50];
    int dismissBomb = 0;
    bool map[65][65];
    bool map_railway[65][65];
    int whos_turn = 0;
    bool visit[65];
    bool themeDecided = false;
    bool first3round[3];
    int flipround = 0;//记录该谁出牌了
    int round = 0;//记录游戏轮数

private slots:
    void generateMap();
    void waiting();
    void letServergenerateResult();
    void setButtonUnavailable();
    void setButtonAvailable();
    void initIndex();
    void initButton();
    void generateResult();
    void createServer();
    void connectServer();
    void newGame();
    void newGame_client();
    void lose(bool);
    void win(bool);
    void flush_countdown();
    void my_turn();
    void flipOnlyRound();
    void onClicked(myButton* );
    void setOnClick();
    void flipCard(myButton* );
    void movePiece(myButton* ,myButton*);
    bool moveAble(const myButton* ,const myButton*);
    int btn_to_index(const myButton* );//将按钮转化为对应编号
    myButton* convert_location(int,int);//将地址(x,y)转化为对应按钮
    void updateButtons();
    void determineTheme(bool);
    bool onRailRoad(const myButton* );//按钮是否在铁路上
    bool dfs(int,int,int,int);
    void on_time_out();
    void analyseType(bool);
    void assignButtonType();
    void endGame();
    void flipOnly(myButton*);
    void setFlipOnly();
    void on_actConnect_triggered();
    void on_createConnect_triggered();
    void onSocketReadyRead();
    void server_close();
    bool buttonCanMove(const myButton*);
    bool haveMovingBtnLeft();
};
#endif // MAINWINDOW_H
