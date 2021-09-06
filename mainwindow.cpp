#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFont>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QPalette>
#include <QKeyEvent>
#include <QGroupBox>
#include <QPainter>
#include <QDir>
#include <QSize>
#include <QTimer>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),create_Server(new create_server(this)),connect_Server(new connect_server(this)),firstButton(NULL)
{
    qDebug()<<"set chessboard";
    ui->setupUi(this);
    ui->notice->setText("   Welcome to Military Chess!");
    ui->countDown->hide();
    ui->theme->hide();
    ui->sec->hide();
    ui->youAre->hide();
    ui->remainTime->hide();
    ui->roundCount->hide();
    ui->timeoutCount->hide();
    ui->label1->hide();
    ui->label2->hide();
    ui->label3->hide();
    ui->admit->hide();
    ui->admitDefeat->hide();
    ui->admitDefeat->setEnabled(false);

    ui->quit->setIconSize(QSize(70,30));
    ui->quit->hide();
    ui->newGame->hide();
    ui->titleNewGame->hide();
    connect(ui->admitDefeat,&QPushButton::clicked,this,[&](){lose(false);});
    Timerflush = new QTimer(this);
    connect(ui->actCreate,SIGNAL(triggered()),this,SLOT(createServer()));
    connect(ui->actConnect,SIGNAL(triggered()),this,SLOT(connectServer()));
}

void MainWindow::on_createConnect_triggered(){//当按下两个弹窗上面的按钮的时候调用这两个函数
    isServer = true;
    QString listen= "Listening";
    server = new QTcpServer(this);
    //先开始tcp监听，以等待tcp客户端的接入
    QString localIP = create_Server->getLocalIP();
    QHostAddress addr(localIP);
    server->listen(addr,6666);//在本机监听
    if (server->isListening())create_Server->setStatus(listen);
    qDebug()<<"QHostAddress:"<<QHostAddress::LocalHost;
    connect(server,SIGNAL(newConnection()),this,SLOT(waiting()));//当有客户端连接上了的时候，开始新游戏
}

void MainWindow::waiting(){
    ui->newGame->show();
    ui->titleNewGame->show();
    if (isServer){
        socket = server->nextPendingConnection();
        connect(socket,SIGNAL(disconnected()),this,SLOT(endGame()));
        connect(socket,SIGNAL(readyRead()),this,SLOT(onSocketReadyRead()));
        ui->quit->setText("Disconnect");
        connect(ui->quit,SIGNAL(clicked()),this,SLOT(endGame()));
        ui->quit->show();
        ui->menu->setStyleSheet("QMenuBar{background:rgb(255, 0, 0);}");
        create_Server->close();
        connect(ui->newGame,SIGNAL(clicked()),this,SLOT(generateResult()));}
    else {
        connect_Server->close();
        connect(socket,SIGNAL(readyRead()),this,SLOT(onSocketReadyRead()));//如果接收到了数据，调用onSocketReadyRead;
        connect(ui->newGame,SIGNAL(clicked()),this,SLOT(letServergenerateResult()));
    }
}

void MainWindow::letServergenerateResult(){
    qDebug()<<"letServergenerateResult";
    QString newGame = "newGame/";
    socket->write(newGame.toUtf8());
    socket->flush();
}

void MainWindow::on_actConnect_triggered(){//当按下两个弹窗上面的按钮的时候调用这两个函数
    isServer = false;
    QString IP = connect_Server->getInput();//用connect_Server的public函数访问其input的IP
    socket = new QTcpSocket(this);
    if (connect_Server->acceptAble()){
        connect_Server->showMsg("Connecting...");
        socket->connectToHost(IP,6666);
    }
    else {connect_Server->showMsg("Wrong Format.");connect_Server->clearInput();}
    connect(socket,SIGNAL(connected()),this,SLOT(waiting()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(endGame()));//如果断开了服务器，调用endGame函数；
    ui->quit->setText("Disconnect");
    connect(ui->quit,SIGNAL(clicked()),this,SLOT(endGame()));
    ui->quit->show();
}

void MainWindow::endGame(){
    Timerflush->stop();
    ui->sec->hide();
    ui->countDown->hide();
    ui->remainTime->hide();
    ui->admit->hide();
    ui->admitDefeat->hide();
    ui->admitDefeat->setEnabled(false);
    if (!isServer) {socket->disconnectFromHost();}
    else socket->close();
    ui->notice->setText("Disconnected");
    ui->quit->setText("Close");
    ui->quit->disconnect();
    if (!isServer)connect(ui->quit,SIGNAL(clicked()),this,SLOT(close()));
    else connect(ui->quit,SIGNAL(clicked()),this,SLOT(server_close()));
}

void MainWindow::server_close(){
    if (server->isListening()){
        server->close();
    }
    close();
}

void MainWindow::generateResult(){
    qDebug()<<"generateResult";
    //generate socket
    generateMap();
    initIndex();
    Timerflush->setInterval(1000);
    connect(Timerflush,SIGNAL(timeout()),this,SLOT(flush_countdown()));
    //generate result
    int seq[50];
    for (int i=0; i<50; i++) seq[i] = i;
    //generate random board layout
    //先得到一个1到50的无重复随机顺序排列
    //再按照这个排列得到一个类型的随机排列
    //最后照着类型的随机排列依次给所有button的类型赋值～
    for (int i=0; i<50; i++){
        int rand = QRandomGenerator::global()->bounded(0, 50-i);//依次生成0-50，0-49，...的随机数
        int temp = seq[rand];
        seq[rand] = seq[49-i];
        seq[49-i] = temp;
    }
    for (int i=0;i<50;i++){
        result[i] = index[seq[i]];
    }

    // giving each button a value via the result[];
    assignButtonType();
    initButton();
    updateButtons();

    //send result[] to client
    QString kw = "result/";
    //transmitClient(kw);
    for (int i=0;i<50;i++){
        kw = kw + QString::number(result[i]) + "/";
    }
    socket->write(kw.toUtf8());
    socket->flush();
}

void MainWindow::onSocketReadyRead(){//use key words:"theme""result""move""win_lose""rand"
    QString buffer = socket->readAll();
    QStringList arr = buffer.split("/");
    if (arr[0]=="newGame"){
        qDebug()<<"newGame received";
        generateResult();
    }
    else if (arr[0]=="theme"){
        qDebug()<<"Theme received";
        themeDecided = true;
        //first,we flip the piece for which the other ultimately decide his/her theme
        int x = (arr[1].toInt());
        int y = (arr[2].toInt());
        qDebug()<<"The other flip card.";
        qDebug()<<"the location of btn the other flipped:("<<x<<","<<y<<")";
        myButton *tmp = convert_location(x,y);
        tmp->known=true;
        tmp->myupdate();
        //then we set our own theme and get on with another round
        QString my_theme = arr[3];
        if (my_theme=="red") {
            qDebug()<<"I receive my Theme.I am red.";
            isRed = true;
            ui->theme->setStyleSheet("QLabel{background:rgb(255, 0, 0);}");
            ui->theme->show();
            ui->youAre->show();
            analyseType(isRed);
            setOnClick();
            my_turn();
        }
        else {
            qDebug()<<"I receive my Theme.I am blue.";
            isRed = false;
            ui->theme->setStyleSheet("QLabel{background:rgb(4, 73, 255);}");
            ui->theme->show();
            ui->youAre->show();
            analyseType(isRed);
            setOnClick();
            my_turn();
        }
    }
    else if (arr[0]=="result"){
        qDebug()<<"result received";
        for (int i=1;i<=50;i++){
            result[i-1] = arr[i].toInt();
        }
        QString confirm = "confirmResult/";
        socket->write(confirm.toUtf8());
        socket->flush();
        newGame_client();
    }
    else if (arr[0]=="confirmResult"){//只有服务器才能收到confirmResult！此时调用服务器的newGame
        newGame();
    }
    else if (arr[0]=="move"){
        qDebug()<<"move received";
        int x1 = arr[1].toInt();
        int x2 = arr[2].toInt();
        int y1 = arr[3].toInt();
        int y2 = arr[4].toInt();
        myButton* tmp1 = convert_location(x1,y1);
        myButton* tmp2 = convert_location(x2,y2);
        qDebug()<<"move ("<<x1<<","<<y1<<") to ("<<x2<<","<<y2<<").";
        if (tmp2->type == 3 || tmp2->type == 300){//如果对方是炸弹
            if (tmp1->type!=4 && tmp1->type!=400){//并且我不是工兵
                tmp1->type = 0;
                tmp2->type = 0;
                tmp1->myupdate();
                tmp2->myupdate();
            }
        }
        else if ((tmp1->type == 3 || tmp1->type == 300)&&(tmp2->type!=0)){//如果我是炸弹，对面不是空
            tmp1->type = 0;
            tmp2->type = 0;
            tmp1->myupdate();
            tmp2->myupdate();
        }
        else if ((tmp1->type == tmp2->type/100)||(tmp2->type == tmp1->type/100)){
            if (tmp1->type!=0 && tmp2->type!=0){
                tmp1->type = 0;
                tmp2->type = 0;
                tmp1->myupdate();
                tmp2->myupdate();
            }
            else{
                tmp2->myPiece = tmp1->myPiece;
                tmp2->type = tmp1->type;
                tmp2->known = true;
                tmp1->type = 0;
                tmp1->myupdate();
                tmp2->myupdate();
            }
        }
        else{
            tmp2->myPiece = tmp1->myPiece;
            tmp2->type = tmp1->type;
            tmp2->known = true;
            tmp1->type = 0;
            tmp1->myupdate();
            tmp2->myupdate();}//现在移动完成了，进入下一轮
        if (themeDecided){
            if (haveMovingBtnLeft()){qDebug()<<"onSocketReadyRead-move-my_turn";my_turn();}
            else lose(false);
        }
        else flipOnlyRound();
    }
    else if (arr[0]=="win_lose"){
        qDebug()<<"win_lose received";
        QString res = arr[1];
        if (res=="win") win(true);
        else if (res=="lose") lose(true);
    }
    else if(arr[0]=="rand"){
        qDebug()<<"rand reiceived";
        QString res = arr[1];
        if (res=="true") determineTheme(true);
        else if (res=="false") determineTheme(false);
    }
    else if (arr[0]=="flip"){
        qDebug()<<"flip message received";
        int x = arr[1].toInt();
        int y = arr[2].toInt();
        qDebug()<<"the location of btn the other flipped:("<<x<<","<<y<<")";
        myButton *tmp = convert_location(x,y);
        tmp->known=true;
        tmp->myupdate();
        if (themeDecided) {
            if (haveMovingBtnLeft()){
                qDebug()<<"onSocketReadyRead-flip-my_turn";
                my_turn();}
            else lose(false);
        }
        else flipOnlyRound();
    }
    else if (arr[0]=="nextFlipOnlyRound"){//在一方time out 的时候调用
        qDebug()<<"nextFlipOnlyRound Receive.";
        flipOnlyRound();
    }
    else if (arr[0]=="nextRound"){//在一方time out的时候调用
        qDebug()<<"nextRound Receive.-my_turn";
        my_turn();
    }
    else{
        qDebug()<<"wrong key";
        qDebug()<<"you have sent key:"<<arr[0];
    }

}

void MainWindow::newGame_client(){
    qDebug()<<"I am Client(And I am in newGame_client();)";
    generateMap();
    Timerflush->setInterval(1000);
    connect(Timerflush,SIGNAL(timeout()),this,SLOT(flush_countdown()));
    assignButtonType();
    initButton();
    updateButtons();//now the whole pic should be ready
    //get into determine theme function!
    setFlipOnly();
}

void MainWindow::generateMap(){
    qDebug()<<"generate Map";
    for (int i=0;i<65;i++){
        for (int j=0;j<65;j++){
            map[i][j]=0;
            map_railway[i][j]=0;
        }
    }
    for (int i=0;i<=60;i++)map[i][i]=1;
    for (int i=1;i<=56;i+=5){//横排
        map[i][i+1]=1;
        map[i+1][i+2]=1;
        map[i+2][i+3]=1;
        map[i+3][i+4]=1;
        map[i+1][i]=1;
        map[i+2][i+1]=1;
        map[i+3][i+2]=1;
        map[i+4][i+3]=1;
    }
    for (int i=6;i<=24;i+=6){map[i][i+6]=1;map[i+6][i]=1;}
    for (int i=8;i<=14;i+=6){map[i][i+6]=1;map[i+6][i]=1;}
    for (int i=16;i<=22;i+=6){map[i][i+6]=1;map[i+6][i]=1;}
    for (int i=8;i<=12;i+=4){map[i][i+4]=1;map[i+4][i]=1;}
    for (int i=10;i<=22;i+=4){map[i][i+4]=1;map[i+4][i]=1;}
    for (int i=20;i<=24;i+=4){map[i][i+4]=1;map[i+4][i]=1;}//上半部分的左斜线和右斜线
    for (int i=31;i<=49;i+=6){map[i][i+6]=1;map[i+6][i]=1;}
    for (int i=33;i<=39;i+=6){map[i][i+6]=1;map[i+6][i]=1;}
    for (int i=41;i<=47;i+=6){map[i][i+6]=1;map[i+6][i]=1;}
    for (int i=33;i<=41;i+=4){map[i][i+4]=1;map[i+4][i]=1;}
    for (int i=35;i<=47;i+=4){map[i][i+4]=1;map[i+4][i]=1;}
    for (int i=45;i<=49;i+=4){map[i][i+4]=1;map[i+4][i]=1;}//下半部分的左斜线和右斜线
    for (int i=1;i<=5;i++){//竖排
        map[i][i+5]=1;map[i+5][i]=1;
        map[i+5][i+10]=1;map[i+10][i+5]=1;
        map[i+10][i+15]=1;map[i+15][i+10]=1;
        map[i+15][i+20]=1;map[i+20][i+15]=1;
        map[i+20][i+25]=1;map[i+25][i+20]=1;
        map[i+25][i+30]=1;map[i+30][i+25]=1;
        map[i+30][i+35]=1;map[i+35][i+30]=1;
        map[i+35][i+40]=1;map[i+40][i+35]=1;
        map[i+40][i+45]=1;map[i+45][i+40]=1;
        map[i+45][i+50]=1;map[i+50][i+45]=1;
        map[i+50][i+55]=1;map[i+55][i+50]=1;
    }
    for (int i=6;i<=9;i++){
        map_railway[i][i+1]=1;map_railway[i+1][i]=1;
        map_railway[i+20][i+21]=1;map_railway[i+21][i+20]=1;
        map_railway[i+25][i+26]=1;map_railway[i+26][i+25]=1;
        map_railway[i+45][i+46]=1;map_railway[i+46][i+45]=1;//四个横行
    }
    for (int i=6;i<=46;i+=5){
        map_railway[i][i+5]=1;map_railway[i+5][i]=1;
        map_railway[i+4][i+9]=1;map_railway[i+9][i+4]=1;//两个竖行
    }
    map_railway[28][33]=1;map_railway[33][28]=1;//中间那一道
}

void MainWindow::setOnClick(){
    ui->A1->disconnect();
    ui->A1_2->disconnect();
    ui->A1_3->disconnect();
    ui->A1_4->disconnect();
    ui->A1_5->disconnect();
    ui->A1_6->disconnect();
    ui->A1_7->disconnect();
    ui->A1_8->disconnect();
    ui->A1_9->disconnect();
    ui->A1_10->disconnect();
    ui->A1_11->disconnect();
    ui->A1_12->disconnect();
    ui->A1_13->disconnect();
    ui->A1_14->disconnect();
    ui->A1_15->disconnect();
    ui->A1_16->disconnect();
    ui->A1_17->disconnect();
    ui->A1_18->disconnect();
    ui->A1_19->disconnect();
    ui->A1_20->disconnect();
    ui->A1_21->disconnect();
    ui->A1_22->disconnect();
    ui->A1_23->disconnect();
    ui->A1_24->disconnect();
    ui->A1_25->disconnect();
    ui->A1_26->disconnect();
    ui->A1_27->disconnect();
    ui->A1_28->disconnect();
    ui->A1_29->disconnect();
    ui->A1_30->disconnect();
    ui->A1_31->disconnect();
    ui->A1_32->disconnect();
    ui->A1_33->disconnect();
    ui->A1_34->disconnect();
    ui->A1_35->disconnect();
    ui->A1_36->disconnect();
    ui->A1_37->disconnect();
    ui->A1_38->disconnect();
    ui->A1_39->disconnect();
    ui->A1_40->disconnect();
    ui->A1_41->disconnect();
    ui->A1_42->disconnect();
    ui->A1_43->disconnect();
    ui->A1_44->disconnect();
    ui->A1_45->disconnect();
    ui->A1_46->disconnect();
    ui->A1_47->disconnect();
    ui->A1_48->disconnect();
    ui->A1_49->disconnect();
    ui->A1_50->disconnect();
    ui->B1->disconnect();
    ui->B1_2->disconnect();
    ui->B1_3->disconnect();
    ui->B1_4->disconnect();
    ui->B1_5->disconnect();
    ui->B1_6->disconnect();
    ui->B1_7->disconnect();
    ui->B1_8->disconnect();
    ui->B1_9->disconnect();
    ui->B1_10->disconnect();
    qDebug()<<"reconnect every button to onClick(),instead of flipOnly().";
    connect(ui->A1,&myButton::clicked,this,[&](){this->onClicked(ui->A1);});
    connect(ui->A1_2,&myButton::clicked,this,[&](){this->onClicked(ui->A1_2);});
    connect(ui->A1_3,&myButton::clicked,this,[&](){this->onClicked(ui->A1_3);});
    connect(ui->A1_4,&myButton::clicked,this,[&](){this->onClicked(ui->A1_4);});
    connect(ui->A1_5,&myButton::clicked,this,[&](){this->onClicked(ui->A1_5);});
    connect(ui->A1_6,&myButton::clicked,this,[&](){this->onClicked(ui->A1_6);});
    connect(ui->A1_7,&myButton::clicked,this,[&](){this->onClicked(ui->A1_7);});
    connect(ui->A1_8,&myButton::clicked,this,[&](){this->onClicked(ui->A1_8);});
    connect(ui->A1_9,&myButton::clicked,this,[&](){this->onClicked(ui->A1_9);});
    connect(ui->A1_10,&myButton::clicked,this,[&](){this->onClicked(ui->A1_10);});
    connect(ui->A1_11,&myButton::clicked,this,[&](){this->onClicked(ui->A1_11);});
    connect(ui->A1_12,&myButton::clicked,this,[&](){this->onClicked(ui->A1_12);});
    connect(ui->A1_13,&myButton::clicked,this,[&](){this->onClicked(ui->A1_13);});
    connect(ui->A1_14,&myButton::clicked,this,[&](){this->onClicked(ui->A1_14);});
    connect(ui->A1_15,&myButton::clicked,this,[&](){this->onClicked(ui->A1_15);});
    connect(ui->A1_16,&myButton::clicked,this,[&](){this->onClicked(ui->A1_16);});
    connect(ui->A1_17,&myButton::clicked,this,[&](){this->onClicked(ui->A1_17);});
    connect(ui->A1_18,&myButton::clicked,this,[&](){this->onClicked(ui->A1_18);});
    connect(ui->A1_19,&myButton::clicked,this,[&](){this->onClicked(ui->A1_19);});
    connect(ui->A1_20,&myButton::clicked,this,[&](){this->onClicked(ui->A1_20);});
    connect(ui->A1_21,&myButton::clicked,this,[&](){this->onClicked(ui->A1_21);});
    connect(ui->A1_22,&myButton::clicked,this,[&](){this->onClicked(ui->A1_22);});
    connect(ui->A1_23,&myButton::clicked,this,[&](){this->onClicked(ui->A1_23);});
    connect(ui->A1_24,&myButton::clicked,this,[&](){this->onClicked(ui->A1_24);});
    connect(ui->A1_25,&myButton::clicked,this,[&](){this->onClicked(ui->A1_25);});
    connect(ui->A1_26,&myButton::clicked,this,[&](){this->onClicked(ui->A1_26);});
    connect(ui->A1_27,&myButton::clicked,this,[&](){this->onClicked(ui->A1_27);});
    connect(ui->A1_28,&myButton::clicked,this,[&](){this->onClicked(ui->A1_28);});
    connect(ui->A1_29,&myButton::clicked,this,[&](){this->onClicked(ui->A1_29);});
    connect(ui->A1_30,&myButton::clicked,this,[&](){this->onClicked(ui->A1_30);});
    connect(ui->A1_31,&myButton::clicked,this,[&](){this->onClicked(ui->A1_31);});
    connect(ui->A1_32,&myButton::clicked,this,[&](){this->onClicked(ui->A1_32);});
    connect(ui->A1_33,&myButton::clicked,this,[&](){this->onClicked(ui->A1_33);});
    connect(ui->A1_34,&myButton::clicked,this,[&](){this->onClicked(ui->A1_34);});
    connect(ui->A1_35,&myButton::clicked,this,[&](){this->onClicked(ui->A1_35);});
    connect(ui->A1_36,&myButton::clicked,this,[&](){this->onClicked(ui->A1_36);});
    connect(ui->A1_37,&myButton::clicked,this,[&](){this->onClicked(ui->A1_37);});
    connect(ui->A1_38,&myButton::clicked,this,[&](){this->onClicked(ui->A1_38);});
    connect(ui->A1_39,&myButton::clicked,this,[&](){this->onClicked(ui->A1_39);});
    connect(ui->A1_40,&myButton::clicked,this,[&](){this->onClicked(ui->A1_40);});
    connect(ui->A1_41,&myButton::clicked,this,[&](){this->onClicked(ui->A1_41);});
    connect(ui->A1_42,&myButton::clicked,this,[&](){this->onClicked(ui->A1_42);});
    connect(ui->A1_43,&myButton::clicked,this,[&](){this->onClicked(ui->A1_43);});
    connect(ui->A1_44,&myButton::clicked,this,[&](){this->onClicked(ui->A1_44);});
    connect(ui->A1_45,&myButton::clicked,this,[&](){this->onClicked(ui->A1_45);});
    connect(ui->A1_46,&myButton::clicked,this,[&](){this->onClicked(ui->A1_46);});
    connect(ui->A1_47,&myButton::clicked,this,[&](){this->onClicked(ui->A1_47);});
    connect(ui->A1_48,&myButton::clicked,this,[&](){this->onClicked(ui->A1_48);});
    connect(ui->A1_49,&myButton::clicked,this,[&](){this->onClicked(ui->A1_49);});
    connect(ui->A1_50,&myButton::clicked,this,[&](){this->onClicked(ui->A1_50);});
    connect(ui->B1,&myButton::clicked,this,[&](){this->onClicked(ui->B1);});
    connect(ui->B1_2,&myButton::clicked,this,[&](){this->onClicked(ui->B1_2);});
    connect(ui->B1_3,&myButton::clicked,this,[&](){this->onClicked(ui->B1_3);});
    connect(ui->B1_4,&myButton::clicked,this,[&](){this->onClicked(ui->B1_4);});
    connect(ui->B1_5,&myButton::clicked,this,[&](){this->onClicked(ui->B1_5);});
    connect(ui->B1_6,&myButton::clicked,this,[&](){this->onClicked(ui->B1_6);});
    connect(ui->B1_7,&myButton::clicked,this,[&](){this->onClicked(ui->B1_7);});
    connect(ui->B1_8,&myButton::clicked,this,[&](){this->onClicked(ui->B1_8);});
    connect(ui->B1_9,&myButton::clicked,this,[&](){this->onClicked(ui->B1_9);});
    connect(ui->B1_10,&myButton::clicked,this,[&](){this->onClicked(ui->B1_10);});
}

void MainWindow::newGame(){
    //目前为止，按钮的myPiece属性还没有被更新过
    //并且现在按钮还按不了
    //必须等到client端收到result，绘制好棋盘（也就是说也执行到这一步），才能开始下面的determineTheme工作。
    setFlipOnly();
    int rand = QRandomGenerator::global()->bounded(1,3);
    if (rand%2==0){
        QString kw = "rand/false/";
        socket->write(kw.toUtf8());
        socket->flush();
        determineTheme(true);}
    else {
        QString kw = "rand/true/";
        socket->write(kw.toUtf8());
        socket->flush();
        determineTheme(false);}
}

void MainWindow::onClicked(myButton* btn){
    ui->A1->numClicks_++;
    if (btn->numClicks_==1 && btn->known==false && btn->type!=0){//翻牌
        qDebug()<<"onClicked():flip card.";
        QString flip = "flip/";
        flip = flip + QString::number(btn->x) + "/";
        flip = flip + QString::number(btn->y) + "/";
        socket->write(flip.toUtf8());
        socket->flush();
        qDebug()<<"sending flip message to the other.The location of btn is("<<btn->x<<","<<btn->y<<")";
        flipCard(btn);
        qDebug()<<"onClicked-my_turn";
        my_turn();
    }
    else if (ui->A1->numClicks_==1 && btn->myPiece==true && btn->known==true && btn->type!=0){//如果这是第一次敲击，并且敲击的是我的棋子
        if (btn->type == 100 || btn->type == 1){
            btn->wrongMove();
        }
        else if (btn->type == 2 || btn->type == 200){
            btn->wrongMove();
        }
        else{
            firstButton = btn;
            qDebug()<<"A button was selected";
            btn->btnSelected = 1;
            btn->myupdate();
            return;
        }
    }
    else if (ui->A1->numClicks_==2){//第二次敲击，这时需要移动棋子
        for (int i=0;i<65;i++) visit[i]=false;
        if (moveAble(firstButton,btn)) {
            movePiece(firstButton,btn);
        }
        else{//如果不能移动
            qDebug()<<"wrongMove()at 2rd click because it's unmoveable";
            firstButton->btnSelected = 0;
            btn->btnSelected = 0;
            btn->wrongMove();
            firstButton->myupdate();
        }
    }
    else{
        if (firstButton!=NULL){firstButton->btnSelected = 0;firstButton->myupdate();}
        btn->btnSelected = 0;
        btn->wrongMove();
    }
}

void MainWindow::flipOnly(myButton* btn){
    qDebug()<<"upon clicking a button in flip only mode";
    if (btn->known==false && btn->type!=0){//如果翻开的棋子是还没翻开过的棋子,并且翻开的地方不是空
        btn->known=true;
        btn->myupdate();
        if (btn->type>100) first3round[flipround]=false;//first3round记录的是：是否是红色（红色:true,蓝色：false）
        else first3round[flipround]=true;
        if (flipround==1){
            //if it's my round 2,and I get two same color
            if (first3round[1]==first3round[0]){
                themeDecided = true;
                if (first3round[0]==true) isRed = true;
                else isRed = false;
                analyseType(isRed);
                if (isRed){
                    qDebug()<<"flipOnly() called.I am red";
                    ui->theme->setStyleSheet("QLabel{background:rgb(255, 0, 0);}");
                    //send message to the other
                    QString kw = "theme/";
                    //QString thm = "blue";
                    //transmitClient(kw);
                    kw = kw + QString::number(btn->x) + "/";
                    kw = kw + QString::number(btn->y) + "/blue/";
                    //QString btn_x = QString::number(btn->x);
                    //QString btn_y = QString::number(btn->y);
                    socket->write(kw.toUtf8());
                    socket->flush();
                }
                else {
                    qDebug()<<"flipOnly() called.I am blue";
                    ui->theme->setStyleSheet("QLabel{background:rgb(4, 73, 255);}");
                    //send message to the other
                    QString kw = "theme/";
                    kw = kw + QString::number(btn->x) + "/";
                    kw = kw + QString::number(btn->y) + "/red/";
                    socket->write(kw.toUtf8());
                    socket->flush();
                }
                ui->theme->show();
                ui->youAre->show();
                qDebug()<<"in flipOnly(),I setOnClick() and begin a my_turn();this should be the first and only time.";
                setOnClick();
                my_turn();
                return;
            }
        }
        else if (flipround==2){
            if (first3round[2]==first3round[0]){
                themeDecided = true;
                if (first3round[0]==true) isRed = true;
                else isRed = false;
                analyseType(isRed);
                if (isRed){
                    qDebug()<<"flipOnly() called.I am red";
                    ui->theme->setStyleSheet("QLabel{background:rgb(255, 0, 0);}");
                    //send message to the other
                    QString kw = "theme/";
                    //QString thm = "blue";
                    //transmitClient(kw);
                    kw = kw + QString::number(btn->x) + "/";
                    kw = kw + QString::number(btn->y) + "/blue/";
                    socket->write(kw.toUtf8());
                    socket->flush();
                }
                else {
                    qDebug()<<"flipOnly() called.I am blue";
                    ui->theme->setStyleSheet("QLabel{background:rgb(4, 73, 255);}");
                    //send message to the other
                    QString kw = "theme/";
                    kw = kw + QString::number(btn->x) + "/";
                    kw = kw + QString::number(btn->y) + "/red/";
                    socket->write(kw.toUtf8());
                    socket->flush();
                }
                ui->theme->show();
                ui->youAre->show();
                setOnClick();
                qDebug()<<"theme decided and transmitted.";
                my_turn();
                return;
            }
            else if (first3round[2]==first3round[1]){
                themeDecided = true;
                if (first3round[1]==true) isRed = true;
                else isRed = false;
                analyseType(isRed);
                if (isRed){
                    qDebug()<<"flipOnly() called.I am red";
                    ui->theme->setStyleSheet("QLabel{background:rgb(255, 0, 0);}");
                    //send message to the other
                    QString kw = "theme/";
                    kw = kw + QString::number(btn->x) + "/";
                    kw = kw + QString::number(btn->y) + "/blue/";
                    socket->write(kw.toUtf8());
                    socket->flush();
                }
                else {
                    qDebug()<<"flipOnly() called.I am blue";
                    ui->theme->setStyleSheet("QLabel{background:rgb(4, 73, 255);}");
                    //send message to the other
                    QString kw = "theme/";
                    kw = kw + QString::number(btn->x) + "/";
                    kw = kw + QString::number(btn->y) + "/red/";
                    socket->write(kw.toUtf8());
                    socket->flush();
                }
                ui->theme->show();
                ui->youAre->show();
                setOnClick();
                qDebug()<<"theme decided and transmitted.";
                my_turn();
                return;
            }
        }
        //如果走到这里还没有调用my_turn()，说明现在还没有确定阵营。继续调用flipOnlyRound();
        flipround++;
        QString kw = "flip/";
        //transmitClient(flip);
        kw = kw + QString::number(btn->x) +"/" + QString::number(btn->y) +"/";
        socket->write(kw.toUtf8());
        socket->flush();
        flipOnlyRound();
        return;
    }
    else if (btn->known==true || btn->type==0){
        qDebug()<<"wrongMove() because you have hit a known or blank space";
        btn->wrongMove();
    }//如果点击的是已经被翻面的棋子，或者是空*/
}

void MainWindow::determineTheme(bool myFirst){
    //先设置为只能翻旗的模式
    qDebug()<<"determineTheme.";
    setFlipOnly();
    if (myFirst){
        whos_turn = 0;
    }
    else whos_turn = 1;
    flipOnlyRound();
}

void MainWindow::flipOnlyRound(){//gameround where only flipping card is allowed
    if (!themeDecided){
        whos_turn++;
        round++;
        //set the click movement
        ui->A1->numClicks_=0;
        //set the panel
        if (whos_turn%2==1){
            qDebug()<<"flipOnlyRound,my round happens";
            setButtonAvailable();
            ui->notice->setText("It's Your Turn Now!Go Ahead!");
            ui->notice->show();
            //set the countdown
            ui->sec->show();
            ui->remainTime->show();
            ui->countDown->show();
        }
        else{
            qDebug()<<"flipOnlyRound,other's round happens";
            setButtonUnavailable();
            ui->notice->setText("It's Your Opponent's Turn!");
            ui->sec->show();
            ui->remainTime->show();
            ui->countDown->show();
        }
        ui->roundCount->show();
        ui->timeoutCount->show();
        ui->label1->show();
        ui->label2->show();
        ui->label3->show();
        ui->roundCount->setText(QString::number(round));
        ui->timeoutCount->setText(QString::number(time_out_count));
        //set the countdown
        ui->countDown->setText("20");
        Timerflush->start();
    }
}

int MainWindow::btn_to_index(const myButton * btn){//convert a button to it's index number
    int x = btn->x;
    int y = btn->y;
    int index = (y-1)*5 + x;
    return index;
}

bool MainWindow::moveAble(const myButton* btn1, const myButton* btn2){
    if (!btn2->known){return false;}//如果目的地的牌还没有被翻开
    if (btn1->type>=100 && btn2->type>=100){qDebug()<<"Move Fail.same color";return false;}
    if (btn1->type<100 && btn2->type<100){
        if(btn1->type>0 && btn2->type>0){
            qDebug()<<"Move Fail.same color";return false;
        }
    }//同色不能走
    int tmp1=0;
    int tmp2=0;
    if (btn1->type>=100) {tmp1=(btn1->type)/100;}else {tmp1=btn1->type;}
    if (btn2->type>=100) {tmp2=(btn2->type)/100;}else {tmp2=btn2->type;}
    //确保了起末点不是同一阵营的（起点不为空，但末点有可能为空）
    //if (tmp1==1 || tmp1==2){qDebug()<<"Move Fail.flag or mine can't move";return false;}//旗子和地雷不能走
    //排查btn1可以lay hands on 的x和y范围
    if (map[btn_to_index(btn1)][btn_to_index(btn2)]==true){//如果这两个地方紧邻，不需要动用铁路就能到达
        //qDebug()<<"these two place are adjacent";
        if (btn2->type == 0)return true;//空当然可以移动
        else if (btn2->isStation){qDebug()<<"Move Fail.enemy is protected in station";return false;}//如果目的地是行营，并且目的地有棋子，那么不能移动
        else {//是敌方，但是不在行营，此刻看对方的种类了
            if (tmp2==3){//可以用炸弹自杀
                return true;
            }
            else if (tmp1==3 && tmp2!=1) return true;//可以用炸弹杀别人(包括炸弹、地雷，但不包括军旗）
            else if (tmp2==2 && tmp1==4) return true;//工兵可以排除地雷
            else if (tmp2==2 && tmp1!=4) return false;//不可以解除地雷
            else if (tmp2==1 && dismissBomb>=3) return true;//扛军旗
            else if (tmp2==1) {return false;}//还不能扛军旗
            else if (tmp2>tmp1){
                //qDebug()<<"Move Fail.Your rank is not high enough";
                return false;}
            else return true;
        }
    }
    //下面考虑这两个点不是邻接的情况（邻接包括可以走的斜对角线）
    //起始点或者终点不在铁路上
    //qDebug()<<"these two are not adjacent";
    if (!onRailRoad(btn1) || !onRailRoad(btn2)){qDebug()<<"Move Fail.start or destination not in railway.";return false;}
    //以下默认btn1，btn2都在铁路上
    if (tmp1!=4){//如果不是工兵
        if (btn1->x!= btn2->x && btn1->y!=btn2->y){qDebug()<<"Move Fail.they are both on railway,but different x and y.";return false;}
        if (btn1->x==btn2->x){
            qDebug()<<"they are on the same column of railway";
            int y1 = btn1->y;
            int y2 = btn2->y;
            int max = std::max(y1,y2);
            int min = std::min(y1,y2);
            for (int i=min+1;i<max;i++){
                qDebug()<<"x="<<btn1->x;
                qDebug()<<i;
                if(convert_location(btn1->x,i)->type!=0){qDebug()<<"Move Fail.meet obstacle along railway.";return false;}
            }
            //end for 
        }
        else if (btn1->y==btn2->y){
            qDebug()<<"they are on the same row of railway";
            int x1 = btn1->x;
            int x2 = btn2->x;
            int max = std::max(x1,x2);
            int min = std::min(x1,x2);
            for (int i=min+1;i<max;i++){
                qDebug()<<"y="<<btn1->y;
                qDebug()<<i;
                if(convert_location(i,btn1->y)->type!=0){qDebug()<<"Move Fail.meet obstacle along railway.";return false;}
            }
            //end for
        }
        //现在已经确保了从btn1到btn2有一条通路，现在要排查棋子类型了
        if (btn2->type==0)return true;
        else if (tmp2==3)return true;
        else if (tmp1==3 && tmp2!=1) return true;
        else if (tmp2==2 && tmp1==4) return true;//工兵可以排除地雷
        else if (tmp2==2 && tmp1!=4) return false;//不可以解除地雷
        else if (tmp2==1 && dismissBomb>=3) return true;//扛军旗
        else if (tmp2==1) return false;//还不能扛军旗
        else if (tmp2>tmp1){
            //qDebug()<<"Move Fail.Your rank is not high enough";
            return false;}
        else return true;
    }
    //如果是工兵移动的情况，需要深度优先搜索 此时btn1->type==4｜｜400
    else if (dfs(btn1->x,btn1->y,btn2->x,btn2->y)){//如果从btn1到btn2有【铁路】通路
        if (btn2->type == 0)return true;//目的地是空的并且可以到达
        else if (tmp2==3)return true;//撞炸弹
        else if (tmp1==3 && tmp2!=1) return true;
        else if (tmp2==2 && tmp1==4) return true;//工兵可以排除地雷
        else if (tmp2==2 && tmp1!=4) return false;//不可以解除地雷
        else if (tmp2==1 && dismissBomb>=3) return true;//扛军旗
        else if (tmp2==1) return false;//还不能扛军旗
        else if (tmp2>tmp1){
            //qDebug()<<"Move Fail.Your rank is not high enough";
            return false;}
        else return true;
    }
    else {
        qDebug()<<"bool moveAble()::Warning!Any situation you have not considered?";
        return false;
    }
}

bool MainWindow::haveMovingBtnLeft(){
    qDebug()<<"haveMovingBtnLeft?";
    if (buttonCanMove(ui->A1)==true) return true;
    if (buttonCanMove(ui->A1_2)==true) return true;
    if (buttonCanMove(ui->A1_3)==true) return true;
    if (buttonCanMove(ui->A1_4)==true) return true;
    if (buttonCanMove(ui->A1_5)==true) return true;
    if (buttonCanMove(ui->A1_6)==true) return true;
    if (buttonCanMove(ui->A1_7)==true) return true;
    if (buttonCanMove(ui->A1_8)==true) return true;
    if (buttonCanMove(ui->A1_9)==true) return true;
    if (buttonCanMove(ui->A1_10)==true) return true;
    if (buttonCanMove(ui->A1_11)==true) return true;
    if (buttonCanMove(ui->A1_12)==true) return true;
    if (buttonCanMove(ui->A1_13)==true) return true;
    if (buttonCanMove(ui->A1_14)==true) return true;
    if (buttonCanMove(ui->A1_15)==true) return true;
    if (buttonCanMove(ui->A1_16)==true) return true;
    if (buttonCanMove(ui->A1_17)==true) return true;
    if (buttonCanMove(ui->A1_18)==true) return true;
    if (buttonCanMove(ui->A1_19)==true) return true;
    if (buttonCanMove(ui->A1_20)==true) return true;
    if (buttonCanMove(ui->A1_21)==true) return true;
    if (buttonCanMove(ui->A1_22)==true) return true;
    if (buttonCanMove(ui->A1_23)==true) return true;
    if (buttonCanMove(ui->A1_24)==true) return true;
    if (buttonCanMove(ui->A1_25)==true) return true;
    if (buttonCanMove(ui->A1_26)==true) return true;
    if (buttonCanMove(ui->A1_27)==true) return true;
    if (buttonCanMove(ui->A1_28)==true) return true;
    if (buttonCanMove(ui->A1_29)==true) return true;
    if (buttonCanMove(ui->A1_30)==true) return true;
    if (buttonCanMove(ui->A1_31)==true) return true;
    if (buttonCanMove(ui->A1_32)==true) return true;
    if (buttonCanMove(ui->A1_33)==true) return true;
    if (buttonCanMove(ui->A1_34)==true) return true;
    if (buttonCanMove(ui->A1_35)==true) return true;
    if (buttonCanMove(ui->A1_36)==true) return true;
    if (buttonCanMove(ui->A1_37)==true) return true;
    if (buttonCanMove(ui->A1_38)==true) return true;
    if (buttonCanMove(ui->A1_39)==true) return true;
    if (buttonCanMove(ui->A1_40)==true) return true;
    if (buttonCanMove(ui->A1_41)==true) return true;
    if (buttonCanMove(ui->A1_42)==true) return true;
    if (buttonCanMove(ui->A1_43)==true) return true;
    if (buttonCanMove(ui->A1_44)==true) return true;
    if (buttonCanMove(ui->A1_45)==true) return true;
    if (buttonCanMove(ui->A1_46)==true) return true;
    if (buttonCanMove(ui->A1_47)==true) return true;
    if (buttonCanMove(ui->A1_48)==true) return true;
    if (buttonCanMove(ui->A1_49)==true) return true;
    if (buttonCanMove(ui->A1_50)==true) return true;
    if (buttonCanMove(ui->B1)==true) return true;
    if (buttonCanMove(ui->B1_2)==true) return true;
    if (buttonCanMove(ui->B1_3)==true) return true;
    if (buttonCanMove(ui->B1_4)==true) return true;
    if (buttonCanMove(ui->B1_5)==true) return true;
    if (buttonCanMove(ui->B1_6)==true) return true;
    if (buttonCanMove(ui->B1_7)==true) return true;
    if (buttonCanMove(ui->B1_8)==true) return true;
    if (buttonCanMove(ui->B1_9)==true) return true;
    if (buttonCanMove(ui->B1_10)==true) return true;
    return false;
}

bool MainWindow::buttonCanMove(const myButton* btn){//查询一个btn是否可以【被我】移动
    if (btn->known==false)return true;
    if (!btn->myPiece) return false;//不能移动别人的棋子
    if (btn->type == 0)return false;
    if (btn->type == 100 || btn->type == 1)return false;
    if (btn->type == 200 || btn->type == 2)return false;
    int m_x = btn->x;
    int m_y = btn->y;
    //使用moveAble函数的前提：第一个参数非空，是我的棋子，不是地雷or军旗
    //只需要查询btn上下左右和斜对角线的几个按钮就可以了～如果它这几个按钮都到不了，then it's stuck.
    if (m_x!=1){
        myButton* left = convert_location(m_x-1,m_y);
        if (moveAble(btn,left)){return true;}//1
        if (m_y!=1){
            myButton *left_above = convert_location(m_x-1,m_y-1);
            if (moveAble(btn,left_above)){return true;}//2
        }
        if (m_y!=12){
            myButton *left_below = convert_location(m_x-1,m_y+1);
            if (moveAble(btn,left_below)){return true;}//3
        }
    }
    if (m_x!=5){
        myButton *right = convert_location(m_x+1,m_y);
        if (moveAble(btn,right)){return true;}//4
        if (m_y!=1){
            myButton *right_above = convert_location(m_x+1,m_y-1);
            if (moveAble(btn,right_above)){return true;}//5
        }
        if (m_y!=12){
            myButton *right_below = convert_location(m_x+1,m_y+1);
            if (moveAble(btn,right_below)){return true;}//6
        }
    }
    if (m_y!=1){
        myButton *above = convert_location(m_x,m_y-1);
        if (moveAble(btn,above)){return true;}//7
    }
    if (m_y!=12){
        myButton *below = convert_location(m_x,m_y+1);
        if (moveAble(btn,below)){return true;}//8
    }
    return false;
}

bool MainWindow::dfs(int x1,int y1,int x2,int y2){//(x1,x2)(y1,y2)分别是起点，终点。这里只需要考虑：s是【工兵】，s在铁路上，t也在铁路上。
    //该函数表示工兵从铁路点s到铁路点t是否有通路。
    //visit[i]表示是否已经查询过经过i的情况。
    int s = (y1-1)*5+x1;
    int t = (y2-1)*5+x2;
    visit[s]=true;
    if ( s == t )return true;
    if (map_railway[s][t]==true)return true;
    for (int i=1;i<=60;i++){//遍历所有的点，查找是否可以s->i->t
        int x,y;
        if (i%5==0){x=5;y=i/5;}
        else{x=i%5;y=((i-x)/5)+1;}
        if (map_railway[s][i] && !visit[i] && convert_location(x,y)->type==0){
            //如果s到i有直接铁路连接，i还没有查询过,并且i是空的
            if (dfs(x,y,x2,y2)){//如果i可以到t
                return true;
            }
        }
    }//end for
    return false;
}

bool MainWindow::onRailRoad(const myButton *btn){
    int num = (btn->y -1)*5 + btn->x;
    if (num>=6 && num<=55){
        if (num%5==1 || num%5==0) return true;
    }
    if (num>=7 && num<=9)return true;
    if (num>=27 && num<=29)return true;
    if (num>=32 && num<=34)return true;
    if (num>=52 && num<=54)return true;
    return false;
}

void MainWindow::movePiece(myButton* btn1, myButton* btn2){//已经知道可以move了，现在是move的动作.btn1非空、不是地雷或者旗子
    //first,decide if you have disarmed a bomb
    if (btn2->type==2 || btn2->type==200){
        dismissBomb++;
    }
    btn1->btnSelected = 0;
    btn2->btnSelected = 0;
    //then,decide if you have won the game.(if you have won,there's no need to inform others what piece you have moved.
    if (btn2->type == 1 && dismissBomb>=3){win(false);return;}
    else if (btn2->type == 100 && dismissBomb>=3){win(false);return;}
    //send signal move to other.
    QString kw = "move/";
    //transmitClient(kw);
    //QByteArray x1,x2,y1,y2;
    kw = kw + QString::number(btn1->x) + "/";
    kw = kw + QString::number(btn2->x) + "/";
    kw = kw + QString::number(btn1->y) + "/";
    kw = kw + QString::number(btn2->y) + "/";
    socket->write(kw.toUtf8());
    socket->flush();
    qDebug()<<"I am moving ("<<btn1->x<<","<<btn1->y<<") to ("<<btn2->x<<","<<btn2->y<<")";
    //start moving
    if (btn2->type==2 || btn2->type==200){
        dismissBomb++;
    }
    if ((btn1->type==3 || btn1->type==300) && (btn2->type!=0)){//炸弹移向非空的位置
        btn1->type = 0;
        btn2->type = 0;
        btn1->myupdate();
        btn2->myupdate();
        if (themeDecided) {
            qDebug()<<"movePiece-my_turn";
            my_turn();return;
        }
        else {
            {flipOnlyRound();return;}
        }
        return;
    }
    else if (btn2->type==3 || btn2->type==300){//我的棋子移向炸弹
        if (btn1->type!=4 && btn1->type!=400){
            btn1->type = 0;
            btn2->type = 0;
            btn1->myupdate();
            btn2->myupdate();
            if (themeDecided) {
                qDebug()<<"movePiece-my_turn";my_turn();return;

            }
            else {
                {flipOnlyRound();return;}
            }
            return;
        }
        else {
            btn2->myPiece = btn1->myPiece;
            btn2->type = btn1->type;
            btn2->known = true;
            btn1->type = 0;
            btn1->myupdate();
            btn2->myupdate();
            if (themeDecided) {
                qDebug()<<"movePiece-my_turn";my_turn();return;

            }
            else {
                {flipOnlyRound();return;}
            }
            return;
        }
    }
    else if ((btn2->type == btn1->type/100)||(btn1->type == btn2->type/100)){
        if (btn1->type!=0 && btn2->type!=0){
            btn1->type = 0;
            btn2->type = 0;
            btn1->myupdate();
            btn2->myupdate();
            if (themeDecided) {
                qDebug()<<"movePiece-my_turn";my_turn();return;

            }
            else {
                {flipOnlyRound();return;}
            }
            return;
        }
        else{
            btn2->myPiece = btn1->myPiece;
            btn2->type = btn1->type;
            btn2->known = true;
            btn1->type = 0;
            btn1->myupdate();
            btn2->myupdate();
            if (themeDecided) {
                qDebug()<<"movePiece-my_turn";my_turn();return;

            }
            else {
                {flipOnlyRound();return;}
            }
            return;
        }
    }
    else {
        btn2->myPiece = btn1->myPiece;
        btn2->type = btn1->type;
        btn2->known = true;
        btn1->type = 0;
        btn1->myupdate();
        btn2->myupdate();
    }
    if (themeDecided) {
        qDebug()<<"movePiece-my_turn";my_turn();return;
    }
    else {
        {flipOnlyRound();return;}
    }
}

void MainWindow::flipCard(myButton* btn){//when this func terminate,your round terminate as well
    qDebug()<<"I flip card.function flipCard called.";
    qDebug()<<"the location of btn I flipped:("<<btn->x<<","<<btn->y<<")";
    btn->known=true;
    btn->myupdate();
}

void MainWindow::my_turn(){
    qDebug()<<"my_turn";
    round++;
    whos_turn++;
    //set the click movement
    ui->A1->numClicks_=0;
    //set the panel
    if (whos_turn%2==1){
        setButtonAvailable();
        ui->notice->setText("It's Your Turn Now!Go Ahead!");
        ui->notice->show();
        ui->sec->show();
        ui->remainTime->show();
        ui->countDown->setText("20");
        ui->countDown->show();
        if (round>=20){
            ui->admitDefeat->setEnabled(true);
            ui->admit->show();
            ui->admitDefeat->show();
        }
        else{
            ui->admit->hide();
            ui->admitDefeat->hide();
            ui->admitDefeat->setEnabled(false);
        }
    }
    else{
        setButtonUnavailable();
        ui->notice->setText("It's Your Opponent's Turn!");
        ui->notice->show();
        ui->countDown->setText("20");
        if (round>=20){
            ui->admitDefeat->setEnabled(true);
            ui->admit->show();
            ui->admitDefeat->show();
        }
        else{
            ui->admitDefeat->setEnabled(false);
            ui->admit->hide();
            ui->admitDefeat->hide();
        }
    }
    ui->roundCount->show();
    ui->timeoutCount->show();
    ui->label1->show();
    ui->label2->show();
    ui->label3->show();
    ui->timeoutCount->setText(QString::number(time_out_count));
    ui->roundCount->setText(QString::number(round));
    Timerflush->start();
    //set the countdown
}

void MainWindow::flush_countdown(){
    int now = ui->countDown->text().toInt();
    if (now>=1){
        now--;
        ui->countDown->setText(QString::number(now));
        Timerflush->start();
    }
    else{
        on_time_out();
    }
}

void MainWindow::on_time_out(){
    if (whos_turn%2==1){
        time_out_count++;
        qDebug()<<"on_time_out();now time_out_count="<<time_out_count;
        if (time_out_count>=3){
            lose(false);
            return;
        }
        if (themeDecided) {
            QString next = "nextRound/";
            //transmitClient(next);
            socket->write(next.toUtf8());
            socket->flush();
            qDebug()<<"on_time_out my_turn()";
            my_turn();
        }
        else {
            QString next = "nextFlipOnlyRound/";
            socket->write(next.toUtf8());
            socket->flush();
            flipOnlyRound();
        }
    }
}

void MainWindow::lose(bool isreceiving){
    if (!isreceiving){
        qDebug()<<"sending win signal to other";
        QString kw ="win_lose/win/";
        //QString res = "win";
        //transmitClient(kw);
        //transmitClient(res);
        socket->write(kw.toUtf8());
        socket->flush();
    }
    Timerflush->stop();
    ui->sec->hide();
    ui->countDown->hide();
    ui->remainTime->hide();
    ui->admit->hide();
    ui->admitDefeat->hide();
    ui->admitDefeat->setEnabled(false);

    m_result = new myResult(this);
    connect(m_result,SIGNAL(callEnd()),this,SLOT(endGame()));
    m_result->setRes(false);
    m_result->exec();
}

void MainWindow::win(bool isreceiving){
    if (!isreceiving){
        qDebug()<<"sending lose signal to other";
        QString kw ="win_lose/lose/";
        //transmitClient(kw);
        socket->write(kw.toUtf8());
        socket->flush();
    }
    Timerflush->stop();
    ui->sec->hide();
    ui->countDown->hide();
    ui->remainTime->hide();
    ui->admit->hide();
    ui->admitDefeat->hide();
    ui->admitDefeat->setEnabled(false);

    m_result = new myResult(this);
    connect(m_result,SIGNAL(callEnd()),this,SLOT(endGame()));
    m_result->setRes(true);
    m_result->exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createServer(){
    create_Server = new create_server(this);
    connect(create_Server,SIGNAL(rightToCreate()),this,SLOT(on_createConnect_triggered()));
    create_Server->exec();
}

void MainWindow::connectServer(){
    connect_Server = new connect_server(this);
    connect(connect_Server,SIGNAL(rightToConnect()),this,SLOT(on_actConnect_triggered()));
    connect_Server->exec();
}

void MainWindow::initIndex(){//大于100:blue 小于100:red
    index[0]=1;
    index[1]=100;
    index[2]=2;
    index[3]=2;
    index[4]=2;
    index[5]=200;
    index[6]=200;
    index[7]=200;
    index[8]=3;
    index[9]=3;
    index[10]=300;
    index[11]=300;
    index[12]=4;
    index[13]=4;
    index[14]=4;
    index[15]=400;
    index[16]=400;
    index[17]=400;
    index[18]=5;
    index[19]=5;
    index[20]=5;
    index[21]=500;
    index[22]=500;
    index[23]=500;
    index[24]=6;
    index[25]=6;
    index[26]=6;
    index[27]=600;
    index[28]=600;
    index[29]=600;
    index[30]=700;
    index[31]=700;
    index[32]=7;
    index[33]=7;
    index[34]=8;
    index[35]=8;
    index[36]=800;
    index[37]=800;
    index[38]=900;
    index[39]=900;
    index[40]=9;
    index[41]=9;
    index[42]=10;
    index[43]=10;
    index[44]=1000;
    index[45]=1000;
    index[46]=11;
    index[47]=1100;
    index[48]=1200;
    index[49]=12;
}

void MainWindow::updateButtons(){//刷新所有按钮的icon和type
    ui->A1->myupdate();
    ui->A1_2->myupdate();
    ui->A1_3->myupdate();
    ui->A1_4->myupdate();
    ui->A1_5->myupdate();
    ui->A1_6->myupdate();
    ui->A1_7->myupdate();
    ui->A1_8->myupdate();
    ui->A1_9->myupdate();
    ui->A1_10->myupdate();
    ui->A1_11->myupdate();
    ui->A1_12->myupdate();
    ui->A1_13->myupdate();
    ui->A1_14->myupdate();
    ui->A1_15->myupdate();
    ui->A1_16->myupdate();
    ui->A1_17->myupdate();
    ui->A1_18->myupdate();
    ui->A1_19->myupdate();
    ui->A1_20->myupdate();
    ui->A1_21->myupdate();
    ui->A1_22->myupdate();
    ui->A1_23->myupdate();
    ui->A1_24->myupdate();
    ui->A1_25->myupdate();
    ui->A1_26->myupdate();
    ui->A1_27->myupdate();
    ui->A1_28->myupdate();
    ui->A1_29->myupdate();
    ui->A1_30->myupdate();
    ui->A1_31->myupdate();
    ui->A1_32->myupdate();
    ui->A1_33->myupdate();
    ui->A1_34->myupdate();
    ui->A1_35->myupdate();
    ui->A1_36->myupdate();
    ui->A1_37->myupdate();
    ui->A1_38->myupdate();
    ui->A1_39->myupdate();
    ui->A1_40->myupdate();
    ui->A1_41->myupdate();
    ui->A1_42->myupdate();
    ui->A1_43->myupdate();
    ui->A1_44->myupdate();
    ui->A1_45->myupdate();
    ui->A1_46->myupdate();
    ui->A1_47->myupdate();
    ui->A1_48->myupdate();
    ui->A1_49->myupdate();
    ui->A1_50->myupdate();

    ui->B1->myupdate();
    ui->B1_2->myupdate();
    ui->B1_3->myupdate();
    ui->B1_4->myupdate();
    ui->B1_5->myupdate();
    ui->B1_6->myupdate();
    ui->B1_7->myupdate();
    ui->B1_8->myupdate();
    ui->B1_9->myupdate();
    ui->B1_10->myupdate();
}

myButton* MainWindow::convert_location(int x,int y){
    int tmp = x*100 + y;
    if (tmp==101)return ui->A1;
    if (tmp==201)return ui->A1_2;
    if (tmp==301)return ui->A1_3;
    if (tmp==401)return ui->A1_4;
    if (tmp==501)return ui->A1_5;
    if (tmp==102)return ui->A1_6;
    if (tmp==202)return ui->A1_7;
    if (tmp==302)return ui->A1_8;
    if (tmp==402)return ui->A1_9;
    if (tmp==502)return ui->A1_10;
    if (tmp==103)return ui->A1_11;
    if (tmp==303)return ui->A1_12;
    if (tmp==503)return ui->A1_13;
    if (tmp==104)return ui->A1_14;
    if (tmp==204)return ui->A1_15;
    if (tmp==404)return ui->A1_16;
    if (tmp==504)return ui->A1_17;
    if (tmp==105)return ui->A1_18;
    if (tmp==305)return ui->A1_19;
    if (tmp==505)return ui->A1_20;
    if (tmp==106)return ui->A1_21;
    if (tmp==206)return ui->A1_22;
    if (tmp==306)return ui->A1_23;
    if (tmp==406)return ui->A1_24;
    if (tmp==506)return ui->A1_25;
    if (tmp==107)return ui->A1_26;
    if (tmp==207)return ui->A1_27;
    if (tmp==307)return ui->A1_28;
    if (tmp==407)return ui->A1_29;
    if (tmp==507)return ui->A1_30;
    if (tmp==108)return ui->A1_31;
    if (tmp==308)return ui->A1_32;
    if (tmp==508)return ui->A1_33;
    if (tmp==109)return ui->A1_34;
    if (tmp==209)return ui->A1_35;
    if (tmp==409)return ui->A1_36;
    if (tmp==509)return ui->A1_37;
    if (tmp==110)return ui->A1_38;
    if (tmp==310)return ui->A1_39;
    if (tmp==510)return ui->A1_40;
    if (tmp==111)return ui->A1_41;
    if (tmp==211)return ui->A1_42;
    if (tmp==311)return ui->A1_43;
    if (tmp==411)return ui->A1_44;
    if (tmp==511)return ui->A1_45;
    if (tmp==112)return ui->A1_46;
    if (tmp==212)return ui->A1_47;
    if (tmp==312)return ui->A1_48;
    if (tmp==412)return ui->A1_49;
    if (tmp==512)return ui->A1_50;
    if (tmp==203)return ui->B1;
    if (tmp==403)return ui->B1_2;
    if (tmp==304)return ui->B1_3;
    if (tmp==205)return ui->B1_4;
    if (tmp==405)return ui->B1_5;
    if (tmp==208)return ui->B1_6;
    if (tmp==408)return ui->B1_7;
    if (tmp==309)return ui->B1_8;
    if (tmp==210)return ui->B1_9;
    if (tmp==410)return ui->B1_10;
    return NULL;
}

void MainWindow::assignButtonType(){
    ui->A1->type = result[0];
    ui->A1_2->type = result[1];
    ui->A1_3->type = result[2];
    ui->A1_4->type = result[3];
    ui->A1_5->type = result[4];
    ui->A1_6->type = result[5];
    ui->A1_7->type = result[6];
    ui->A1_8->type = result[7];
    ui->A1_9->type = result[8];
    ui->A1_10->type = result[9];
    ui->A1_11->type = result[10];
    ui->A1_12->type = result[11];
    ui->A1_13->type = result[12];
    ui->A1_14->type = result[13];
    ui->A1_15->type = result[14];
    ui->A1_16->type = result[15];
    ui->A1_17->type = result[16];
    ui->A1_18->type = result[17];
    ui->A1_19->type = result[18];
    ui->A1_20->type = result[19];
    ui->A1_21->type = result[20];
    ui->A1_22->type = result[21];
    ui->A1_23->type = result[22];
    ui->A1_24->type = result[23];
    ui->A1_25->type = result[24];
    ui->A1_26->type = result[25];
    ui->A1_27->type = result[26];
    ui->A1_28->type = result[27];
    ui->A1_29->type = result[28];
    ui->A1_30->type = result[29];
    ui->A1_31->type = result[30];
    ui->A1_32->type = result[31];
    ui->A1_33->type = result[32];
    ui->A1_34->type = result[33];
    ui->A1_35->type = result[34];
    ui->A1_36->type = result[35];
    ui->A1_37->type = result[36];
    ui->A1_38->type = result[37];
    ui->A1_39->type = result[38];
    ui->A1_40->type = result[39];
    ui->A1_41->type = result[40];
    ui->A1_42->type = result[41];
    ui->A1_43->type = result[42];
    ui->A1_44->type = result[43];
    ui->A1_45->type = result[44];
    ui->A1_46->type = result[45];
    ui->A1_47->type = result[46];
    ui->A1_48->type = result[47];
    ui->A1_49->type = result[48];
    ui->A1_50->type = result[49];

}

void MainWindow::initButton(){
    ui->A1->x=1;
    ui->A1_2->x=2;
    ui->A1_3->x=3;
    ui->A1_4->x=4;
    ui->A1_5->x=5;
    ui->A1_6->x=1;
    ui->A1_7->x=2;
    ui->A1_8->x=3;
    ui->A1_9->x=4;
    ui->A1_10->x=5;
    ui->A1_11->x=1;
    ui->A1_12->x=3;
    ui->A1_13->x=5;
    ui->A1_14->x=1;
    ui->A1_15->x=2;
    ui->A1_16->x=4;
    ui->A1_17->x=5;
    ui->A1_18->x=1;
    ui->A1_19->x=3;
    ui->A1_20->x=5;
    ui->A1_21->x=1;
    ui->A1_22->x=2;
    ui->A1_23->x=3;
    ui->A1_24->x=4;
    ui->A1_25->x=5;
    ui->A1_26->x=1;
    ui->A1_27->x=2;
    ui->A1_28->x=3;
    ui->A1_29->x=4;
    ui->A1_30->x=5;
    ui->A1_31->x=1;
    ui->A1_32->x=3;
    ui->A1_33->x=5;
    ui->A1_34->x=1;
    ui->A1_35->x=2;
    ui->A1_36->x=4;
    ui->A1_37->x=5;
    ui->A1_38->x=1;
    ui->A1_39->x=3;
    ui->A1_40->x=5;
    ui->A1_41->x=1;
    ui->A1_42->x=2;
    ui->A1_43->x=3;
    ui->A1_44->x=4;
    ui->A1_45->x=5;
    ui->A1_46->x=1;
    ui->A1_47->x=2;
    ui->A1_48->x=3;
    ui->A1_49->x=4;
    ui->A1_50->x=5;
    ui->B1->x=2;
    ui->B1_2->x=4;
    ui->B1_3->x=3;
    ui->B1_4->x=2;
    ui->B1_5->x=4;
    ui->B1_6->x=2;
    ui->B1_7->x=4;
    ui->B1_8->x=3;
    ui->B1_9->x=2;
    ui->B1_10->x=4;

    //修改y
    ui->A1->y=1;
    ui->A1_2->y=1;
    ui->A1_3->y=1;
    ui->A1_4->y=1;
    ui->A1_5->y=1;
    ui->A1_6->y=2;
    ui->A1_7->y=2;
    ui->A1_8->y=2;
    ui->A1_9->y=2;
    ui->A1_10->y=2;
    ui->A1_11->y=3;
    ui->A1_12->y=3;
    ui->A1_13->y=3;
    ui->A1_14->y=4;
    ui->A1_15->y=4;
    ui->A1_16->y=4;
    ui->A1_17->y=4;
    ui->A1_18->y=5;
    ui->A1_19->y=5;
    ui->A1_20->y=5;
    ui->A1_21->y=6;
    ui->A1_22->y=6;
    ui->A1_23->y=6;
    ui->A1_24->y=6;
    ui->A1_25->y=6;
    ui->A1_26->y=7;
    ui->A1_27->y=7;
    ui->A1_28->y=7;
    ui->A1_29->y=7;
    ui->A1_30->y=7;
    ui->A1_31->y=8;
    ui->A1_32->y=8;
    ui->A1_33->y=8;
    ui->A1_34->y=9;
    ui->A1_35->y=9;
    ui->A1_36->y=9;
    ui->A1_37->y=9;
    ui->A1_38->y=10;
    ui->A1_39->y=10;
    ui->A1_40->y=10;
    ui->A1_41->y=11;
    ui->A1_42->y=11;
    ui->A1_43->y=11;
    ui->A1_44->y=11;
    ui->A1_45->y=11;
    ui->A1_46->y=12;
    ui->A1_47->y=12;
    ui->A1_48->y=12;
    ui->A1_49->y=12;
    ui->A1_50->y=12;
    ui->B1->y=3;
    ui->B1_2->y=3;
    ui->B1_3->y=4;
    ui->B1_4->y=5;
    ui->B1_5->y=5;
    ui->B1_6->y=8;
    ui->B1_7->y=8;
    ui->B1_8->y=9;
    ui->B1_9->y=10;
    ui->B1_10->y=10;

    //修改isStation
    ui->B1->isStation=true;
    ui->B1_2->isStation=true;
    ui->B1_3->isStation=true;
    ui->B1_4->isStation=true;
    ui->B1_5->isStation=true;
    ui->B1_6->isStation=true;
    ui->B1_7->isStation=true;
    ui->B1_8->isStation=true;
    ui->B1_9->isStation=true;
    ui->B1_10->isStation=true;

    //修改known
    ui->B1->known=true;
    ui->B1_2->known=true;
    ui->B1_3->known=true;
    ui->B1_4->known=true;
    ui->B1_5->known=true;
    ui->B1_6->known=true;
    ui->B1_7->known=true;
    ui->B1_8->known=true;
    ui->B1_9->known=true;
    ui->B1_10->known=true;

}

void MainWindow::analyseType(bool IsRed){
    ui->A1->analyseType(IsRed);
    ui->A1_2->analyseType(IsRed);
    ui->A1_3->analyseType(IsRed);
    ui->A1_4->analyseType(IsRed);
    ui->A1_5->analyseType(IsRed);
    ui->A1_6->analyseType(IsRed);
    ui->A1_7->analyseType(IsRed);
    ui->A1_8->analyseType(IsRed);
    ui->A1_9->analyseType(IsRed);
    ui->A1_10->analyseType(IsRed);
    ui->A1_11->analyseType(IsRed);
    ui->A1_12->analyseType(IsRed);
    ui->A1_13->analyseType(IsRed);
    ui->A1_14->analyseType(IsRed);
    ui->A1_15->analyseType(IsRed);
    ui->A1_16->analyseType(IsRed);
    ui->A1_17->analyseType(IsRed);
    ui->A1_18->analyseType(IsRed);
    ui->A1_19->analyseType(IsRed);
    ui->A1_20->analyseType(IsRed);
    ui->A1_21->analyseType(IsRed);
    ui->A1_22->analyseType(IsRed);
    ui->A1_23->analyseType(IsRed);
    ui->A1_24->analyseType(IsRed);
    ui->A1_25->analyseType(IsRed);
    ui->A1_26->analyseType(IsRed);
    ui->A1_27->analyseType(IsRed);
    ui->A1_28->analyseType(IsRed);
    ui->A1_29->analyseType(IsRed);
    ui->A1_30->analyseType(IsRed);
    ui->A1_31->analyseType(IsRed);
    ui->A1_32->analyseType(IsRed);
    ui->A1_33->analyseType(IsRed);
    ui->A1_34->analyseType(IsRed);
    ui->A1_35->analyseType(IsRed);
    ui->A1_36->analyseType(IsRed);
    ui->A1_37->analyseType(IsRed);
    ui->A1_38->analyseType(IsRed);
    ui->A1_39->analyseType(IsRed);
    ui->A1_40->analyseType(IsRed);
    ui->A1_41->analyseType(IsRed);
    ui->A1_42->analyseType(IsRed);
    ui->A1_43->analyseType(IsRed);
    ui->A1_44->analyseType(IsRed);
    ui->A1_45->analyseType(IsRed);
    ui->A1_46->analyseType(IsRed);
    ui->A1_47->analyseType(IsRed);
    ui->A1_48->analyseType(IsRed);
    ui->A1_49->analyseType(IsRed);
    ui->A1_50->analyseType(IsRed);
    ui->B1->analyseType(IsRed);
    ui->B1_2->analyseType(IsRed);
    ui->B1_3->analyseType(IsRed);
    ui->B1_4->analyseType(IsRed);
    ui->B1_5->analyseType(IsRed);
    ui->B1_6->analyseType(IsRed);
    ui->B1_7->analyseType(IsRed);
    ui->B1_8->analyseType(IsRed);
    ui->B1_9->analyseType(IsRed);
    ui->B1_10->analyseType(IsRed);
}

void MainWindow::setFlipOnly(){
    ui->A1->disconnect(this);
    ui->A1_2->disconnect(this);
    ui->A1_3->disconnect(this);
    ui->A1_4->disconnect(this);
    ui->A1_5->disconnect(this);
    ui->A1_6->disconnect(this);
    ui->A1_7->disconnect(this);
    ui->A1_8->disconnect(this);
    ui->A1_9->disconnect(this);
    ui->A1_10->disconnect(this);
    ui->A1_11->disconnect(this);
    ui->A1_12->disconnect(this);
    ui->A1_13->disconnect(this);
    ui->A1_14->disconnect(this);
    ui->A1_15->disconnect(this);
    ui->A1_16->disconnect(this);
    ui->A1_17->disconnect(this);
    ui->A1_18->disconnect(this);
    ui->A1_19->disconnect(this);
    ui->A1_20->disconnect(this);
    ui->A1_21->disconnect(this);
    ui->A1_22->disconnect(this);
    ui->A1_23->disconnect(this);
    ui->A1_24->disconnect(this);
    ui->A1_25->disconnect(this);
    ui->A1_26->disconnect(this);
    ui->A1_27->disconnect(this);
    ui->A1_28->disconnect(this);
    ui->A1_29->disconnect(this);
    ui->A1_30->disconnect(this);
    ui->A1_31->disconnect(this);
    ui->A1_32->disconnect(this);
    ui->A1_33->disconnect(this);
    ui->A1_34->disconnect(this);
    ui->A1_35->disconnect(this);
    ui->A1_36->disconnect(this);
    ui->A1_37->disconnect(this);
    ui->A1_38->disconnect(this);
    ui->A1_39->disconnect(this);
    ui->A1_40->disconnect(this);
    ui->A1_41->disconnect(this);
    ui->A1_42->disconnect(this);
    ui->A1_43->disconnect(this);
    ui->A1_44->disconnect(this);
    ui->A1_45->disconnect(this);
    ui->A1_46->disconnect(this);
    ui->A1_47->disconnect(this);
    ui->A1_48->disconnect(this);
    ui->A1_49->disconnect(this);
    ui->A1_50->disconnect(this);
    ui->B1->disconnect(this);
    ui->B1_2->disconnect(this);
    ui->B1_3->disconnect(this);
    ui->B1_4->disconnect(this);
    ui->B1_5->disconnect(this);
    ui->B1_6->disconnect(this);
    ui->B1_7->disconnect(this);
    ui->B1_8->disconnect(this);
    ui->B1_9->disconnect(this);
    ui->B1_10->disconnect(this);

    connect(ui->A1,&myButton::clicked,this,[&](){this->flipOnly(ui->A1);});
    connect(ui->A1_2,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_2);});
    connect(ui->A1_3,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_3);});
    connect(ui->A1_4,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_4);});
    connect(ui->A1_5,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_5);});
        connect(ui->A1_6,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_6);});
        connect(ui->A1_7,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_7);});
        connect(ui->A1_8,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_8);});
        connect(ui->A1_9,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_9);});
        connect(ui->A1_10,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_10);});
        connect(ui->A1_11,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_11);});
        connect(ui->A1_12,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_12);});
        connect(ui->A1_13,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_13);});
        connect(ui->A1_14,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_14);});
        connect(ui->A1_15,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_15);});
        connect(ui->A1_16,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_16);});
        connect(ui->A1_17,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_17);});
        connect(ui->A1_18,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_18);});
        connect(ui->A1_19,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_19);});
        connect(ui->A1_20,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_20);});
        connect(ui->A1_21,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_21);});
        connect(ui->A1_22,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_22);});
        connect(ui->A1_23,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_23);});
        connect(ui->A1_24,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_24);});
        connect(ui->A1_25,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_25);});
        connect(ui->A1_26,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_26);});
        connect(ui->A1_27,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_27);});
        connect(ui->A1_28,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_28);});
        connect(ui->A1_29,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_29);});
        connect(ui->A1_30,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_30);});
        connect(ui->A1_31,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_31);});
        connect(ui->A1_32,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_32);});
        connect(ui->A1_33,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_33);});
        connect(ui->A1_34,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_34);});
        connect(ui->A1_35,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_35);});
        connect(ui->A1_36,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_36);});
        connect(ui->A1_37,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_37);});
        connect(ui->A1_38,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_38);});
        connect(ui->A1_39,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_39);});
        connect(ui->A1_40,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_40);});
        connect(ui->A1_41,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_41);});
        connect(ui->A1_42,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_42);});
        connect(ui->A1_43,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_43);});
        connect(ui->A1_44,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_44);});
        connect(ui->A1_45,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_45);});
        connect(ui->A1_46,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_46);});
        connect(ui->A1_47,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_47);});
        connect(ui->A1_48,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_48);});
        connect(ui->A1_49,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_49);});
        connect(ui->A1_50,&myButton::clicked,this,[&](){this->flipOnly(ui->A1_50);});
        connect(ui->B1,&myButton::clicked,this,[&](){this->flipOnly(ui->B1);});
        connect(ui->B1_2,&myButton::clicked,this,[&](){this->flipOnly(ui->B1_2);});
        connect(ui->B1_3,&myButton::clicked,this,[&](){this->flipOnly(ui->B1_3);});
        connect(ui->B1_4,&myButton::clicked,this,[&](){this->flipOnly(ui->B1_4);});
        connect(ui->B1_5,&myButton::clicked,this,[&](){this->flipOnly(ui->B1_5);});
        connect(ui->B1_6,&myButton::clicked,this,[&](){this->flipOnly(ui->B1_6);});
        connect(ui->B1_7,&myButton::clicked,this,[&](){this->flipOnly(ui->B1_7);});
        connect(ui->B1_8,&myButton::clicked,this,[&](){this->flipOnly(ui->B1_8);});
        connect(ui->B1_9,&myButton::clicked,this,[&](){this->flipOnly(ui->B1_9);});
        connect(ui->B1_10,&myButton::clicked,this,[&](){this->flipOnly(ui->B1_10);});
}

void MainWindow::setButtonUnavailable(){
    ui->A1->setEnabled(false);
    ui->A1_2->setEnabled(false);
    ui->A1_3->setEnabled(false);
    ui->A1_4->setEnabled(false);
    ui->A1_5->setEnabled(false);
    ui->A1_6->setEnabled(false);
    ui->A1_7->setEnabled(false);
    ui->A1_8->setEnabled(false);
    ui->A1_9->setEnabled(false);
    ui->A1_10->setEnabled(false);
    ui->A1_11->setEnabled(false);
    ui->A1_12->setEnabled(false);
    ui->A1_13->setEnabled(false);
    ui->A1_14->setEnabled(false);
    ui->A1_15->setEnabled(false);
    ui->A1_16->setEnabled(false);
    ui->A1_17->setEnabled(false);
    ui->A1_18->setEnabled(false);
    ui->A1_19->setEnabled(false);
    ui->A1_20->setEnabled(false);
    ui->A1_21->setEnabled(false);
    ui->A1_22->setEnabled(false);
    ui->A1_23->setEnabled(false);
    ui->A1_24->setEnabled(false);
    ui->A1_25->setEnabled(false);
    ui->A1_26->setEnabled(false);
    ui->A1_27->setEnabled(false);
    ui->A1_28->setEnabled(false);
    ui->A1_29->setEnabled(false);
    ui->A1_30->setEnabled(false);
    ui->A1_31->setEnabled(false);
    ui->A1_32->setEnabled(false);
    ui->A1_33->setEnabled(false);
    ui->A1_34->setEnabled(false);
    ui->A1_35->setEnabled(false);
    ui->A1_36->setEnabled(false);
    ui->A1_37->setEnabled(false);
    ui->A1_38->setEnabled(false);
    ui->A1_39->setEnabled(false);
    ui->A1_40->setEnabled(false);
    ui->A1_41->setEnabled(false);
    ui->A1_42->setEnabled(false);
    ui->A1_43->setEnabled(false);
    ui->A1_44->setEnabled(false);
    ui->A1_45->setEnabled(false);
    ui->A1_46->setEnabled(false);
    ui->A1_47->setEnabled(false);
    ui->A1_48->setEnabled(false);
    ui->A1_49->setEnabled(false);
    ui->A1_50->setEnabled(false);
    ui->B1->setEnabled(false);
    ui->B1_2->setEnabled(false);
    ui->B1_3->setEnabled(false);
    ui->B1_4->setEnabled(false);
    ui->B1_5->setEnabled(false);
    ui->B1_6->setEnabled(false);
    ui->B1_7->setEnabled(false);
    ui->B1_8->setEnabled(false);
    ui->B1_9->setEnabled(false);
    ui->B1_10->setEnabled(false);
}

void MainWindow::setButtonAvailable(){
    ui->A1->setEnabled(true);
    ui->A1_2->setEnabled(true);
    ui->A1_3->setEnabled(true);
    ui->A1_4->setEnabled(true);
    ui->A1_5->setEnabled(true);
    ui->A1_6->setEnabled(true);
    ui->A1_7->setEnabled(true);
    ui->A1_8->setEnabled(true);
    ui->A1_9->setEnabled(true);
    ui->A1_10->setEnabled(true);
    ui->A1_11->setEnabled(true);
    ui->A1_12->setEnabled(true);
    ui->A1_13->setEnabled(true);
    ui->A1_14->setEnabled(true);
    ui->A1_15->setEnabled(true);
    ui->A1_16->setEnabled(true);
    ui->A1_17->setEnabled(true);
    ui->A1_18->setEnabled(true);
    ui->A1_19->setEnabled(true);
    ui->A1_20->setEnabled(true);
    ui->A1_21->setEnabled(true);
    ui->A1_22->setEnabled(true);
    ui->A1_23->setEnabled(true);
    ui->A1_24->setEnabled(true);
    ui->A1_25->setEnabled(true);
    ui->A1_26->setEnabled(true);
    ui->A1_27->setEnabled(true);
    ui->A1_28->setEnabled(true);
    ui->A1_29->setEnabled(true);
    ui->A1_30->setEnabled(true);
    ui->A1_31->setEnabled(true);
    ui->A1_32->setEnabled(true);
    ui->A1_33->setEnabled(true);
    ui->A1_34->setEnabled(true);
    ui->A1_35->setEnabled(true);
    ui->A1_36->setEnabled(true);
    ui->A1_37->setEnabled(true);
    ui->A1_38->setEnabled(true);
    ui->A1_39->setEnabled(true);
    ui->A1_40->setEnabled(true);
    ui->A1_41->setEnabled(true);
    ui->A1_42->setEnabled(true);
    ui->A1_43->setEnabled(true);
    ui->A1_44->setEnabled(true);
    ui->A1_45->setEnabled(true);
    ui->A1_46->setEnabled(true);
    ui->A1_47->setEnabled(true);
    ui->A1_48->setEnabled(true);
    ui->A1_49->setEnabled(true);
    ui->A1_50->setEnabled(true);
    ui->B1->setEnabled(true);
    ui->B1_2->setEnabled(true);
    ui->B1_3->setEnabled(true);
    ui->B1_4->setEnabled(true);
    ui->B1_5->setEnabled(true);
    ui->B1_6->setEnabled(true);
    ui->B1_7->setEnabled(true);
    ui->B1_8->setEnabled(true);
    ui->B1_9->setEnabled(true);
    ui->B1_10->setEnabled(true);
}
