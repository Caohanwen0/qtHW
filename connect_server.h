#ifndef CONNECT_SERVER_H
#define CONNECT_SERVER_H

#include <QtWidgets>
#include <QLineEdit>
#include <QDialog>
#include <QPushButton>
#include <QObject>
#include <QtNetwork>

namespace Ui {
class connect_server;
}

class connect_server : public QDialog
{
    Q_OBJECT

public:
    Ui::connect_server *ui;
    explicit connect_server(QWidget *parent = nullptr);
    QString getInput();
    bool acceptAble();
    void showMsg(QString msg);
    ~connect_server();
public slots:
    void sendRightConnect();
    void clearInput();
signals:
    void rightToConnect();
private:
    QRegularExpressionValidator *validator;
    QRegularExpression* QRegExp;
};

#endif // CONNECT_SERVER_H
