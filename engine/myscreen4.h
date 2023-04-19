#ifndef MYSCREEN4_H
#define MYSCREEN4_H

#include <QWidget>
#include"mainwindow.h"

namespace Ui {
class myscreen4;
}

class myscreen4 : public QWidget
{
    Q_OBJECT

public:
    explicit myscreen4(QWidget *parent = nullptr);
    ~myscreen4();
    QTimer *timer;
    void freplot();
private:
    Ui::myscreen4 *ui;
};

#endif // MYSCREEN4_H
