#include "mybutton.h"


myButton::myButton(QWidget * parent):QPushButton(parent),btnSelected(-1),known(false),type(0),x(0),y(0),isStation(false),myPiece(false)
{
    this->setStyleSheet("QPushButton{icon:url(:/png/31.png);background:transparent;}");
    this->setIconSize(QSize(70,30));
}

int myButton::numClicks_=0;


void myButton::wrongMove(){
    timer=new QTimer(this);
    this->setStyleSheet("QPushButton{icon:url(:/wrong/warn.jpg);background:transparent;}");
    timer->setInterval(500);
    timer->start();
    connect(timer,SIGNAL(timeout()),this,SLOT(flushButton()));
    numClicks_=0;
}

void myButton::flushButton(){
    this->myupdate();
}

void myButton::analyseType(bool isRed){
    if (type!=0){
        if (type>=100 && isRed){//is blue
            myPiece = false;
        }
        else if (type>=100 && !isRed){
            myPiece = true;
        }
        else if (type<100 && isRed){
            myPiece = true;
        }
        else if (type<100 && !isRed){
            myPiece = false;
        }
    }
}


void myButton::myupdate(){
    this->setIconSize(QSize(70,30));
    if (btnSelected == 0 || btnSelected == -1){
    if (known == false){//如果未知
        this->setStyleSheet("QPushButton{icon:url(:/png/31.png);background:transparent;}");
    }
    else if (type == 0){//如果什么都没有
        this->setStyleSheet("QPushButton{border:none;background:transparent;}");
    }
    else{
        if (type == 1){
            this->setStyleSheet("QPushButton{icon:url(:/png/5.png);background:transparent;}");
        }
        else if (type==2){
            this->setStyleSheet("QPushButton{icon:url(:/png/1.png);background:transparent;}");
        }
        else if (type==3){
            this->setStyleSheet("QPushButton{icon:url(:/png/28.png);background:transparent;}");
        }
        else if (type==4){
            this->setStyleSheet("QPushButton{icon:url(:/png/3.png);background:transparent;}");
        }
        else if (type==5){
            this->setStyleSheet("QPushButton{icon:url(:/png/15.png);background:transparent;}");
        }
        else if (type==6){
            this->setStyleSheet("QPushButton{icon:url(:/png/11.png);background:transparent;}");
        }
        else if (type==7){
            this->setStyleSheet("QPushButton{icon:url(:/png/26.png);background:transparent;}");
        }
        else if (type==8){
            this->setStyleSheet("QPushButton{icon:url(:/png/24.png);background:transparent;}");
        }
        else if (type==9){
            this->setStyleSheet("QPushButton{icon:url(:/png/13.png);background:transparent;}");
        }
        else if (type==10){
            this->setStyleSheet("QPushButton{icon:url(:/png/20.png);background:transparent;}");
        }
        else if (type==11){
            this->setStyleSheet("QPushButton{icon:url(:/png/7.png);background:transparent;}");
        }
        else if (type==12){
            this->setStyleSheet("QPushButton{icon:url(:/png/22.png);background:transparent;}");
        }
        else if (type==100){
            this->setStyleSheet("QPushButton{icon:url(:/png/6.png);background:transparent;}");
        }
        else if (type==200){
            this->setStyleSheet("QPushButton{icon:url(:/png/2.png);background:transparent;}");
        }
        else if (type==300){
            this->setStyleSheet("QPushButton{icon:url(:/png/29.png);background:transparent;}");
        }
        else if (type==400){
            this->setStyleSheet("QPushButton{icon:url(:/png/4.png);background:transparent;}");
        }
        else if (type==500){
            this->setStyleSheet("QPushButton{icon:url(:/png/16.png);background:transparent;}");
        }
        else if (type==600){
            this->setStyleSheet("QPushButton{icon:url(:/png/12.png);background:transparent;}");
        }
        else if (type==700){
            this->setStyleSheet("QPushButton{icon:url(:/png/27.png);background:transparent;}");
        }
        else if (type==800){
            this->setStyleSheet("QPushButton{icon:url(:/png/25.png);background:transparent;}");
        }
        else if (type==900){
            this->setStyleSheet("QPushButton{icon:url(:/png/14.png);background:transparent;}");
        }
        else if (type==1000){
            this->setStyleSheet("QPushButton{icon:url(:/png/21.png);background:transparent;}");
        }
        else if (type==1100){
            this->setStyleSheet("QPushButton{icon:url(:/png/8.png);background:transparent;}");
        }
        else if (type==1200){
            this->setStyleSheet("QPushButton{icon:url(:/png/23.png);background:transparent;}");
        }
    }
    }
    else{
        qDebug()<<"The "<<type<<" type of chess is selected";
        if (known == false){//如果未知
            this->setStyleSheet("QPushButton{icon:url(:/png/31.png);background:transparent;}");
        }
        else if (type == 0){//如果什么都没有
            this->setStyleSheet("QPushButton{border:none;background:transparent;}");
        }
        else{
            if (type == 1){
                this->setStyleSheet("QPushButton{icon:url(:/new/prefix1/5.jpg);background:transparent;}");
            }
            else if (type==2){
                this->setStyleSheet("QPushButton{icon:url(:/new/prefix1/1.jpg);background:transparent;}");
            }
            else if (type==3){
                this->setStyleSheet("QPushButton{icon:url(:/new/prefix1/28.jpg);background:transparent;}");
            }
            else if (type==4){
                this->setStyleSheet("QPushButton{icon:url(:/new/prefix1/3.jpg);background:transparent;}");
            }
            else if (type==5){
                this->setStyleSheet("QPushButton{icon:url(:/new/prefix1/15.jpg);background:transparent;}");
            }
            else if (type==6){
                this->setStyleSheet("QPushButton{icon:url(:/new/prefix1/11.jpg);background:transparent;}");
            }
            else if (type==7){
                this->setStyleSheet("QPushButton{icon:url(:/new/prefix1/26.jpg);background:transparent;}");
            }
            else if (type==8){
                this->setStyleSheet("QPushButton{icon:url(:/new/prefix1/24.jpg);background:transparent;}");
            }
            else if (type==9){
                this->setStyleSheet("QPushButton{icon:url(:/new/prefix1/13.jpg);background:transparent;}");
            }
            else if (type==10){
                this->setStyleSheet("QPushButton{icon:url(:/new/prefix1/20.jpg);background:transparent;}");
            }
            else if (type==11){
                this->setStyleSheet("QPushButton{icon:url(:/new/prefix1/7.jpg);background:transparent;}");
            }
            else if (type==12){
                this->setStyleSheet("QPushButton{icon:url(:/new/prefix1/22.jpg);background:transparent;}");
            }
            else if (type==100){
                this->setStyleSheet("QPushButton{icon:url(:/new/prefix1/6.jpg);background:transparent;}");
            }
            else if (type==200){
                this->setStyleSheet("QPushButton{icon:url(:/new/prefix1/2.jpg);background:transparent;}");
            }
            else if (type==300){
                this->setStyleSheet("QPushButton{icon:url(:/new/prefix1/29.jpg);background:transparent;}");
            }
            else if (type==400){
                this->setStyleSheet("QPushButton{icon:url(:/new/prefix1/4.jpg);background:transparent;}");
            }
            else if (type==500){
                this->setStyleSheet("QPushButton{icon:url(:/new/prefix1/16.jpg);background:transparent;}");
            }
            else if (type==600){
                this->setStyleSheet("QPushButton{icon:url(:/new/prefix1/12.jpg);background:transparent;}");
            }
            else if (type==700){
                this->setStyleSheet("QPushButton{icon:url(:/new/prefix1/27.jpg);background:transparent;}");
            }
            else if (type==800){
                this->setStyleSheet("QPushButton{icon:url(:/new/prefix1/25.jpg);background:transparent;}");
            }
            else if (type==900){
                this->setStyleSheet("QPushButton{icon:url(:/new/prefix1/14.jpg);background:transparent;}");
            }
            else if (type==1000){
                this->setStyleSheet("QPushButton{icon:url(:/new/prefix1/21.jpg);background:transparent;}");
            }
            else if (type==1100){
                this->setStyleSheet("QPushButton{icon:url(:/new/prefix1/8.jpg);background:transparent;}");
            }
            else if (type==1200){
                this->setStyleSheet("QPushButton{icon:url(:/new/prefix1/23.jpg);background:transparent;}");
            }
        }
    }
}

