#include "myscreen2.h"
#include "ui_myscreen2.h"

myscreen2::myscreen2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myscreen2)
{
    ui->setupUi(this);
    setFixedSize(1920,1080);
this->setAttribute(Qt::WA_QuitOnClose,false);

    timer = new QTimer(this);
    timer->setInterval(200);
    connect(timer,&QTimer::timeout,this,[=](){
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

        ui->spinBox_26->setValue(v22.back());
        ui->spinBox_27->setValue(v23.back());
        ui->spinBox_28->setValue(v24.back());
        ui->spinBox_29->setValue(v25.back());
        ui->spinBox_30->setValue(v26.back());
        ui->spinBox31->setValue(v27.back());
        ui->spinBox32->setValue(v28.back());


        ui->spinBox_72->setValue(v1.back());
        ui->spinBox_73->setValue(v2.back());
        ui->spinBox_74->setValue(v3.back());
        ui->spinBox_75->setValue(v4.back());
        ui->spinBox_76->setValue((v20.back())*59.7/829);
        ui->spinBox_77->setValue((v21.back())*27.9/395);
        ui->spinBox_78->setValue((v9.back()-4)/16*100);
        ui->spinBox_79->setValue((v10.back()-4)/16*100);
        ui->spinBox_80->setValue((v11.back()-4)/16*30);
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
//engine
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
    });

    timer->start();


}

myscreen2::~myscreen2()
{
    delete ui;
}
