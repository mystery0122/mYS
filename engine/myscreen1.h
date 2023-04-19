#ifndef MYSCREEN1_H
#define MYSCREEN1_H

#include <QWidget>
#include<mainwindow.h>
namespace Ui {
class myscreen1;
}

class myscreen1 : public QWidget
{
    Q_OBJECT

public:
    explicit myscreen1(QWidget *parent = nullptr);
    ~myscreen1();
QTimer *timer;
public slots:
    void freplot();//分屏画图接收

    void showplot();
private:
    Ui::myscreen1 *ui;
};

#endif // MYSCREEN1_H
