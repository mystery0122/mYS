#include "myscreen1.h"
#include "ui_myscreen1.h"

myscreen1::myscreen1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myscreen1)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_QuitOnClose,false);
     setFixedSize(1920,1080);

    ui->fp1->addGraph();//添加数据曲线（一个图像可以有多个数据曲线）
    ui->fp1->graph()->setName("燃油计量阀阀芯位置");

    ui->fp1->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop|Qt::AlignLeft);
    ui->fp1->legend->setBrush(QColor(255,255,255,0));//设置图例背景
    ui->fp1->legend->setBorderPen(Qt::NoPen);

    ui->fp1->graph(0)->rescaleAxes();
    ui->fp1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->fp1->legend->setVisible(true); // 显示图例

    ui->fp2->addGraph();

    ui->fp2->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop|Qt::AlignLeft);
    ui->fp2->legend->setBrush(QColor(255,255,255,0));//设置图例背景
    ui->fp2->legend->setBorderPen(Qt::NoPen);

    ui->fp2->graph(0)->setName("TCM计量阀阀芯位置");
    ui->fp2->graph()->rescaleAxes();
    ui->fp2->addGraph();
    ui->fp2->graph(1)->setName("关断控制阀阀芯位置");
    ui->fp2->addGraph();
    ui->fp2->graph(2)->setName("高压关断阀阀芯位置");
    ui->fp2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->fp2->legend->setVisible(true); // 显示图例
    ui->fp2->graph(0)->setPen(QPen(Qt::blue));
    ui->fp2->graph(1)->setPen(QPen(Qt::black));
    ui->fp2->graph(2)->setPen(QPen(Qt::red));




    ui->fp3->addGraph();

    ui->fp3->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop|Qt::AlignLeft);
    ui->fp3->legend->setBrush(QColor(255,255,255,0));//设置图例背景
    ui->fp3->legend->setBorderPen(Qt::NoPen);

    ui->fp3->graph(0)->setName("计量阀入口夹钳流量计");
    ui->fp3->graph()->rescaleAxes();
    ui->fp3->addGraph();
    ui->fp3->graph(1)->setName("关断阀入口夹钳流量计");
    ui->fp3->addGraph();
    ui->fp3->graph(2)->setName("旁通阀出口夹钳流量计");
    ui->fp3->addGraph();
    ui->fp3->graph(3)->setName("泄露油管路夹钳流量计");
     ui->fp3->legend->setVisible(true);
    ui->fp3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->fp3->graph(0)->setPen(QPen(Qt::blue));
    ui->fp3->graph(1)->setPen(QPen(Qt::black));
    ui->fp3->graph(2)->setPen(QPen(Qt::red));
    ui->fp3->graph(3)->setPen(QPen(Qt::green));

    ui->fp4->addGraph();

    ui->fp4->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop|Qt::AlignLeft);
    ui->fp4->legend->setBrush(QColor(255,255,255,0));//设置图例背景
    ui->fp4->legend->setBorderPen(Qt::NoPen);

    ui->fp4->graph(0)->setName("回油压力");
    ui->fp4->graph()->rescaleAxes();
    ui->fp4->addGraph();
    ui->fp4->graph(1)->setName("P4");
    ui->fp4->addGraph();
    ui->fp4->graph(2)->setName("P3");
    ui->fp4->addGraph();
    ui->fp4->graph(3)->setName("P2");
    ui->fp4->addGraph();
    ui->fp4->graph(4)->setName("P2P3P4");
    ui->fp4->addGraph();
    ui->fp4->graph(5)->setName("P1");
    ui->fp4->addGraph();
    ui->fp4->graph(6)->setName("关断阀P口");
    ui->fp4->legend->setVisible(true);
    ui->fp4->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->fp4->graph(0)->setPen(QPen(Qt::blue));
    ui->fp4->graph(1)->setPen(QPen(Qt::black));
    ui->fp4->graph(2)->setPen(QPen(Qt::red));
    ui->fp4->graph(3)->setPen(QPen(Qt::green));
    ui->fp4->graph(4)->setPen(QPen(Qt::yellow));
    ui->fp4->graph(5)->setPen(QPen(Qt::cyan));
    ui->fp4->graph(6)->setPen(QPen(Qt::magenta));


    ui->fp5->addGraph();

    ui->fp5->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop|Qt::AlignLeft);
    ui->fp5->legend->setBrush(QColor(255,255,255,0));//设置图例背景
    ui->fp5->legend->setBorderPen(Qt::NoPen);

    ui->fp5->graph(0)->setName("二通比例调速阀阀芯位置");
    ui->fp5->graph()->rescaleAxes();
    ui->fp5->addGraph();
    ui->fp5->graph(1)->setName("VSV伺服阀LVDT位移传感器");
    ui->fp5->addGraph();
    ui->fp5->graph(2)->setName("VSV拉压力传感器");
    ui->fp5->addGraph();
    ui->fp5->legend->setVisible(true);
    ui->fp5->graph(3)->setName("VSV伺服激光位移传感器");
    ui->fp5->graph(0)->setPen(QPen(Qt::blue));
    ui->fp5->graph(1)->setPen(QPen(Qt::black));
    ui->fp5->graph(2)->setPen(QPen(Qt::red));
    ui->fp5->graph(3)->setPen(QPen(Qt::green));

    ui->fp6->addGraph();

    ui->fp6->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop|Qt::AlignLeft);
    ui->fp6->legend->setBrush(QColor(255,255,255,0));//设置图例背景
    ui->fp6->legend->setBorderPen(Qt::NoPen);
    ui->fp6->legend->setVisible(true);
    ui->fp6->graph(0)->setName("出油涡轮流量计");
    ui->fp6->graph()->rescaleAxes();
    ui->fp6->addGraph();
    ui->fp6->graph(1)->setName("回油涡轮流量计");
    ui->fp6->graph(0)->setPen(QPen(Qt::blue));
    ui->fp6->graph(1)->setPen(QPen(Qt::black));

    ui->fp1->yAxis->setRange(-1, 11);
    ui->fp2->yAxis->setRange(-1, 11);
    ui->fp3->yAxis->setRange(-1, 70);
    ui->fp4->yAxis->setRange(-5, 50);
    ui->fp5->yAxis->setRange(-1, 11);
    ui->fp6->yAxis->setRange(0, 800);


    timer = new QTimer(this);
    timer->setInterval(200);
    connect(timer,&QTimer::timeout,this,[=](){
       freplot();
       showplot();
    });
    timer->start();
    //ui->fp1->graph(0)->addData(v0.back(),v1.back());

}
void myscreen1::freplot(){
    ui->fp1->graph(0)->addData(v0.back(),v1.back());
    ui->fp1->graph(0)->addData(v0.back(),v1.back());

    ui->fp1->xAxis->setRange(v0.back()-19000, v0.back()+1000);
    ui->fp1->replot();

    ui->fp2->graph(0)->addData(v0.back(),v2.back());
    ui->fp2->graph(1)->addData(v0.back(),v3.back());
    ui->fp2->graph(2)->addData(v0.back(),v4.back());

    ui->fp2->xAxis->setRange(v0.back()-19000, v0.back()+1000);
    ui->fp2->replot();

    ui->fp3->graph(0)->addData(v0.back(),v9.back());
    ui->fp3->graph(1)->addData(v0.back(),v10.back());
    ui->fp3->graph(2)->addData(v0.back(),v11.back());
    ui->fp3->graph(3)->addData(v0.back(),v12.back());

     ui->fp3->xAxis->setRange(v0.back()-19000, v0.back()+1000);
    ui->fp3->replot();


    ui->fp4->graph(0)->addData(v0.back(),v13.back());
    ui->fp4->graph(1)->addData(v0.back(),v14.back());
    ui->fp4->graph(2)->addData(v0.back(),v15.back());
    ui->fp4->graph(3)->addData(v0.back(),v16.back());
    ui->fp4->graph(4)->addData(v0.back(),v17.back());
    ui->fp4->graph(5)->addData(v0.back(),v18.back());
    ui->fp4->graph(6)->addData(v0.back(),v19.back());

    ui->fp4->xAxis->setRange(v0.back()-19000, v0.back()+1000);
    ui->fp4->replot();

    ui->fp5->graph(0)->addData(v0.back(),v5.back());

    ui->fp5->graph(1)->addData(v0.back(),v6.back());
    ui->fp5->graph(2)->addData(v0.back(),v7.back());
    ui->fp5->graph(3)->addData(v0.back(),v8.back());

     ui->fp5->xAxis->setRange(v0.back()-19000, v0.back()+1000);
    ui->fp5->replot();


    ui->fp6->graph(0)->addData(v0.back(),v20.back());
    ui->fp6->graph(1)->addData(v0.back(),v21.back());

    ui->fp6->xAxis->setRange(v0.back()-19000, v0.back()+1000);
    ui->fp6->replot();

}
void myscreen1::showplot(){
    if(global::p0==1){
         ui->fp1->graph()->setVisible(true);
    }
    else if(global::p0==0){
        ui->fp1->graph()->setVisible(false);
    }
    if(global::p1==1){
         ui->fp2->graph(0)->setVisible(true);
    }
    else if(global::p1==0){
        ui->fp2->graph(0)->setVisible(false);
    }
    if(global::p2==1){
         ui->fp2->graph(1)->setVisible(true);
    }
    else if(global::p2==0){
        ui->fp2->graph(1)->setVisible(false);
    }
    if(global::p3==1){
         ui->fp2->graph(2)->setVisible(true);
    }
    else if(global::p3==0){
        ui->fp2->graph(2)->setVisible(false);
    }
    if(global::p4==1){
         ui->fp3->graph(0)->setVisible(true);
    }
    else if(global::p4==0){
        ui->fp3->graph(0)->setVisible(false);
    }
    if(global::p5==1){
         ui->fp3->graph(1)->setVisible(true);
    }
    else if(global::p5==0){
        ui->fp3->graph(1)->setVisible(false);
    }
    if(global::p6==1){
         ui->fp3->graph(2)->setVisible(true);
    }
    else if(global::p6==0){
        ui->fp3->graph(2)->setVisible(false);
    }
    if(global::p7==1){
         ui->fp3->graph(3)->setVisible(true);
    }
    else if(global::p7==0){
        ui->fp3->graph(3)->setVisible(false);
    }
    if(global::p8==1){
         ui->fp4->graph(0)->setVisible(true);
    }
    else if(global::p8==0){
        ui->fp4->graph(0)->setVisible(false);
    }
    if(global::p9==1){
         ui->fp4->graph(1)->setVisible(true);
    }
    else if(global::p9==0){
        ui->fp4->graph(1)->setVisible(false);
    }
    if(global::p10==1){
         ui->fp4->graph(2)->setVisible(true);
    }
    else if(global::p10==0){
        ui->fp4->graph(2)->setVisible(false);
    }
    if(global::p11==1){
         ui->fp4->graph(3)->setVisible(true);
    }
    else if(global::p11==0){
        ui->fp4->graph(3)->setVisible(false);
    }
    if(global::p12==1){
         ui->fp4->graph(4)->setVisible(true);
    }
    else if(global::p12==0){
        ui->fp4->graph(4)->setVisible(false);
    }
    if(global::p13==1){
         ui->fp4->graph(5)->setVisible(true);
    }
    else if(global::p13==0){
        ui->fp4->graph(5)->setVisible(false);
    }
    if(global::p14==1){
         ui->fp4->graph(6)->setVisible(true);
    }
    else if(global::p14==0){
        ui->fp4->graph(6)->setVisible(false);
    }

    if(global::p15==1){
         ui->fp5->graph(0)->setVisible(true);
    }
    else if(global::p15==0){
        ui->fp5->graph(0)->setVisible(false);
    }
    if(global::p16==1){
         ui->fp5->graph(1)->setVisible(true);
    }
    else if(global::p16==0){
        ui->fp5->graph(1)->setVisible(false);
    }
    if(global::p17==1){
         ui->fp5->graph(2)->setVisible(true);
    }
    else if(global::p17==0){
        ui->fp5->graph(2)->setVisible(false);
    }
    if(global::p18==1){
         ui->fp5->graph(3)->setVisible(true);
    }
    else if(global::p18==0){
        ui->fp5->graph(3)->setVisible(false);
    }
    if(global::p19==1){
         ui->fp6->graph(0)->setVisible(true);
    }
    else if(global::p19==0){
        ui->fp6->graph(0)->setVisible(false);
    }
    if(global::p20==1){
         ui->fp6->graph(1)->setVisible(true);
    }
    else if(global::p20==0){
        ui->fp6->graph(1)->setVisible(false);
    }

}

myscreen1::~myscreen1()
{
    delete ui;
}
