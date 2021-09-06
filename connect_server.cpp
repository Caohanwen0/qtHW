#include "connect_server.h"
#include "ui_connect_server.h"


connect_server::connect_server(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::connect_server)
{
    ui->setupUi(this);
    QRegExp = new QRegularExpression("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
    validator = new QRegularExpressionValidator(*QRegExp,ui->ipInput);
    ui->ipInput->setValidator(validator);
    ui->ipInput->setInputMask("000.000.000.000");
    connect(ui->num0,&QPushButton::clicked,ui->ipInput,[&](){ui->ipInput->insert("0");});
    connect(ui->num1,&QPushButton::clicked,ui->ipInput,[&](){ui->ipInput->insert("1");});
    connect(ui->num2,&QPushButton::clicked,ui->ipInput,[&](){ui->ipInput->insert("2");});
    connect(ui->num3,&QPushButton::clicked,ui->ipInput,[&](){ui->ipInput->insert("3");});
    connect(ui->num4,&QPushButton::clicked,ui->ipInput,[&](){ui->ipInput->insert("4");});
    connect(ui->num5,&QPushButton::clicked,ui->ipInput,[&](){ui->ipInput->insert("5");});
    connect(ui->num6,&QPushButton::clicked,ui->ipInput,[&](){ui->ipInput->insert("6");});
    connect(ui->num7,&QPushButton::clicked,ui->ipInput,[&](){ui->ipInput->insert("7");});
    connect(ui->num8,&QPushButton::clicked,ui->ipInput,[&](){ui->ipInput->insert("8");});
    connect(ui->num9,&QPushButton::clicked,ui->ipInput,[&](){ui->ipInput->insert("9");});
    connect(ui->numBlank,&QPushButton::clicked,ui->ipInput,[&](){ui->ipInput->insert(" ");});
    connect(ui->numDelete,&QPushButton::clicked,ui->ipInput,[&](){ui->ipInput->backspace();});
    //ui->connectBtn->setShortcut(QKeySequence(QLatin1String("Enter")));
}

bool connect_server::acceptAble(){
    QString IP = ui->ipInput->text();
    int pos = 0;
    if (validator->validate(IP,pos)==QRegularExpressionValidator::Acceptable)return true;
    else return false;
}

void connect_server::clearInput(){
    ui->ipInput->clear();
}

void connect_server::showMsg(QString msg){
    ui->wrongMsg->setText(msg);
}

QString connect_server::getInput(){
    QString IP = ui->ipInput->text();
    qDebug()<<"input IP is"<<IP;
    return IP;
}

void connect_server::sendRightConnect(){
    emit rightToConnect();
}

connect_server::~connect_server()
{
    delete ui;
}

