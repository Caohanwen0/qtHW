#include "create_server.h"
#include "ui_create_server.h"

create_server::create_server(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::create_server)
{
    ui->setupUi(this);
    //ui->createBtn->setShortcut(QKeySequence::StandardKey;enterEvent();));
    QString localHostName = QHostInfo::localHostName();
    //qDebug() <<"localHostName: "<<localHostName;
    QHostInfo info = QHostInfo::fromName(localHostName);
    foreach(QHostAddress address,info.addresses())
    {
         if(address.protocol() == QAbstractSocket::IPv4Protocol){
             localIP = address.toString();
             ui->IP->setText(address.toString());
         }
    }
}

void create_server::setStatus(QString str){
    ui->status->setText(str);
    ui->status->show();
}

QString create_server::getLocalIP(){
    return localIP;
}

QPushButton* create_server::createBtn(){
    return ui->createBtn;
}

void create_server::sendRightCreate(){
    emit rightToCreate();
}


create_server::~create_server()
{
    delete ui;
}
