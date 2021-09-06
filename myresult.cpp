#include "myresult.h"
#include "ui_myresult.h"

myResult::myResult(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myResult)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(onClickOK()));
}

void myResult::setRes(bool win){
    if (win==false){
        ui->resLabel->setText("You Lose");
    }
}

void myResult::setNot20RoundYet(){
    ui->resLabel->setText("Not 20 round yet.");
}

void myResult::onClickOK(){
    close();
    emit callEnd();
}

myResult::~myResult()
{
    delete ui;
}
