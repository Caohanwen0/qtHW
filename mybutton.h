#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>
#include <cstring>
#include <QTimer>
#include <QFont>
#include <QDebug>
#include <QPainter>
#include <QPen>

class myButton : public QPushButton
{
    Q_OBJECT
public:
    int btnSelected;
    friend class QTimer;
    static int numClicks_;// return 0:first time in this round I click ;       return 1:second time;
    myButton(QWidget *parent);
    int type;//如果不为空，这是从1到12的一个int.如果为空，是0.
    bool myPiece;
    bool known;
    int x;
    int y;
    bool isStation;
public slots:
    void wrongMove();
    void flushButton();
    void analyseType(bool isRed);
    void myupdate();//根据棋子类型更新type和icon
private:
    QTimer* timer;
};

#endif // MYBUTTON_H
