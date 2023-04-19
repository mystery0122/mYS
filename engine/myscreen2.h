#ifndef MYSCREEN2_H
#define MYSCREEN2_H

#include <QWidget>
#include<QTimer>
#include"mainwindow.h"
namespace Ui {
class myscreen2;
}

class myscreen2 : public QWidget
{
    Q_OBJECT

public:
    explicit myscreen2(QWidget *parent = nullptr);
    ~myscreen2();

private:
    Ui::myscreen2 *ui;
    QTimer *timer;
};

#endif // MYSCREEN2_H
