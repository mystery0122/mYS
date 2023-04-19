#include "myscreen4.h"
#include "ui_myscreen4.h"

myscreen4::myscreen4(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myscreen4)
{
    ui->setupUi(this);
     setFixedSize(1920,1080);
    this->setAttribute(Qt::WA_QuitOnClose,false);

    ui->engineplot1->addGraph();
    ui->engineplot1->legend->setVisible(true);
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);

    ui->engineplot1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);//可以进行鼠标位置 放大缩小 拖拽  放大缩小坐标系


    timer = new QTimer(this);
    timer->setInterval(200);
    connect(timer,&QTimer::timeout,this,[=](){
       freplot();
    });
    timer->start();
}

myscreen4::~myscreen4()
{
    delete ui;
}
void myscreen4::freplot(){
    static int i=0;
    ui->engineplot1->graph(0)->addData(i,sin(i));
    i++;
    ui->engineplot1->xAxis->setRange(i-20, i+20);
    ui->engineplot1->replot();
}
