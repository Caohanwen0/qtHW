#ifndef MYRESULT_H
#define MYRESULT_H

#include <QDialog>

namespace Ui {
class myResult;
}

class myResult : public QDialog
{
    Q_OBJECT

public:
    void setNot20RoundYet();
    void setRes(bool win);
    explicit myResult(QWidget *parent = nullptr);
    ~myResult();

signals:
    void callEnd();
public slots:
    void onClickOK();

private:
    Ui::myResult *ui;
};

#endif // MYRESULT_H
