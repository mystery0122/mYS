#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "model_thread.h"
#include "file.h"
#include "opt_file.h"
#include <QVariant>
#include"myscreen1.h"
#include"myscreen2.h"
#include"myscreen3.h"
#include"myscreen4.h"
myscreen1 *plt1;
myscreen2 *plt2;
myscreen3 *plt3;
myscreen4 *plt4;

QVector<double> v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32,v33,v34,v35,v36,v37,v38,v39,v40,v41,v42,v43,v44,v45,v46,v47,v48,v49,v50;
QVector<double> v51,v52,v53,v54,v55,v56,v57,v58,v59,v60,v61,v62,v63,v64,v65,v66,v67,v68,v69,v70,v71,v72,v73,v74,v75,v76,v77,v78,v79,v80,v81,v82,v83,v84,v85;
QVector<double> t0,d0,t1,d1,t2,d2,t3,d3,t4,d4,t5,d5,t6,d6,t7,d7,t8,d8,t9,d9,t10,d10,t11,d11,t12,d12,t13,d13,t14,d14,t15,d15,t16,d16,t17,d17;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setFixedSize(1920,1080);
     setLED(ui->label_led,1,16);
    setWindowTitle("燃油系统仿真实验平台");

     qRegisterMetaType<QVariant>("QVariant");

    setplot();

    tcpServer = new QTcpServer(this);
    // 新的连接
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(mNewConnetion()));

    /*定时器与时间*/
    timer = new QTimer(this);

//    timerplot = new QTimer(this);
//    timerplot->setInterval(100);
//    connect(timer,&QTimer::timeout,this,[=](){
//       replot();
//    });

//    timerplot->start();

    timersend = new QTimer(this);
    timersend->setInterval(100);
    connect(timersend,&QTimer::timeout,this,[=](){
        global::sendcount+=100;//计算运行时间
        static int ct0,ct1,ct2,ct3,ct4,ct5,ct9,ct10,ct11,ct12,ct13,ct14,ct15,ct16,ct17=0;//不能使用同一个计数变量

        if(!d0.isEmpty()){
        textsend(global::c13,ct0,t0,d0);}
        if(!d1.isEmpty()){
        textsend(global::c10,ct1,t1,d1);}
        if(!d2.isEmpty()){
        textsend(global::c12,ct2,t2,d2);}
        if(!d3.isEmpty()){
        textsend(global::c11,ct3,t3,d3);}
        if(!d4.isEmpty()){
        textsend(global::c0,ct4,t4,d4);}
        if(!d5.isEmpty()){
        textsend(global::c1,ct5,t5,d5);}
        if(!d9.isEmpty()){
        textsend(global::c4,ct9,t9,d9);}
        if(!d10.isEmpty()){
        textsend(global::c7,ct10,t10,d10);}
        if(!d11.isEmpty()){
        textsend(global::c20,ct11,t11,d11);}
        if(!d12.isEmpty()){
        textsend(global::c17,ct12,t12,d12);}
        if(!d13.isEmpty()){
        textsend(global::c18,ct13,t13,d13);}
        if(!d14.isEmpty()){
        textsend(global::c19,ct14,t14,d14);}
        if(!d15.isEmpty()){
        textsend(global::c14,ct15,t15,d15);}
        if(!d16.isEmpty()){
        textsend(global::c15,ct16,t16,d16);}
        if(!d17.isEmpty()){
        textsend(global::c16,ct17,t17,d17);}
        on_pushButton_send_clicked();
    });

    //udp连接
    udpSocket = new QUdpSocket(this);
    connect(udpSocket,&QUdpSocket::readyRead,this,&MainWindow::udp_readyread);

    connect(udpSocket,&QUdpSocket::readyRead,this,&MainWindow::led);
    connect(this,SIGNAL(plot()),this,SLOT(replot()));

//    timerplot = new QTimer(this);
//    timerplot->setInterval(200);
//    connect(timerplot,&QTimer::timeout,this,SLOT(replot()));


    //打开文件
    QString textFile = QFileDialog::getSaveFileName(this,tr("Save txt"),
                                                               "",tr("text (*.txt)")); //选择路径
    file_1= new QFile(textFile);
    file_1->open(QIODevice::ReadWrite|QIODevice::Append);


    setLED(ui->labelset1,1,16);
    setLED(ui->labelset2,1,16);
    setLED(ui->labelset3,1,16);
    setLED(ui->labelset4,1,16);
    setLED(ui->labelset5,2,16);
    setLED(ui->labelset6,2,16);
    setLED(ui->labelset7,3,16);
    setLED(ui->labelset8,3,16);
    setLED(ui->labelset9,3,16);
    setLED(ui->labelset10,2,16);
    setLED(ui->labelset11,1,16);
    setLED(ui->labelset12,1,16);
    setLED(ui->labelset13,1,16);
    setLED(ui->labelset14,1,16);
    setLED(ui->labelset15,1,16);
    setLED(ui->labelset16,1,16);
    setLED(ui->labelset17,1,16);
    setLED(ui->labelset18,1,16);

    setLED(ui->timeled1,0,16);
    setLED(ui->timeled2,0,16);
    setLED(ui->timeled3,0,16);
    setLED(ui->timeled4,0,16);
    setLED(ui->timeled5,0,16);
    setLED(ui->timeled6,0,16);
    setLED(ui->timeled10,0,16);
    setLED(ui->timeled11,0,16);
    setLED(ui->timeled12,0,16);
    setLED(ui->timeled13,0,16);
    setLED(ui->timeled14,0,16);
    setLED(ui->timeled15,0,16);
    setLED(ui->timeled16,0,16);
    setLED(ui->timeled17,0,16);
    setLED(ui->timeled18,0,16);

    setLED(ui->checklabel,0,16);

     setLED(ui->label_led_2,1,16);

}


MainWindow::~MainWindow()
{
    emit sigDisconnected();//断开连接
    delete ui;
}
//init slot
void MainWindow::setplot(){

    ui->cplot1->addGraph();//添加数据曲线（一个图像可以有多个数据曲线）
    ui->cplot1->graph()->setName("燃油计量阀阀芯位置");

    ui->cplot1->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop|Qt::AlignLeft);
    ui->cplot1->legend->setBrush(QColor(255,255,255,0));//设置图例背景
    ui->cplot1->legend->setBorderPen(Qt::NoPen);

    ui->cplot1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->cplot1->legend->setVisible(true); // 显示图例

    ui->cplot2->addGraph();
    ui->cplot2->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop|Qt::AlignLeft);
    ui->cplot2->legend->setBrush(QColor(255,255,255,0));//设置图例背景
    ui->cplot2->legend->setBorderPen(Qt::NoPen);
    ui->cplot2->graph()->setName("TCM控制阀阀芯位置");
    ui->cplot2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->cplot2->addGraph();
    ui->cplot2->graph(1)->setName("关断控制阀阀芯位置");
    ui->cplot2->legend->setVisible(true);
    ui->cplot2->addGraph();
    ui->cplot2->graph(2)->setName("高压关断阀阀芯位置");
    ui->cplot2->graph(0)->setPen(QPen(Qt::blue));
    ui->cplot2->graph(1)->setPen(QPen(Qt::black));
    ui->cplot2->graph(2)->setPen(QPen(Qt::red));


    ui->cplot5->addGraph();

    ui->cplot5->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop|Qt::AlignLeft);
    ui->cplot5->legend->setBrush(QColor(255,255,255,0));//设置图例背景
    ui->cplot5->legend->setBorderPen(Qt::NoPen);

    ui->cplot5->graph(0)->setName("计量阀入口夹钳流量");
    ui->cplot5->graph(0)->setPen(QPen(Qt::blue));
    ui->cplot5->addGraph();
    ui->cplot5->graph(1)->setName("关断阀入口夹钳流量");
    ui->cplot5->graph(1)->setPen(QPen(Qt::red));
     ui->cplot5->addGraph();
     ui->cplot5->graph(2)->setName("旁通阀出口夹钳流量");
     ui->cplot5->graph(2)->setPen(QPen(Qt::green));
     ui->cplot5->addGraph();
     ui->cplot5->graph(3)->setName("泄露油管夹钳流量计");
    ui->cplot5->graph(3)->setPen(QPen(Qt::black));
    ui->cplot5->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->cplot5->legend->setVisible(true); // 显示图例

    ui->cplot3->addGraph();
    ui->cplot3->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop|Qt::AlignLeft);
    ui->cplot3->legend->setBrush(QColor(255,255,255,0));//设置图例背景
    ui->cplot3->legend->setBorderPen(Qt::NoPen);

    ui->cplot3->graph(0)->setName("回油压力");
    ui->cplot3->addGraph();
    ui->cplot3->graph(1)->setName("P4");
    ui->cplot3->addGraph();
    ui->cplot3->graph(2)->setName("P3");
    ui->cplot3->addGraph();
    ui->cplot3->graph(3)->setName("P2");
    ui->cplot3->addGraph();
    ui->cplot3->graph(4)->setName("P2P3P4");
    ui->cplot3->addGraph();
    ui->cplot3->graph(5)->setName("P1");
    ui->cplot3->addGraph();
    ui->cplot3->graph(6)->setName("关断阀P口");
    ui->cplot3->legend->setVisible(true);
    ui->cplot3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->cplot3->graph(0)->setPen(QPen(Qt::blue));
    ui->cplot3->graph(1)->setPen(QPen(Qt::black));
    ui->cplot3->graph(2)->setPen(QPen(Qt::red));
    ui->cplot3->graph(3)->setPen(QPen(Qt::green));
    ui->cplot3->graph(4)->setPen(QPen(Qt::yellow));
    ui->cplot3->graph(5)->setPen(QPen(Qt::cyan));
    ui->cplot3->graph(6)->setPen(QPen(Qt::magenta));


    ui->cplot4->addGraph();

    ui->cplot4->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop|Qt::AlignLeft);
    ui->cplot4->legend->setBrush(QColor(255,255,255,0));//设置图例背景
    ui->cplot4->legend->setBorderPen(Qt::NoPen);

    ui->cplot4->graph(0)->setName("二通比例调速阀阀芯位置");
    ui->cplot4->addGraph();
    ui->cplot4->graph(1)->setName("VSV伺服阀LVDT位移传感器");
    ui->cplot4->addGraph();
    ui->cplot4->graph(2)->setName("VSV拉压力传感器");
    ui->cplot4->addGraph();
    ui->cplot4->legend->setVisible(true);
    ui->cplot4->graph(3)->setName("VSV伺服激光位移传感器");
    ui->cplot4->graph(0)->setPen(QPen(Qt::blue));
    ui->cplot4->graph(1)->setPen(QPen(Qt::black));
    ui->cplot4->graph(2)->setPen(QPen(Qt::red));
    ui->cplot4->graph(3)->setPen(QPen(Qt::green));

    ui->cplot6->addGraph();

    ui->cplot6->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop|Qt::AlignLeft);
    ui->cplot6->legend->setBrush(QColor(255,255,255,0));//设置图例背景
    ui->cplot6->legend->setBorderPen(Qt::NoPen);

    ui->cplot6->graph(0)->setName("出油涡轮流量计");
    ui->cplot6->addGraph();
    ui->cplot6->graph(1)->setName("回油涡轮流量计");
    ui->cplot6->graph(0)->setPen(QPen(Qt::blue));
    ui->cplot6->graph(1)->setPen(QPen(Qt::black));
    ui->cplot6->legend->setVisible(true);

    ui->cplot1->yAxis->setRange(-1, 11);
    ui->cplot2->yAxis->setRange(-1, 11);
    ui->cplot5->yAxis->setRange(-1, 70);
    ui->cplot3->yAxis->setRange(-5, 50);
    ui->cplot4->yAxis->setRange(-1, 11);
    ui->cplot6->yAxis->setRange(0, 800);

/**发动机画图**/
    ui->engineplot1->addGraph();//添加数据曲线
    ui->engineplot1->graph()->setName("发动机数据");
    ui->engineplot1->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop|Qt::AlignLeft);
    ui->engineplot1->legend->setBrush(QColor(255,255,255,0));//设置图例背景
    ui->engineplot1->legend->setBorderPen(Qt::NoPen);
    ui->engineplot1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->engineplot1->legend->setVisible(true);

/**飞机画图**/
    ui->airplot1->addGraph();//添加数据曲线
    ui->airplot1->graph()->setName("飞机数据");
    ui->airplot1->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop|Qt::AlignLeft);
    ui->airplot1->legend->setBrush(QColor(255,255,255,0));//设置图例背景
    ui->airplot1->legend->setBorderPen(Qt::NoPen);
    ui->airplot1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->airplot1->legend->setVisible(true);

}

//udp接收解析
void MainWindow::udp_readyread(){
    QTextStream out(file_1);



    while(udpSocket->hasPendingDatagrams())
        {
            QByteArray data;


            //返回待读取的数据报的字节数
            data.resize(udpSocket->pendingDatagramSize());

            QHostAddress peerAddr;

            quint16 peerPort;

            //读取数据报的内容
            udpSocket->readDatagram(data.data(),data.size(),&peerAddr,&peerPort);
            QString data2= data.data();
            QStringList section2 =data2.split("\n");
            if(section2.size()>=9){
            QStringList section=section2[8].split(" ");

           if(section.size()>30){

                v0.append(section[0].toDouble());//时间
                v1.append(section[1].toDouble());//燃油计量伺服阀
                v2.append(section[2].toDouble());//TCM关断控制伺服阀
                v3.append(section[3].toDouble());//关断控制比例阀
                v4.append(section[4].toDouble());//高压关断阀
                v5.append(section[5].toDouble());//二通比例调速阀
                v6.append(section[6].toDouble());//VSV伺服阀 LVDT位移传感器
                v7.append(section[7].toDouble());//VSV伺服阀 拉压力传感器
                v8.append(section[8].toDouble());//VSV伺服阀 激光位移传感器
                v9.append(section[9].toDouble());//计量阀入口夹钳流量计
                v10.append(section[10].toDouble());//关断阀入口夹钳流量计
                v11.append(section[11].toDouble());//旁通阀出口夹钳流量计
                v12.append(section[12].toDouble());//泄露油管路夹钳流量计
                v13.append(section[13].toDouble());//回油压力传感器
                v14.append(section[14].toDouble());//P4 压力传感器
                v15.append(section[15].toDouble());//P3 压力传感器
                v16.append(section[16].toDouble());//P2 压力传感器
                v17.append(section[17].toDouble());//P2P3P4回油压力传感器
                v18.append(section[18].toDouble());//P1 压力传感器
                v19.append(section[19].toDouble());//关断阀P口压力传感器
                v20.append(section[20].toDouble());//出油涡轮流量计
                v21.append(section[21].toDouble());//回油涡轮流量计

                v22.append(section[22].toDouble());//实际控制电压 m_SendData.FuelMeteringServoIn;
                v23.append(section[23].toDouble());//实际控制电压 m_SendData.TCMIn;
                v24.append(section[24].toDouble());//实际控制电压 m_SendData.ShutoffControlIn;
                v25.append(section[25].toDouble());//实际控制电压 m_SendData.ProportionalSpeedControlIn;
                v26.append(section[26].toDouble());//实际控制电压 m_SendData.VSVAmplification;
                v27.append(section[27].toDouble());//实际控制电压 m_SendData.OverRotating;
                v28.append(section[28].toDouble());//实际控制电压 m_SendData.ShutoffPilot;

                v29.append(section[29].toDouble());//diff
                v30.append(section[30].toDouble());//diffFlag

                v31.append(section[31].toDouble());//燃油流量
                v32.append(section[32].toDouble());//压气机可调导叶
                v33.append(section[33].toDouble());//压气机可调放气活门
                v34.append(section[34].toDouble());//瞬时放气阀门
                v35.append(section[35].toDouble());//高压转子转速
                v36.append(section[36].toDouble());//低压转子转速
                v37.append(section[37].toDouble());//高压压气机进口总压
                v38.append(section[38].toDouble());//高压压气机进口温度
                v39.append(section[39].toDouble());//高压压气机出口静压
                v40.append(section[40].toDouble());//高压压气机出口总温
                v41.append(section[41].toDouble());//排气温度
                v42.append(section[42].toDouble());//发动机推力
                v43.append(section[43].toDouble());//风扇喘振裕度
                v44.append(section[44].toDouble());//低压压气机入口喘振裕度
                v45.append(section[45].toDouble());//高压压气机入口喘振裕度

                v46.append(section[46].toDouble());//飞行速度
                v47.append(section[47].toDouble());//飞行高度
                v48.append(section[48].toDouble());//俯仰角
                v49.append(section[49].toDouble());//攻角
                v50.append(section[50].toDouble());//推力指令
                v51.append(section[51].toDouble());//实际推力

                v52.append(section[52].toDouble());   //m_RecvData.FuelMeteringServoOut;
                v53.append(section[53].toDouble());   //m_RecvData.TCMOut;
                v54.append(section[54].toDouble());   //m_RecvData.HighPressure;
                v55.append(section[55].toDouble());   //m_RecvData.FuelIn;
                v56.append(section[56].toDouble());  //模式判断
                v57.append(section[57].toDouble());  //燃油计量伺服阀电压输入(V)
                v58.append(section[58].toDouble());  //TCM关断控制伺服阀电压输入(V
                v59.append(section[59].toDouble());  //关断控制比例阀电压输入(V)
                v60.append(section[60].toDouble());  //二通比例调速阀电压输入(V)
                v61.append(section[61].toDouble());  //VSV伺服阀放大板电压输入(V)
                v62.append(section[62].toDouble());  //超转保护泄油阀(IO）
                v63.append(section[63].toDouble());  //电动关断先导阀(IO)
                v64.append(section[64].toDouble());  //燃油阀PID输入
                v65.append(section[65].toDouble());  //VSV PID输入
                v66.append(section[66].toDouble());  //TCM模式输出燃油流量设定
                v67.append(section[67].toDouble());  //输出燃油流量设定
                v68.append(section[68].toDouble());  //飞机飞行高度设定
                v69.append(section[69].toDouble());   //飞机飞行速度设定
                v70.append(section[70].toDouble());   //飞机飞行轨迹设定
                v71.append(section[71].toDouble());   //发动机N1转速设定
                v72.append(section[72].toDouble());   //发动机输出推力设定
                v73.append(section[73].toDouble());   //发动机工作高度设定
                v74.append(section[74].toDouble());   //发动机工作MA设定
                v75.append(section[75].toDouble());   //发动机工作温度设定
                v76.append(section[76].toDouble());   //AIM nl
                v77.append(section[77].toDouble());   //nl
                v78.append(section[78].toDouble());   //IE huansuan fuel
                v79.append(section[79].toDouble());   //engine_far_command
                v80.append(section[80].toDouble());
                v81.append(section[81].toDouble());
                v82.append(section[82].toDouble());
                v83.append(section[83].toDouble());
                v84.append(section[84].toDouble());

//显示
                ui->spinBox_1->setValue(v0.back());
                ui->spinBox_2->setValue(v1.back());
                ui->spinBox_3->setValue(v2.back());
                ui->spinBox_4->setValue(v3.back());
                ui->spinBox_5->setValue(v4.back());
                ui->spinBox_6->setValue(v5.back());
                ui->spinBox_7->setValue(v6.back());
                ui->spinBox_8->setValue(v7.back());
                ui->spinBox_9->setValue(v8.back());
                ui->spinBox_10->setValue(v9.back());
                ui->spinBox_11->setValue(v10.back());
                ui->spinBox_12->setValue(v11.back());
                ui->spinBox_13->setValue(v12.back());
                ui->spinBox_14->setValue(v13.back());
                ui->spinBox_15->setValue(v14.back());
                ui->spinBox_16->setValue(v15.back());
                ui->spinBox_17->setValue(v16.back());
                ui->spinBox_18->setValue(v17.back());
                ui->spinBox_19->setValue(v18.back());
                ui->spinBox_20->setValue(v19.back());
                ui->spinBox_21->setValue(v20.back());
                ui->spinBox_22->setValue(v21.back());
                ui->spinBox_23->setValue(v29.back());//diffFlag

                ui->spinBox_26->setValue(v22.back()); //实际控制电压
                ui->spinBox_27->setValue(v23.back()); //实际控制电压
                ui->spinBox_28->setValue(v24.back()); //实际控制电压
                ui->spinBox_29->setValue(v25.back()); //实际控制电压
                ui->spinBox_30->setValue(v26.back()); //实际控制电压
                ui->spinBox31->setValue(v27.back());  //实际控制电压
                ui->spinBox32->setValue(v28.back());  //实际控制电压
//发动机
                ui->enginebox1->setValue(v31.back());
                ui->enginebox1_2->setValue(v32.back());
                ui->enginebox1_3->setValue(v33.back());
                ui->enginebox1_4->setValue(v34.back());
                ui->enginebox1_5->setValue(v35.back());
                ui->enginebox1_6->setValue(v36.back());
                ui->enginebox1_7->setValue(v37.back());
                ui->enginebox1_8->setValue(v38.back());
                ui->enginebox1_9->setValue(v39.back());
                ui->enginebox1_10->setValue(v40.back());
                ui->enginebox1_11->setValue(v41.back());
                ui->enginebox1_12->setValue(v42.back());
                ui->enginebox1_13->setValue(v43.back());
                ui->enginebox1_14->setValue(v44.back());
                ui->enginebox1_15->setValue(v45.back());
//飞机
                ui->airbox->setValue(v46.back());
                ui->airbox_2->setValue(v47.back());
                ui->airbox_3->setValue(v48.back());
                ui->airbox_4->setValue(v49.back());
                ui->airbox_5->setValue(v50.back());
                ui->airbox_6->setValue(v51.back());

                //换算
                ui->spinBox_72->setValue(v1.back());
                ui->spinBox_73->setValue(v2.back());
                ui->spinBox_74->setValue(v3.back());
                ui->spinBox_75->setValue(v4.back());
                ui->spinBox_76->setValue((v20.back())*59.7/829);
                ui->spinBox_77->setValue((v21.back())*27.9/395);
                ui->spinBox_78->setValue((v9.back()-4)/16*100);
                ui->spinBox_79->setValue((v10.back()-4)/16*60);
                ui->spinBox_80->setValue((v11.back()-4)/16*60);
                ui->spinBox_81->setValue((v12.back()-4)/16*30);
                ui->spinBox_82->setValue((v13.back()-4)/16*40);
                ui->spinBox_83->setValue((v14.back()-4)/16*40);
                ui->spinBox_84->setValue((v15.back()-4)/16*40);
                ui->spinBox_85->setValue((v16.back()-4)/16*40);
                ui->spinBox_86->setValue((v17.back()-4)/16*40);
                ui->spinBox_87->setValue((v18.back()-4)/16*40);
                ui->spinBox_88->setValue((v19.back()-4)/16*40);
                ui->spinBox_89->setValue(v5.back());
                ui->spinBox_90->setValue(9.77-v6.back());
                ui->spinBox_91->setValue(4000*v7.back());
                ui->spinBox_92->setValue(-3.167*v8.back()+12.8);

           }
           static int index=0;
           if(index%40==0){
            emit(plot());
               index=0;
           }
           else{
               index++;
           }
        }
            alldata += data.data();
            out<<alldata;
            alldata.clear();

      }
}


//tcp
void MainWindow::mStateChanged(QAbstractSocket::SocketState state)
{
    QTcpSocket *tmpTcpSocket = (QTcpSocket *)sender();
    switch (state) {
    // 已断开
    case QAbstractSocket::UnconnectedState:
        //ui->textEdit->append("服务端：客户端断开连接");
        tmpTcpSocket->deleteLater();
        break;
        // 已连接
    case QAbstractSocket::ConnectedState:
       // ui->textEdit->append("服务端：客户端已连接");
        break;
    default:
        break;
    }
}


void MainWindow::receiveMessages()
{

}

void MainWindow::mNewConnetion()
{
    // 与客户端连接
    QTcpSocket *tmpTcpSocket = tcpServer->nextPendingConnection();

    // 客户端的ip地址
//    QString ipaddr = tmpTcpSocket->peerAddress().toString();
//    quint16 port = tmpTcpSocket->peerPort();
//    // 打印客户端连接的ip信息
//    ui->textEdit->append("服务端：客户端的ip地址：" + ipaddr);
//    // 打印客户端连接的端口信息
//    ui->textEdit->append("服务端：客户端的端口：" + QString::number(port));

    connect(tmpTcpSocket, SIGNAL(readyRead()), this, SLOT(receiveMessages()));


    connect(tmpTcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(mStateChanged(QAbstractSocket::SocketState)));

}

void MainWindow::on_start_listen_button_clicked()
{
    tcpServer->listen(QHostAddress("192.168.1.2"), 8989);
     udpSocket->bind(2000);

     global::listen_signal=1;

     setLED(ui->label_led,2,16);
}


//燃油阀控制信号与燃油流量为线性关系，直接拟合映射输出信号
//y=0.9647x+0.07943
float MainWindow::fuel_control(float aim_fuel){
    float signal = (aim_fuel-0.07943)/0.9647;
    if(signal>5)return 5;
    else if(signal<0)return 0;
    else
    return (aim_fuel-0.07943)/0.9647;
}


void MainWindow::replot(){

    ui->cplot1->graph(0)->addData(v0.back(),v1.back());
    ui->cplot1->xAxis->setRange(v0.back()-19000, v0.back()+1000);
    ui->cplot1->replot();

    ui->cplot2->graph(0)->addData(v0.back(),v2.back());
    ui->cplot2->graph(1)->addData(v0.back(),v3.back());
    ui->cplot2->graph(2)->addData(v0.back(),v4.back());
    ui->cplot2->xAxis->setRange(v0.back()-19000, v0.back()+1000);
    ui->cplot2->replot();


    ui->cplot5->graph(0)->addData(v0.back(),v9.back());
    ui->cplot5->graph(1)->addData(v0.back(),v10.back());
    ui->cplot5->graph(2)->addData(v0.back(),v11.back());
    ui->cplot5->graph(3)->addData(v0.back(),v12.back());
    ui->cplot5->xAxis->setRange(v0.back()-19000, v0.back()+1000);
    ui->cplot5->replot();

    ui->cplot3->graph(0)->addData(v0.back(),v13.back());
    ui->cplot3->graph(1)->addData(v0.back(),v14.back());
    ui->cplot3->graph(2)->addData(v0.back(),v15.back());
    ui->cplot3->graph(3)->addData(v0.back(),v16.back());
    ui->cplot3->graph(4)->addData(v0.back(),v17.back());
    ui->cplot3->graph(5)->addData(v0.back(),v18.back());
    ui->cplot3->graph(6)->addData(v0.back(),v19.back());
    ui->cplot3->xAxis->setRange(v0.back()-19000, v0.back()+1000);
    ui->cplot3->replot();

    ui->cplot4->graph(0)->addData(v0.back(),v5.back());
    ui->cplot4->graph(1)->addData(v0.back(),v6.back());
    ui->cplot4->graph(2)->addData(v0.back(),v7.back());
    ui->cplot4->graph(3)->addData(v0.back(),v8.back());
    ui->cplot4->xAxis->setRange(v0.back()-19000, v0.back()+1000);
    ui->cplot4->replot();


    ui->cplot6->graph(0)->addData(v0.back(),v20.back());
    ui->cplot6->xAxis->setRange(v0.back()-19000, v0.back()+1000);
     ui->cplot6->graph(1)->addData(v0.back(),v21.back());
    ui->cplot6->replot();






}

// 该函数将label控件变成一个圆形指示灯，需要指定颜色color以及直径size
// color 0:grey 1:red 2:green 3:yellow
// size  单位是像素
void MainWindow::setLED(QLabel* label, int color, int size)
{
    // 将label中的文字清空
    label->setText("");
    // 先设置矩形大小
    // 如果ui界面设置的label大小比最小宽度和高度小，矩形将被设置为最小宽度和最小高度；
    // 如果ui界面设置的label大小比最小宽度和高度大，矩形将被设置为最大宽度和最大高度；
    QString min_width = QString("min-width: %1px;").arg(size);              // 最小宽度：size
    QString min_height = QString("min-height: %1px;").arg(size);            // 最小高度：size
    QString max_width = QString("max-width: %1px;").arg(size);              // 最小宽度：size
    QString max_height = QString("max-height: %1px;").arg(size);            // 最小高度：size
    // 再设置边界形状及边框
    QString border_radius = QString("border-radius: %1px;").arg(size/2);    // 边框是圆角，半径为size/2
    QString border = QString("border:1px solid black;");                    // 边框为1px黑色
    // 最后设置背景颜色
    QString background = "background-color:";
    switch (color) {
    case 0:
        // 灰色
        background += "rgb(190,190,190)";
        break;
    case 1:
        // 红色
        background += "rgb(255,0,0)";
        break;
    case 2:
        // 绿色
        background += "rgb(0,255,0)";
        break;
    case 3:
        // 黄色
        background += "rgb(255,255,0)";
        break;
    default:
        break;
    }

    const QString SheetStyle = min_width + min_height + max_width + max_height + border_radius + border + background;
    label->setStyleSheet(SheetStyle);
}
void MainWindow::led(){


   global::model_n=ui->model->currentIndex();

    if(ui->model->currentIndex()==0){
        ui->send1->setEnabled(false);
        ui->send2->setEnabled(false);
        ui->send3->setEnabled(false);
        ui->send4->setEnabled(false);
        ui->send5->setEnabled(true);
        ui->send6->setEnabled(true);
        ui->send10->setEnabled(true);
        ui->send11->setEnabled(false);
        ui->send12->setEnabled(false);
        ui->send13->setEnabled(false);
        ui->send14->setEnabled(false);
        ui->send15->setEnabled(false);
        ui->send16->setEnabled(false);
        ui->send17->setEnabled(false);
        ui->send18->setEnabled(false);

        setLED(ui->labelset1,1,16);
        setLED(ui->labelset2,1,16);
        setLED(ui->labelset3,1,16);
        setLED(ui->labelset4,1,16);
        setLED(ui->labelset5,2,16);
        setLED(ui->labelset6,2,16);
        setLED(ui->labelset7,3,16);
        setLED(ui->labelset8,3,16);
        setLED(ui->labelset9,3,16);
        setLED(ui->labelset10,2,16);
        setLED(ui->labelset11,1,16);
        setLED(ui->labelset12,1,16);
        setLED(ui->labelset13,1,16);
        setLED(ui->labelset14,1,16);
        setLED(ui->labelset15,1,16);
        setLED(ui->labelset16,1,16);
        setLED(ui->labelset17,1,16);
        setLED(ui->labelset18,1,16);
    }
    else if(ui->model->currentIndex()==1){
        ui->send1->setEnabled(true);
        ui->send2->setEnabled(false);
        ui->send3->setEnabled(false);
        ui->send4->setEnabled(true);
        ui->send5->setEnabled(false);
        ui->send6->setEnabled(false);
        ui->send10->setEnabled(false);
        ui->send11->setEnabled(false);
        ui->send12->setEnabled(false);
        ui->send13->setEnabled(false);
        ui->send14->setEnabled(false);
        ui->send15->setEnabled(false);
        ui->send16->setEnabled(false);
        ui->send17->setEnabled(false);
        ui->send18->setEnabled(false);

        setLED(ui->labelset1,2,16);
        setLED(ui->labelset2,1,16);
        setLED(ui->labelset3,1,16);
        setLED(ui->labelset4,2,16);
        setLED(ui->labelset5,1,16);
        setLED(ui->labelset6,1,16);
        setLED(ui->labelset7,3,16);
        setLED(ui->labelset8,3,16);
        setLED(ui->labelset9,3,16);
        setLED(ui->labelset10,1,16);
        setLED(ui->labelset11,1,16);
        setLED(ui->labelset12,1,16);
        setLED(ui->labelset13,1,16);
        setLED(ui->labelset14,1,16);
        setLED(ui->labelset15,1,16);
        setLED(ui->labelset16,1,16);
        setLED(ui->labelset17,1,16);
        setLED(ui->labelset18,1,16);

    }
    else if(ui->model->currentIndex()==2){

        ui->send1->setEnabled(false);
        ui->send2->setEnabled(true);
        ui->send3->setEnabled(false);
        ui->send4->setEnabled(true);
        ui->send5->setEnabled(false);
        ui->send6->setEnabled(false);
        ui->send10->setEnabled(false);
        ui->send11->setEnabled(false);
        ui->send12->setEnabled(false);
        ui->send13->setEnabled(false);
        ui->send14->setEnabled(false);
        ui->send15->setEnabled(false);
        ui->send16->setEnabled(false);
        ui->send17->setEnabled(false);
        ui->send18->setEnabled(false);

        setLED(ui->labelset1,1,16);
        setLED(ui->labelset2,2,16);
        setLED(ui->labelset3,1,16);
        setLED(ui->labelset4,2,16);
        setLED(ui->labelset5,1,16);
        setLED(ui->labelset6,1,16);
        setLED(ui->labelset7,3,16);
        setLED(ui->labelset8,3,16);
        setLED(ui->labelset9,3,16);
        setLED(ui->labelset10,1,16);
        setLED(ui->labelset11,1,16);
        setLED(ui->labelset12,1,16);
        setLED(ui->labelset13,1,16);
        setLED(ui->labelset14,1,16);
        setLED(ui->labelset15,1,16);
        setLED(ui->labelset16,1,16);
        setLED(ui->labelset17,1,16);
        setLED(ui->labelset18,1,16);
    }
    else if(ui->model->currentIndex()==3){

        ui->send1->setEnabled(true);
        ui->send2->setEnabled(false);
        ui->send3->setEnabled(true);
        ui->send4->setEnabled(true);
        ui->send5->setEnabled(false);
        ui->send6->setEnabled(false);
        ui->send10->setEnabled(false);
        ui->send11->setEnabled(false);
        ui->send12->setEnabled(false);
        ui->send13->setEnabled(false);
        ui->send14->setEnabled(false);
        ui->send15->setEnabled(false);
        ui->send16->setEnabled(false);
        ui->send17->setEnabled(false);
        ui->send18->setEnabled(false);

        setLED(ui->labelset1,2,16);
        setLED(ui->labelset2,1,16);
        setLED(ui->labelset3,2,16);
        setLED(ui->labelset4,2,16);
        setLED(ui->labelset5,1,16);
        setLED(ui->labelset6,1,16);
        setLED(ui->labelset7,3,16);
        setLED(ui->labelset8,3,16);
        setLED(ui->labelset9,3,16);
        setLED(ui->labelset10,1,16);
        setLED(ui->labelset11,1,16);
        setLED(ui->labelset12,1,16);
        setLED(ui->labelset13,1,16);
        setLED(ui->labelset14,1,16);
        setLED(ui->labelset15,1,16);
        setLED(ui->labelset16,1,16);
        setLED(ui->labelset17,1,16);
        setLED(ui->labelset18,1,16);
    }
    else if(ui->model->currentIndex()==4){

        ui->send1->setEnabled(false);
        ui->send2->setEnabled(false);
        ui->send3->setEnabled(false);
        ui->send4->setEnabled(false);
        ui->send5->setEnabled(false);
        ui->send6->setEnabled(false);
        ui->send10->setEnabled(false);
        ui->send11->setEnabled(true);
        ui->send12->setEnabled(false);
        ui->send13->setEnabled(true);
        ui->send14->setEnabled(true);
        ui->send15->setEnabled(true);
        ui->send16->setEnabled(false);
        ui->send17->setEnabled(false);
        ui->send18->setEnabled(false);

        setLED(ui->labelset1,1,16);
        setLED(ui->labelset2,1,16);
        setLED(ui->labelset3,1,16);
        setLED(ui->labelset4,1,16);
        setLED(ui->labelset5,1,16);
        setLED(ui->labelset6,1,16);
        setLED(ui->labelset7,3,16);
        setLED(ui->labelset8,3,16);
        setLED(ui->labelset9,3,16);
        setLED(ui->labelset10,1,16);
        setLED(ui->labelset11,2,16);
        setLED(ui->labelset12,1,16);
        setLED(ui->labelset13,2,16);
        setLED(ui->labelset14,2,16);
        setLED(ui->labelset15,2,16);
        setLED(ui->labelset16,1,16);
        setLED(ui->labelset17,1,16);
        setLED(ui->labelset18,1,16);
    }
    else if(ui->model->currentIndex()==5){

        ui->send1->setEnabled(false);
        ui->send2->setEnabled(false);
        ui->send3->setEnabled(false);
        ui->send4->setEnabled(false);
        ui->send5->setEnabled(false);
        ui->send6->setEnabled(false);
        ui->send10->setEnabled(false);
        ui->send11->setEnabled(false);
        ui->send12->setEnabled(true);
        ui->send13->setEnabled(true);
        ui->send14->setEnabled(true);
        ui->send15->setEnabled(true);
        ui->send16->setEnabled(false);
        ui->send17->setEnabled(false);
        ui->send18->setEnabled(false);

        setLED(ui->labelset1,1,16);
        setLED(ui->labelset2,1,16);
        setLED(ui->labelset3,1,16);
        setLED(ui->labelset4,1,16);
        setLED(ui->labelset5,1,16);
        setLED(ui->labelset6,1,16);
        setLED(ui->labelset7,3,16);
        setLED(ui->labelset8,3,16);
        setLED(ui->labelset9,3,16);
        setLED(ui->labelset10,1,16);
        setLED(ui->labelset11,1,16);
        setLED(ui->labelset12,2,16);
        setLED(ui->labelset13,2,16);
        setLED(ui->labelset14,2,16);
        setLED(ui->labelset15,2,16);
        setLED(ui->labelset16,1,16);
        setLED(ui->labelset17,1,16);
        setLED(ui->labelset18,1,16);
    }
    else if(ui->model->currentIndex()==6){

        ui->send1->setEnabled(false);
        ui->send2->setEnabled(false);
        ui->send3->setEnabled(false);
        ui->send4->setEnabled(false);
        ui->send5->setEnabled(false);
        ui->send6->setEnabled(false);
        ui->send10->setEnabled(false);
        ui->send11->setEnabled(false);
        ui->send12->setEnabled(false);
        ui->send13->setEnabled(false);
        ui->send14->setEnabled(false);
        ui->send15->setEnabled(false);
        ui->send16->setEnabled(true);
        ui->send17->setEnabled(true);
        ui->send18->setEnabled(true);


        setLED(ui->labelset1,1,16);
        setLED(ui->labelset2,1,16);
        setLED(ui->labelset3,1,16);
        setLED(ui->labelset4,1,16);
        setLED(ui->labelset5,1,16);
        setLED(ui->labelset6,1,16);
        setLED(ui->labelset7,3,16);
        setLED(ui->labelset8,3,16);
        setLED(ui->labelset9,3,16);
        setLED(ui->labelset10,1,16);
        setLED(ui->labelset11,1,16);
        setLED(ui->labelset12,1,16);
        setLED(ui->labelset13,1,16);
        setLED(ui->labelset14,1,16);
        setLED(ui->labelset15,1,16);
        setLED(ui->labelset16,2,16);
        setLED(ui->labelset17,2,16);
        setLED(ui->labelset18,2,16);
    }
    else if(ui->model->currentIndex()==7){
        if(int(v30.back())==1){
           setLED(ui->checklabel,2,16);
        }
        else{
        setLED(ui->checklabel,3,16);
        }

        ui->send1->setEnabled(true);
        ui->send2->setEnabled(false);
        ui->send3->setEnabled(false);
        ui->send4->setEnabled(true);
        ui->send5->setEnabled(false);
        ui->send6->setEnabled(false);
        ui->send10->setEnabled(false);
        ui->send11->setEnabled(false);
        ui->send12->setEnabled(false);
        ui->send13->setEnabled(false);
        ui->send14->setEnabled(false);
        ui->send15->setEnabled(false);
        ui->send16->setEnabled(false);
        ui->send17->setEnabled(false);
        ui->send18->setEnabled(false);

        setLED(ui->labelset1,2,16);
        setLED(ui->labelset2,1,16);
        setLED(ui->labelset3,1,16);
        setLED(ui->labelset4,2,16);
        setLED(ui->labelset5,1,16);
        setLED(ui->labelset6,1,16);
        setLED(ui->labelset7,3,16);
        setLED(ui->labelset8,3,16);
        setLED(ui->labelset9,3,16);
        setLED(ui->labelset10,1,16);
        setLED(ui->labelset11,1,16);
        setLED(ui->labelset12,1,16);
        setLED(ui->labelset13,1,16);
        setLED(ui->labelset14,1,16);
        setLED(ui->labelset15,1,16);
        setLED(ui->labelset16,1,16);
        setLED(ui->labelset17,1,16);
        setLED(ui->labelset18,1,16);

    }

}

void MainWindow::on_pushButton_clicked()
{
    plt1= new myscreen1;//数据画图屏幕

    plt2= new myscreen2;//采集数据显示屏幕

    plt3 = new myscreen3;//输出数据显示屏幕

    plt4 = new myscreen4;//发动机飞机显示屏幕
    //ctest=5;

   // connect(this, SIGNAL(fplot()),plt2,SLOT(replot()));

    QDesktopWidget *desktop = QApplication::desktop();
    plt1->setGeometry(desktop->screenGeometry(2));
    plt1->show();
    plt2->setGeometry(desktop->screenGeometry(4));
    plt2->show();
    plt3->setGeometry(desktop->screenGeometry(1));
    plt3->show();

//    plt2->setGeometry(desktop->screenGeometry(1));
//    plt2->show();

//    plt3->setGeometry(desktop->screenGeometry(1));
//    plt3->show();

        plt4->setGeometry(desktop->screenGeometry(3));
        plt4->show();
}

void MainWindow::on_stop_listen_button_clicked()
{
    tcpServer->disconnect();
    global::listen_signal=0;
    setLED(ui->label_led,1,16);
}
void MainWindow::on_pushButton_set_clicked()
{
       global::c0= ui->send5->value();
       global::c1= ui->send6->value();
      // global::c3二通比
       global::c4= ui->send10->value();
       global::c10=ui->send2->value();
       global::c11=ui->send4->value();
       global::model_n= ui->model->currentIndex();
       global::c13=ui->send1->value();
       global::c12=ui->send3->value();
       global::c7=ui->send11->value();
       global::c20 = ui->send12->value();
       global::c17=ui->send13->value();
       global::c18=ui->send14->value();
       global::c19=ui->send15->value();
       global::c14=ui->send16->value();
       global::c15=ui->send17->value();
       global::c16=ui->send18->value();

       //备用输入
       global::kp           =ui->backupSend1->value();
       global::ki           =ui->backupSend2->value();
       global::kd           =ui->backupSend3->value();
       global::integral_top =ui->backupSend4->value();
       global::integral_down=ui->backupSend5->value();
       global::I1           =ui->backupSend6->value();
       global::Q            =ui->backupSend7->value();
       global::R            =ui->backupSend8->value();




       //不合理提
//       if((global::c0>10)){
//       global::c0=0;
//       QMessageBox::warning(this, "提示", "设定值不合理！");
//       }

}
void MainWindow::on_pushButton_send_clicked()//发送
{
    QList <QTcpSocket *> socketList = tcpServer->findChildren<QTcpSocket *>();
    //qDebug() << "tcpSocket 数量：" << socketList.count() << endl;
    if (socketList.count() == 0) {
        return;
    }
    foreach (QTcpSocket *tmpTcpSocket, socketList) {

        // 服务端向每个客户端发送消息
        char sendbuf[1024];
        sendbuf[0]='\0';
        char tmp[1024];
        tmp[0]='\0';
        double data[28]={0};
        data[0]=global::c0;//燃油计量伺服阀电压输入(V)
        data[1]=global::c1;//TCM关断控制伺服阀电压输入(V)
        data[2]=global::c2;//关断控制比例阀电压输入(V)
        data[3]=global::c3;//二通比例调速阀电压输入(V)
        data[4]=global::c4;//VSV伺服阀放大板电压输入(V)
        data[5]=global::c5;//超转保护泄油阀(IO）
        data[6]=global::c6;//电动关断先导阀(IO)
        data[7]=global::c7;//发动机N1转速设定
        data[8]=global::c12;//TCM模式输出燃油流量设定
        data[9]=global::c13;//输出燃油流量设定
        data[10]=global::model_n;//模式判断
        data[11]=global::c10;//燃油阀PID输入
        data[12]=global::c11;//VSVpid设定
        data[13]=global::c14;//飞机飞行高度设定
        data[14]=global::c15;//飞机飞行速度设定
        data[15]=global::c16;//飞机飞行轨迹设定
        data[16]=global::c17;//发动机工作高度设定
        data[17]=global::c18;//发动机工作MA设定
        data[18]=global::c19;//发动机工作温度设定
        data[19]=global::c20;//发动机输出推力设定
        data[20]=global::kp;//kp
        data[21]=global::ki;//ki
        data[22]=global::kd;//kd
        data[23]=global::integral_top ;//integral_top
        data[24]=global::integral_down;//integral_down
        data[25]=global::I1           ;//I1
        data[26]=global::Q;//Q
        data[27]=global::R;//R


        for (int i=0;i<27;i++) {
            sprintf(tmp,"%.4f ",(double)data[i]);
            sprintf(sendbuf,"%.*s%.*s",sizeof(sendbuf),sendbuf,sizeof(tmp),tmp);
            }
            sprintf(tmp,"%.4f",(double)data[27]);
            sprintf(sendbuf,"%.*s%.*s",sizeof(sendbuf),sendbuf,sizeof(tmp),tmp);

        tmpTcpSocket->write(sendbuf);
    }
}


//发送时序曲线要用定时器
void MainWindow::on_pushButton_timerstart_clicked()
{
    timersend->start();
}

void MainWindow::on_pushButton_timerstop_clicked()
{
    timersend->stop();
    global::sendcount=0;
}
void MainWindow::textsend(float &a,int &j,QVector<double>vtime, QVector<double> vdata){

    if(((global::sendcount/1000)==vtime[j])&&j<((vdata.size())-1)){
        a=vdata[j];
        j++;
    }
    else if((global::sendcount/1000)>=vtime[j]){
       a=vdata[vdata.size()-1];
    }
    else if(((global::sendcount/1000)<vtime[0])){
        a=0;
    }else{
        a=vdata[j-1];
    }
}

//读取时序
void MainWindow::on_pushButton_2_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "open", "../", "txt(*.txt)");
    if (!path.isEmpty())
    {
        QFile file(path);
        bool isok = file.open(QIODevice::ReadOnly);
        if (isok)
        {
            QTextStream filestream(&file);
            QString str;
            filestream.setCodec("UTF-8");//防止读取数据中文乱码

            while (filestream.atEnd() == false)
            {
                str = filestream.readLine();
                QStringList a = str.split(" ");
                t0.push_back(a[0].toDouble());
                d0.push_back(a[1].toDouble());
            }
        }
        else
        {
            QMessageBox::warning(this, "提示", "文件路径为空 ！");
        }
        file.close();

        }
        setLED(ui->timeled1,2,16);


}

void MainWindow::on_pushButton_3_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "open", "../", "txt(*.txt)");
    if (!path.isEmpty())
    {
        QFile file(path);
        bool isok = file.open(QIODevice::ReadOnly);
        if (isok)
        {
            QTextStream filestream(&file);
            QString str;
            filestream.setCodec("UTF-8");//防止读取数据中文乱码

            while (filestream.atEnd() == false)
            {
                str = filestream.readLine();
                QStringList a = str.split(" ");
                t1.push_back(a[0].toDouble());
                d1.push_back(a[1].toDouble());
            }
        }
        else
        {
            QMessageBox::warning(this, "提示", "文件路径为空 ！");
        }
        file.close();

        }
     setLED(ui->timeled2,2,16);
}

void MainWindow::on_pushButton_4_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "open", "../", "txt(*.txt)");
    if (!path.isEmpty())
    {
        QFile file(path);
        bool isok = file.open(QIODevice::ReadOnly);
        if (isok)
        {
            QTextStream filestream(&file);
            QString str;
            filestream.setCodec("UTF-8");//防止读取数据中文乱码

            while (filestream.atEnd() == false)
            {
                str = filestream.readLine();
                QStringList a = str.split(" ");
                t2.push_back(a[0].toDouble());
                d2.push_back(a[1].toDouble());
            }
        }
        else
        {
            QMessageBox::warning(this, "提示", "文件路径为空 ！");
        }
        file.close();

        }
     setLED(ui->timeled3,2,16);
}

void MainWindow::on_pushButton_5_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "open", "../", "txt(*.txt)");
    if (!path.isEmpty())
    {
        QFile file(path);
        bool isok = file.open(QIODevice::ReadOnly);
        if (isok)
        {
            QTextStream filestream(&file);
            QString str;
            filestream.setCodec("UTF-8");//防止读取数据中文乱码

            while (filestream.atEnd() == false)
            {
                str = filestream.readLine();
                QStringList a = str.split(" ");
                t3.push_back(a[0].toDouble());
                d3.push_back(a[1].toDouble());
            }
        }
        else
        {
            QMessageBox::warning(this, "提示", "文件路径为空 ！");
        }
        file.close();

        }
     setLED(ui->timeled4,2,16);
}

void MainWindow::on_pushButton_6_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "open", "../", "txt(*.txt)");
    if (!path.isEmpty())
    {
        QFile file(path);
        bool isok = file.open(QIODevice::ReadOnly);
        if (isok)
        {
            QTextStream filestream(&file);
            QString str;
            filestream.setCodec("UTF-8");//防止读取数据中文乱码

            while (filestream.atEnd() == false)
            {
                str = filestream.readLine();
                QStringList a = str.split(" ");
                t4.push_back(a[0].toDouble());
                d4.push_back(a[1].toDouble());
            }
        }
        else
        {
            QMessageBox::warning(this, "提示", "文件路径为空 ！");
        }
        file.close();

        }
     setLED(ui->timeled5,2,16);
}

void MainWindow::on_pushButton_7_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "open", "../", "txt(*.txt)");
    if (!path.isEmpty())
    {
        QFile file(path);
        bool isok = file.open(QIODevice::ReadOnly);
        if (isok)
        {
            QTextStream filestream(&file);
            QString str;
            filestream.setCodec("UTF-8");//防止读取数据中文乱码

            while (filestream.atEnd() == false)
            {
                str = filestream.readLine();
                QStringList a = str.split(" ");
                t5.push_back(a[0].toDouble());
                d5.push_back(a[1].toDouble());
            }
        }
        else
        {
            QMessageBox::warning(this, "提示", "文件路径为空 ！");
        }
        file.close();

        }
     setLED(ui->timeled6,2,16);
}

void MainWindow::on_pushButton_11_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "open", "../", "txt(*.txt)");
    if (!path.isEmpty())
    {
        QFile file(path);
        bool isok = file.open(QIODevice::ReadOnly);
        if (isok)
        {
            QTextStream filestream(&file);
            QString str;
            filestream.setCodec("UTF-8");//防止读取数据中文乱码

            while (filestream.atEnd() == false)
            {
                str = filestream.readLine();
                QStringList a = str.split(" ");
                t9.push_back(a[0].toDouble());
                d9.push_back(a[1].toDouble());
            }
        }
        else
        {
            QMessageBox::warning(this, "提示", "文件路径为空 ！");
        }
        file.close();

        }
     setLED(ui->timeled10,2,16);
}

void MainWindow::on_pushButton_12_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "open", "../", "txt(*.txt)");
    if (!path.isEmpty())
    {
        QFile file(path);
        bool isok = file.open(QIODevice::ReadOnly);
        if (isok)
        {
            QTextStream filestream(&file);
            QString str;
            filestream.setCodec("UTF-8");//防止读取数据中文乱码

            while (filestream.atEnd() == false)
            {
                str = filestream.readLine();
                QStringList a = str.split(" ");
                t10.push_back(a[0].toDouble());
                d10.push_back(a[1].toDouble());
            }
        }
        else
        {
            QMessageBox::warning(this, "提示", "文件路径为空 ！");
        }
        file.close();

        }
     setLED(ui->timeled11,2,16);
}

void MainWindow::on_pushButton_13_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "open", "../", "txt(*.txt)");
    if (!path.isEmpty())
    {
        QFile file(path);
        bool isok = file.open(QIODevice::ReadOnly);
        if (isok)
        {
            QTextStream filestream(&file);
            QString str;
            filestream.setCodec("UTF-8");//防止读取数据中文乱码

            while (filestream.atEnd() == false)
            {
                str = filestream.readLine();
                QStringList a = str.split(" ");
                t11.push_back(a[0].toDouble());
                d11.push_back(a[1].toDouble());
            }
        }
        else
        {
            QMessageBox::warning(this, "提示", "文件路径为空 ！");
        }
        file.close();

        }
     setLED(ui->timeled12,2,16);
}

void MainWindow::on_pushButton_14_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "open", "../", "txt(*.txt)");
    if (!path.isEmpty())
    {
        QFile file(path);
        bool isok = file.open(QIODevice::ReadOnly);
        if (isok)
        {
            QTextStream filestream(&file);
            QString str;
            filestream.setCodec("UTF-8");//防止读取数据中文乱码

            while (filestream.atEnd() == false)
            {
                str = filestream.readLine();
                QStringList a = str.split(" ");
                t12.push_back(a[0].toDouble());
                d12.push_back(a[1].toDouble());
            }
        }
        else
        {
            QMessageBox::warning(this, "提示", "文件路径为空 ！");
        }
        file.close();

        }
     setLED(ui->timeled13,2,16);
}

void MainWindow::on_pushButton_15_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "open", "../", "txt(*.txt)");
    if (!path.isEmpty())
    {
        QFile file(path);
        bool isok = file.open(QIODevice::ReadOnly);
        if (isok)
        {
            QTextStream filestream(&file);
            QString str;
            filestream.setCodec("UTF-8");//防止读取数据中文乱码

            while (filestream.atEnd() == false)
            {
                str = filestream.readLine();
                QStringList a = str.split(" ");
                t13.push_back(a[0].toDouble());
                d13.push_back(a[1].toDouble());
            }
        }
        else
        {
            QMessageBox::warning(this, "提示", "文件路径为空 ！");
        }
        file.close();

        }
     setLED(ui->timeled14,2,16);
}

void MainWindow::on_pushButton_16_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "open", "../", "txt(*.txt)");
    if (!path.isEmpty())
    {
        QFile file(path);
        bool isok = file.open(QIODevice::ReadOnly);
        if (isok)
        {
            QTextStream filestream(&file);
            QString str;
            filestream.setCodec("UTF-8");//防止读取数据中文乱码

            while (filestream.atEnd() == false)
            {
                str = filestream.readLine();
                QStringList a = str.split(" ");
                t14.push_back(a[0].toDouble());
                d14.push_back(a[1].toDouble());
            }
        }
        else
        {
            QMessageBox::warning(this, "提示", "文件路径为空 ！");
        }
        file.close();

        }
     setLED(ui->timeled15,2,16);
}

void MainWindow::on_pushButton_17_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "open", "../", "txt(*.txt)");
    if (!path.isEmpty())
    {
        QFile file(path);
        bool isok = file.open(QIODevice::ReadOnly);
        if (isok)
        {
            QTextStream filestream(&file);
            QString str;
            filestream.setCodec("UTF-8");//防止读取数据中文乱码

            while (filestream.atEnd() == false)
            {
                str = filestream.readLine();
                QStringList a = str.split(" ");
                t15.push_back(a[0].toDouble());
                d15.push_back(a[1].toDouble());
            }
        }
        else
        {
            QMessageBox::warning(this, "提示", "文件路径为空 ！");
        }
        file.close();

        }
     setLED(ui->timeled16,2,16);
}

void MainWindow::on_pushButton_18_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "open", "../", "txt(*.txt)");
    if (!path.isEmpty())
    {
        QFile file(path);
        bool isok = file.open(QIODevice::ReadOnly);
        if (isok)
        {
            QTextStream filestream(&file);
            QString str;
            filestream.setCodec("UTF-8");//防止读取数据中文乱码

            while (filestream.atEnd() == false)
            {
                str = filestream.readLine();
                QStringList a = str.split(" ");
                t16.push_back(a[0].toDouble());
                d16.push_back(a[1].toDouble());
            }
        }
        else
        {
            QMessageBox::warning(this, "提示", "文件路径为空 ！");
        }
        file.close();

        }
     setLED(ui->timeled17,2,16);
}

void MainWindow::on_pushButton_19_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "open", "../", "txt(*.txt)");
    if (!path.isEmpty())
    {
        QFile file(path);
        bool isok = file.open(QIODevice::ReadOnly);
        if (isok)
        {
            QTextStream filestream(&file);
            QString str;
            filestream.setCodec("UTF-8");//防止读取数据中文乱码

            while (filestream.atEnd() == false)
            {
                str = filestream.readLine();
                QStringList a = str.split(" ");
                t17.push_back(a[0].toDouble());
                d17.push_back(a[1].toDouble());
            }
        }
        else
        {
            QMessageBox::warning(this, "提示", "文件路径为空 ！");
        }
        file.close();

        }
     setLED(ui->timeled18,2,16);
}

void MainWindow::on_pushButton_21_clicked()
{
    t0.clear();
    d0.clear();
    setLED(ui->timeled1,0,16);
}

void MainWindow::on_pushButton_22_clicked()
{
    t1.clear();
    d1.clear();
    setLED(ui->timeled2,0,16);
}

void MainWindow::on_pushButton_23_clicked()
{
    t2.clear();
    d2.clear();
    setLED(ui->timeled3,0,16);
}

void MainWindow::on_pushButton_24_clicked()
{
    t3.clear();
    d3.clear();
    setLED(ui->timeled4,0,16);
}

void MainWindow::on_pushButton_25_clicked()
{
    t4.clear();
    d4.clear();
    setLED(ui->timeled5,0,16);
}

void MainWindow::on_pushButton_26_clicked()
{
    t5.clear();
    d5.clear();
    setLED(ui->timeled6,0,16);
}


void MainWindow::on_pushButton_30_clicked()
{
    t9.clear();
    d9.clear();
    setLED(ui->timeled10,0,16);
}

void MainWindow::on_pushButton_31_clicked()
{
    t10.clear();
    d10.clear();
    setLED(ui->timeled11,0,16);
}

void MainWindow::on_pushButton_32_clicked()
{
    t11.clear();
    d11.clear();
    setLED(ui->timeled12,0,16);
}

void MainWindow::on_pushButton_33_clicked()
{
    t12.clear();
    d12.clear();
    setLED(ui->timeled13,0,16);
}

void MainWindow::on_pushButton_34_clicked()
{
    t13.clear();
    d13.clear();
    setLED(ui->timeled14,0,16);
}

void MainWindow::on_pushButton_35_clicked()
{
    t14.clear();
    d14.clear();
    setLED(ui->timeled15,0,16);
}

void MainWindow::on_pushButton_36_clicked()
{
    t15.clear();
    d15.clear();
    setLED(ui->timeled16,0,16);
}

void MainWindow::on_pushButton_37_clicked()
{
    t16.clear();
    d16.clear();
    setLED(ui->timeled17,0,16);
}

void MainWindow::on_pushButton_38_clicked()
{
    t17.clear();
    d17.clear();
    setLED(ui->timeled18,0,16);
}

//恢复安全值
void MainWindow::on_pushButton_20_clicked()
{

   ui->send5->setValue(0);
   ui->send6->setValue(0);
   ui->send10->setValue(-1.5);
   ui->send2->setValue(0);
   ui->send4->setValue(0);
   ui->send1->setValue(0);
   ui->send3->setValue(0);
   ui->send11->setValue(0);
   ui->send12->setValue(0);
   ui->send13->setValue(0);
   ui->send14->setValue(0);
   ui->send15->setValue(0);
   ui->send16->setValue(0);
   ui->send17->setValue(0);
   ui->send18->setValue(0);
   ui->model->setCurrentIndex(0);
   global::c2=-5;
   global::c5=0;
   global::c6=0;
   ui->ShutoffControlInBox->setChecked(false);
   ui->OverRotatingBox->setChecked(false);
   ui->ShutoffPilotBox->setChecked(false);
   on_pushButton_set_clicked();
   on_pushButton_send_clicked();

     QMessageBox::warning(this, "提示", "全部恢复为0！");
}

void MainWindow::on_pushButton_39_clicked()
{
    if(!m_bConnectState){
     setLED(ui->label_led_2,3,16);
     slotSshConnect();
    }
    else if(m_bConnectState){
     setLED(ui->label_led_2,2,16);
    slotSshSendCmd();
    }

}
void MainWindow::createConnection()
{
    QString strIp = "192.168.1.150";
    QString strUser = "root";
    QString strPwd = "root";
    m_sshSocket = new CConnectionForSshClient(strIp,22,strPwd,strUser);
    m_sshSocket->init();
    connect(m_sshSocket,SIGNAL(sigConnectStateChanged(bool,QString,int)),
            this,SLOT(slotConnectStateChanged(bool,QString,int)));
    connect(m_sshSocket,SIGNAL(sigDataArrived(QString ,QString , int )),
            this,SLOT(slotDataArrived(QString ,QString , int )));
    connect(this,SIGNAL(sigSend(QString)),m_sshSocket,SLOT(slotSend(QString)));
    connect(this,SIGNAL(sigDisconnected()),m_sshSocket,SLOT(slotDisconnected()));

}

void MainWindow::disConnection()
{
    emit sigDisconnected();
}


void MainWindow::slotSshConnect()
{
    if(!m_bConnectState){
        createConnection();  //发起连接
    }   
}

void MainWindow::slotSshSendCmd()
{
    if(m_bConnectState){
        QString strCmd ="cd home";
        strCmd += "\n"; //添加回车
        emit sigSend(strCmd);
    }
    if(m_bConnectState){
        QString strCmd ="./newRanYouMoniter+udp_enginefuel_0407";
        strCmd += "\n"; //添加回车
        emit sigSend(strCmd);
    }

}


void MainWindow::slotConnectStateChanged(bool bState, QString strIp, int nPort)
{
    Q_UNUSED(strIp)
    Q_UNUSED(nPort)

    m_bConnectState = bState;
    if(m_bConnectState)
        ui->pushButton_39->setText("启动ARM");
    else if(!m_bConnectState)
        ui->pushButton_39->setText("连接");

}

void MainWindow::slotDataArrived(QString strMsg, QString strIp, int nPort)
{
    Q_UNUSED(strIp)
    Q_UNUSED(nPort)

}

void MainWindow::on_pushButton_40_clicked()
{
    emit sigDisconnected();//断开连接
    m_bConnectState = false;
     setLED(ui->label_led_2,1,16);
    ui->pushButton_39->setText("连接");
    qDebug()<<"stop";
}



void MainWindow::on_ShutoffControlInBox_stateChanged(int arg1)
{
    if(arg1==2){
        global::c2=4.7;
    }
    else{
        global::c2=-5;
    }
}

void MainWindow::on_OverRotatingBox_stateChanged(int arg1)
{
    if(arg1==2){
        global::c5=1;
    }
    else{
        global::c5=0;
    }
}

void MainWindow::on_ShutoffPilotBox_stateChanged(int arg1)
{
    if(arg1==2){
        global::c6=1;
    }
    else{
        global::c6=0;
    }
}

void MainWindow::on_check0_stateChanged(int arg1)
{
    if(arg1==2){
        global::p0=1;
        ui->cplot1->graph()->setVisible(true);
    }
    else{
        global::p0=0;
        ui->cplot1->graph()->setVisible(false);
    }
}

void MainWindow::on_check1_stateChanged(int arg1)
{
    if(arg1==2){
        global::p1=1;
        if(global::p1==1){
        ui->cplot2->graph(0)->setVisible(true);
        }

    }
    else{
        global::p1=0;
        ui->cplot2->graph(0)->setVisible(false);
    }
}

void MainWindow::on_check1_2_stateChanged(int arg1)
{
    if(arg1==2){
        global::p2=1;
        if(global::p2==1){
        ui->cplot2->graph(1)->setVisible(true);
        }
    }
    else{
        global::p2=0;
        ui->cplot2->graph(1)->setVisible(false);
    }
}

void MainWindow::on_check1_3_stateChanged(int arg1)
{
    if(arg1==2){
        global::p3=1;
        if(global::p3==1){
        ui->cplot2->graph(2)->setVisible(true);
        }
    }
    else{
        global::p3=0;
        ui->cplot2->graph(2)->setVisible(false);
    }
}

void MainWindow::on_check2_6_stateChanged(int arg1)
{
    if(arg1==2){
        global::p4=1;
        if(global::p4==1){
        ui->cplot5->graph(0)->setVisible(true);
        }

    }
    else{
        global::p4=0;
        ui->cplot5->graph(0)->setVisible(false);
    }
}

void MainWindow::on_check2_8_stateChanged(int arg1)
{
    if(arg1==2){
        global::p5=1;
        if(global::p5==1){
        ui->cplot5->graph(1)->setVisible(true);
        }

    }
    else{
        global::p5=0;
        ui->cplot5->graph(1)->setVisible(false);
    }
}

void MainWindow::on_check2_5_stateChanged(int arg1)
{
    if(arg1==2){
        global::p6=1;
        if(global::p6==1){
        ui->cplot5->graph(2)->setVisible(true);
        }

    }
    else{
        global::p6=0;
        ui->cplot5->graph(2)->setVisible(false);
    }
}

void MainWindow::on_check2_7_stateChanged(int arg1)
{
    if(arg1==2){
        global::p7=1;
        if(global::p7==1){
        ui->cplot5->graph(3)->setVisible(true);
        }

    }
    else{
        global::p7=0;
        ui->cplot5->graph(3)->setVisible(false);
    }
}

void MainWindow::on_check3_21_stateChanged(int arg1)
{
    if(arg1==2){
        global::p8=1;
        if(global::p8==1){
        ui->cplot3->graph(0)->setVisible(true);
        }

    }
    else{
        global::p8=0;
        ui->cplot3->graph(0)->setVisible(false);
    }
}

void MainWindow::on_check3_18_stateChanged(int arg1)
{
    if(arg1==2){
        global::p9=1;
        if(global::p9==1){
        ui->cplot3->graph(1)->setVisible(true);
        }

    }
    else{
        global::p9=0;
        ui->cplot3->graph(1)->setVisible(false);
    }
}

void MainWindow::on_check3_15_stateChanged(int arg1)
{
    if(arg1==2){
        global::p10=1;
        if(global::p10==1){
        ui->cplot3->graph(2)->setVisible(true);
        }

    }
    else{
        global::p10=0;
        ui->cplot3->graph(2)->setVisible(false);
    }
}

void MainWindow::on_check3_17_stateChanged(int arg1)
{
    if(arg1==2){
        global::p11=1;
        if(global::p11==1){
        ui->cplot3->graph(3)->setVisible(true);
        }

    }
    else{
        global::p11=0;
        ui->cplot3->graph(3)->setVisible(false);
    }
}

void MainWindow::on_check3_19_stateChanged(int arg1)
{
    if(arg1==2){
        global::p12=1;
        if(global::p12==1){
        ui->cplot3->graph(4)->setVisible(true);
        }

    }
    else{
        global::p12=0;
        ui->cplot3->graph(4)->setVisible(false);
    }
}


void MainWindow::on_check3_16_stateChanged(int arg1)
{
    if(arg1==2){
        global::p13=1;
        if(global::p13==1){
        ui->cplot3->graph(5)->setVisible(true);
        }

    }
    else{
        global::p13=0;
        ui->cplot3->graph(5)->setVisible(false);
    }
}

void MainWindow::on_check3_20_stateChanged(int arg1)
{
    if(arg1==2){
        global::p14=1;
        if(global::p14==1){
        ui->cplot3->graph(6)->setVisible(true);
        }

    }
    else{
        global::p14=0;
        ui->cplot3->graph(6)->setVisible(false);
    }
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1==2){
        global::p15=1;
        if(global::p15==1){
        ui->cplot4->graph(0)->setVisible(true);
        }

    }
    else{
        global::p15=0;
        ui->cplot4->graph(0)->setVisible(false);
    }
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    if(arg1==2){
        global::p16=1;
        if(global::p16==1){
        ui->cplot4->graph(1)->setVisible(true);
        }

    }
    else{
        global::p16=0;
        ui->cplot4->graph(1)->setVisible(false);
    }
}

void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
    if(arg1==2){
        global::p17=1;
        if(global::p17==1){
        ui->cplot4->graph(2)->setVisible(true);
        }

    }
    else{
        global::p17=0;
        ui->cplot4->graph(2)->setVisible(false);
    }
}

void MainWindow::on_checkBox_4_stateChanged(int arg1)
{
    if(arg1==2){
        global::p18=1;
        if(global::p18==1){
        ui->cplot4->graph(3)->setVisible(true);
        }

    }
    else{
        global::p18=0;
        ui->cplot4->graph(3)->setVisible(false);
    }
}

void MainWindow::on_checkBox_5_stateChanged(int arg1)
{
    if(arg1==2){
        global::p19=1;
        if(global::p19==1){
        ui->cplot6->graph(0)->setVisible(true);
        }

    }
    else{
        global::p19=0;
        ui->cplot6->graph(0)->setVisible(false);
    }
}

void MainWindow::on_checkBox_6_stateChanged(int arg1)
{
    if(arg1==2){
        global::p20=1;
        if(global::p20==1){
        ui->cplot6->graph(1)->setVisible(true);
        }

    }
    else{
        global::p20=0;
        ui->cplot6->graph(1)->setVisible(false);
    }
}
