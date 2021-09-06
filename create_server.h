#ifndef CREATE_SERVER_H
#define CREATE_SERVER_H

#include <QDialog>
#include <QtNetwork>

namespace Ui {
class create_server;
}

class create_server : public QDialog
{
    Q_OBJECT

public:
    Ui::create_server *ui;
    explicit create_server(QWidget *parent = nullptr);
    QString getLocalIP();
    QPushButton* createBtn();
    void setStatus(QString str);
    ~create_server();

private:
    QString localIP;
signals:
    void rightToCreate();
public slots:
    void sendRightCreate();


};

#endif // CREATE_SERVER_H
