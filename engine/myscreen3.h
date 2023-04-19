#ifndef MYSCREEN3_H
#define MYSCREEN3_H

#include <QWidget>
#include"mainwindow.h"
namespace Ui {
class myscreen3;
}

class myscreen3 : public QWidget
{
    Q_OBJECT

public:
    explicit myscreen3(QWidget *parent = nullptr);
    ~myscreen3();
    QTimer *timer;
    void setLED(QLabel* label, int color, int size);

private slots:

private:
    Ui::myscreen3 *ui;
};

#endif // MYSCREEN3_H
