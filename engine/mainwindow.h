#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <stdlib.h>
#include <QWidget>
#include <QMainWindow>
#include <qcustomplot.h>
#include <model_thread.h>
#include <QTcpServer>
#include <QTcpSocket>
#include<QTimer>
#include<QTextStream>
#include<QMessageBox>
#include<QFileDialog>
#include<QFile>
#include<QUdpSocket>

#include"global.h"
#include"sshWidget.h"
#include"CConnectionForSshClient.h"
namespace Ui {
class MainWindow;
}
extern void controller_step(real32_T arg_LP);
extern void controller_initialize();
extern void controller_terminate();
extern real_T model_step(real32_T arg_Wf, real32_T arg_VSV);
extern void model_initialize();
extern void model_terminate();
extern float ctest;
extern  QVector<double> v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32,v33,v34,v35,v36,v37,v38,v39,v40,v41,v42,v43,v44,v45,v46,v47,v48,v49,v50;
extern  QVector<double>  v51,v52,v53,v54,v55,v56,v57,v58,v59,v60,v61,v62,v63,v64,v65,v66,v67,v68,v69,v70,v71,v72,v73,v74,v75,v76,v77,v78,v79,v80,v81,v82,v83,v84,v85;

//时序曲线容器 t:time d:data
extern QVector<double> t0,d0,t1,d1,t2,d2,t3,d3,t4,d4,t5,d5,t6,d6,t7,d7,t8,d8,t9,d9,t10,d10,t11,d11,t12,d12,t13,d13,t14,d14,t15,d15,t16,d16,t17,d17;
//extern void JT9D_Model_Dyn_old1_initialize(void);
//extern real_T JT9D_Model_Dyn_old1_step(real_T,real_T&);
//extern void JT9D_Model_Dyn_old1_terminate(void);
struct engine_data_type{
    double s_nl_actual;
    double s_nl_aim;
    double s_fuel_aim;
    double s_fuel_actual;
    double s_time_fuel;
    double s_fuel_voltage;
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setplot();
    ~MainWindow();
    ModelThread *j;  //创建发动机模型的子线程对象

    QTimer *timer;

    QTimer *timersend;//发送数据定时器

    QTimer *timerplot;

    JT9D_Model_Dyn_old1 JT9D_Model_Dyn_old1_OBJ;
    engine_data_type engine_data;
    //QVector<double> v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32,v33;
    QUdpSocket *udpSocket;
    QFile *file_1;
    QString alldata;



    void setLED(QLabel* label, int color, int size);

    //运行时序曲线函数
    void textsend(float &a,int &j,QVector<double>vtime,QVector<double>vdata);



    float fuel_control(float aim_fuel);
private slots:

    void slotSshConnect();
    void slotSshSendCmd();
    void slotConnectStateChanged(bool bState,QString strIp,int nPort);
    void slotDataArrived(QString strMsg,QString strIp, int nPort);

    void receiveMessages();
    void mStateChanged(QAbstractSocket::SocketState);
    void mNewConnetion();


    void on_start_listen_button_clicked();


    void led();

   void udp_readyread();

   //画图
   void replot();



   void on_pushButton_clicked();

   void on_stop_listen_button_clicked();

   void on_pushButton_send_clicked();

   void on_pushButton_set_clicked();

   void on_pushButton_timerstart_clicked();

   void on_pushButton_timerstop_clicked();

   void on_pushButton_2_clicked();

   void on_pushButton_3_clicked();

   void on_pushButton_4_clicked();

   void on_pushButton_5_clicked();

   void on_pushButton_6_clicked();

   void on_pushButton_7_clicked();

   void on_pushButton_11_clicked();

   void on_pushButton_12_clicked();

   void on_pushButton_13_clicked();

   void on_pushButton_14_clicked();

   void on_pushButton_15_clicked();

   void on_pushButton_16_clicked();

   void on_pushButton_17_clicked();

   void on_pushButton_18_clicked();

   void on_pushButton_19_clicked();

   void on_pushButton_21_clicked();

   void on_pushButton_22_clicked();

   void on_pushButton_23_clicked();

   void on_pushButton_24_clicked();

   void on_pushButton_25_clicked();

   void on_pushButton_26_clicked();

   void on_pushButton_30_clicked();

   void on_pushButton_31_clicked();

   void on_pushButton_32_clicked();

   void on_pushButton_33_clicked();

   void on_pushButton_34_clicked();

   void on_pushButton_35_clicked();

   void on_pushButton_36_clicked();

   void on_pushButton_37_clicked();

   void on_pushButton_38_clicked();


   void on_pushButton_20_clicked();

   void on_pushButton_39_clicked();

   void on_pushButton_40_clicked();


   void on_check0_stateChanged(int arg1);

   void on_check1_stateChanged(int arg1);

   void on_check1_2_stateChanged(int arg1);

   void on_check1_3_stateChanged(int arg1);

   void on_ShutoffControlInBox_stateChanged(int arg1);

   void on_OverRotatingBox_stateChanged(int arg1);

   void on_ShutoffPilotBox_stateChanged(int arg1);

   void on_check2_6_stateChanged(int arg1);

   void on_check2_8_stateChanged(int arg1);

   void on_check2_5_stateChanged(int arg1);

   void on_check2_7_stateChanged(int arg1);

   void on_check3_21_stateChanged(int arg1);

   void on_check3_18_stateChanged(int arg1);

   void on_check3_15_stateChanged(int arg1);

   void on_check3_17_stateChanged(int arg1);

   void on_check3_19_stateChanged(int arg1);

   void on_check3_16_stateChanged(int arg1);

   void on_check3_20_stateChanged(int arg1);

   void on_checkBox_stateChanged(int arg1);

   void on_checkBox_2_stateChanged(int arg1);

   void on_checkBox_3_stateChanged(int arg1);

   void on_checkBox_4_stateChanged(int arg1);

   void on_checkBox_5_stateChanged(int arg1);

   void on_checkBox_6_stateChanged(int arg1);

signals:
  void plot();
  void sigSend(QString strMsg);
  void sigDisconnected();

private:
  void createConnection();
  void disConnection();
    Ui::MainWindow *ui;
     QTcpServer *tcpServer;  //tcp套接字
     bool m_bConnectState;
     CConnectionForSshClient *m_sshSocket;





};

#endif // MAINWINDOW_H
