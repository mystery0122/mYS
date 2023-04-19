#include "myscreen3.h"
#include "ui_myscreen3.h"
float ctest;
myscreen3::myscreen3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myscreen3)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_QuitOnClose,false);
     setFixedSize(1920,1080);
    timer = new QTimer(this);
    timer->setInterval(200);
    connect(timer,&QTimer::timeout,this,[=](){
        if(global::listen_signal==1){setLED(ui->label_listen_led,2,16);}
        else if(global::listen_signal==0){setLED(ui->label_listen_led,1,16);}

        if(global::model_n==0){
            setLED(ui->label_29,2,16);
            setLED(ui->label_30,1,16);
            setLED(ui->label_31,1,16);
            setLED(ui->label_32,1,16);
            setLED(ui->label_33,1,16);
            setLED(ui->label_36,1,16);
            setLED(ui->label_37,1,16);

            setLED(ui->set1,1,16);
            setLED(ui->set2,1,16);
            setLED(ui->set3,1,16);
            setLED(ui->set4,1,16);
            setLED(ui->set5,2,16);
            setLED(ui->set6,2,16);
            setLED(ui->set7,3,16);
            setLED(ui->set8,3,16);
            setLED(ui->set9,3,16);
            setLED(ui->set10,2,16);
            setLED(ui->set11,1,16);
            setLED(ui->set12,1,16);
            setLED(ui->set13,1,16);
            setLED(ui->set14,1,16);
            setLED(ui->set15,1,16);
            setLED(ui->set16,1,16);
            setLED(ui->set17,1,16);
            setLED(ui->set18,1,16);

        }
        else if(global::model_n==1){
            setLED(ui->label_29,1,16);
            setLED(ui->label_30,2,16);
            setLED(ui->label_31,1,16);
            setLED(ui->label_32,1,16);
            setLED(ui->label_33,1,16);
            setLED(ui->label_36,1,16);
            setLED(ui->label_37,1,16);

            setLED(ui->set1,2,16);
            setLED(ui->set2,1,16);
            setLED(ui->set3,1,16);
            setLED(ui->set4,2,16);
            setLED(ui->set5,1,16);
            setLED(ui->set6,1,16);
            setLED(ui->set7,3,16);
            setLED(ui->set8,3,16);
            setLED(ui->set9,3,16);
            setLED(ui->set10,1,16);
            setLED(ui->set11,1,16);
            setLED(ui->set12,1,16);
            setLED(ui->set13,1,16);
            setLED(ui->set14,1,16);
            setLED(ui->set15,1,16);
            setLED(ui->set16,1,16);
            setLED(ui->set17,1,16);
            setLED(ui->set18,1,16);
        }
        else if(global::model_n==2){//TCM model
            setLED(ui->label_29,1,16);
            setLED(ui->label_30,1,16);
            setLED(ui->label_31,2,16);
            setLED(ui->label_32,1,16);
            setLED(ui->label_33,1,16);
            setLED(ui->label_36,1,16);
            setLED(ui->label_37,1,16);

            setLED(ui->set1,1,16);
            setLED(ui->set2,2,16);
            setLED(ui->set3,1,16);
            setLED(ui->set4,2,16);
            setLED(ui->set5,1,16);
            setLED(ui->set6,1,16);
            setLED(ui->set7,3,16);
            setLED(ui->set8,3,16);
            setLED(ui->set9,3,16);
            setLED(ui->set10,1,16);
            setLED(ui->set11,1,16);
            setLED(ui->set12,1,16);
            setLED(ui->set13,1,16);
            setLED(ui->set14,1,16);
            setLED(ui->set15,1,16);
            setLED(ui->set16,1,16);
            setLED(ui->set17,1,16);
            setLED(ui->set18,1,16);
        }

        else if(global::model_n==3){
            setLED(ui->label_29,1,16);
            setLED(ui->label_30,1,16);
            setLED(ui->label_31,1,16);
            setLED(ui->label_32,2,16);
            setLED(ui->label_33,1,16);
            setLED(ui->label_36,1,16);
            setLED(ui->label_37,1,16);

            setLED(ui->set1,2,16);
            setLED(ui->set2,1,16);
            setLED(ui->set3,2,16);
            setLED(ui->set4,2,16);
            setLED(ui->set5,1,16);
            setLED(ui->set6,1,16);
            setLED(ui->set7,3,16);
            setLED(ui->set8,3,16);
            setLED(ui->set9,3,16);
            setLED(ui->set10,1,16);
            setLED(ui->set11,1,16);
            setLED(ui->set12,1,16);
            setLED(ui->set13,1,16);
            setLED(ui->set14,1,16);
            setLED(ui->set15,1,16);
            setLED(ui->set16,1,16);
            setLED(ui->set17,1,16);
            setLED(ui->set18,1,16);
        }
        else if(global::model_n==4){
            setLED(ui->label_29,1,16);
            setLED(ui->label_30,1,16);
            setLED(ui->label_31,1,16);
            setLED(ui->label_32,1,16);
            setLED(ui->label_33,2,16);
            setLED(ui->label_36,1,16);
            setLED(ui->label_37,1,16);

            setLED(ui->set1,1,16);
            setLED(ui->set2,1,16);
            setLED(ui->set3,1,16);
            setLED(ui->set4,1,16);
            setLED(ui->set5,1,16);
            setLED(ui->set6,1,16);
            setLED(ui->set7,3,16);
            setLED(ui->set8,3,16);
            setLED(ui->set9,3,16);
            setLED(ui->set10,1,16);
            setLED(ui->set11,2,16);
            setLED(ui->set12,1,16);
            setLED(ui->set13,2,16);
            setLED(ui->set14,2,16);
            setLED(ui->set15,2,16);
            setLED(ui->set16,1,16);
            setLED(ui->set17,1,16);
            setLED(ui->set18,1,16);
        }
        else if(global::model_n==5){//engine model
            setLED(ui->label_29,1,16);
            setLED(ui->label_30,1,16);
            setLED(ui->label_31,1,16);
            setLED(ui->label_32,1,16);
            setLED(ui->label_33,1,16);
            setLED(ui->label_36,2,16);
            setLED(ui->label_37,1,16);

            setLED(ui->set1,1,16);
            setLED(ui->set2,1,16);
            setLED(ui->set3,1,16);
            setLED(ui->set4,1,16);
            setLED(ui->set5,1,16);
            setLED(ui->set6,1,16);
            setLED(ui->set7,3,16);
            setLED(ui->set8,3,16);
            setLED(ui->set9,3,16);
            setLED(ui->set10,1,16);
            setLED(ui->set11,1,16);
            setLED(ui->set12,2,16);
            setLED(ui->set13,2,16);
            setLED(ui->set14,2,16);
            setLED(ui->set15,2,16);
            setLED(ui->set16,1,16);
            setLED(ui->set17,1,16);
            setLED(ui->set18,1,16);
        }
        else if(global::model_n==6){//engine model
            setLED(ui->label_29,1,16);
            setLED(ui->label_30,1,16);
            setLED(ui->label_31,1,16);
            setLED(ui->label_32,1,16);
            setLED(ui->label_33,1,16);
            setLED(ui->label_36,1,16);
            setLED(ui->label_37,2,16);

            setLED(ui->set1,1,16);
            setLED(ui->set2,1,16);
            setLED(ui->set3,1,16);
            setLED(ui->set4,1,16);
            setLED(ui->set5,1,16);
            setLED(ui->set6,1,16);
            setLED(ui->set7,3,16);
            setLED(ui->set8,3,16);
            setLED(ui->set9,3,16);
            setLED(ui->set10,1,16);
            setLED(ui->set11,1,16);
            setLED(ui->set12,1,16);
            setLED(ui->set13,1,16);
            setLED(ui->set14,1,16);
            setLED(ui->set15,1,16);
            setLED(ui->set16,2,16);
            setLED(ui->set17,2,16);
            setLED(ui->set18,2,16);
        }




        ui->doubleSpinBox_1->setValue(global::c13);
        ui->doubleSpinBox_2->setValue(global::c10);
        ui->doubleSpinBox_3->setValue(global::c12);
        ui->doubleSpinBox_4->setValue(global::c11);
        ui->doubleSpinBox_5->setValue(global::c0);
        ui->doubleSpinBox_6->setValue(global::c1);
        ui->doubleSpinBox_7->setValue(global::c2);
        ui->doubleSpinBox_8->setValue(global::c5);
        ui->doubleSpinBox_9->setValue(global::c6);
        ui->doubleSpinBox_10->setValue(global::c4);
        ui->doubleSpinBox_11->setValue(404);//备用
        ui->doubleSpinBox_12->setValue(global::c7);
        ui->doubleSpinBox_13->setValue(global::c20);//发动机输出推力设定
        ui->doubleSpinBox_14->setValue(global::c17);
        ui->doubleSpinBox_15->setValue(global::c18);
        ui->doubleSpinBox_16->setValue(global::c19);
        ui->doubleSpinBox_17->setValue(global::c14);
        ui->doubleSpinBox_18->setValue(global::c15);
        ui->doubleSpinBox_19->setValue(global::c16);
        ui->doubleSpinBox_20->setValue(404);//备用1
        ui->doubleSpinBox_21->setValue(404);//备用2


    });

    timer->start();


}

//设置信号灯
void myscreen3::setLED(QLabel* label, int color, int size)
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
myscreen3::~myscreen3()
{
    delete ui;
}

