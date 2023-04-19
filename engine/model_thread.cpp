#include "model_thread.h"



extern void controller_step(real32_T arg_LP);
extern void controller_initialize();
extern void controller_terminate();
extern real_T model_step(real32_T arg_Wf, real32_T arg_VSV);
extern void model_initialize();
extern void model_terminate();

//pi
//extern void JT9D_Model_Dyn_old1_initialize(void);
//extern real_T JT9D_Model_Dyn_old1_step(real_T,real_T&);
//extern void JT9D_Model_Dyn_old1_terminate(void);

//extern real32_T far;  //燃油指令
//extern real32_T vsv;
//extern real32_T aim_nl;
//ModelThread::ModealThread(){
//    m_run = 1;
//}

ModelThread::ModelThread(){
    //register my type
    qRegisterMetaType<vsv_data>("vsv_data");
        qRegisterMetaType<fuel_data>("fuel_data");
         qRegisterMetaType<QVariant>("QVariant");

}
void ModelThread::stop(){
    m_run = 0;
}


void ModelThread::run(){
    /*  初始化模型与控制器  */
     //转c代码
   // far = 1.56;
   // vsv = 0;
    model_initialize();
    controller_initialize();
   // JT9D_Model_Dyn_old1_initialize();

    while (1) {
        static double nl_real = 816;
        double vsv_command;
       // double* aim_nl;
        double far_command =  controller_step(nl_real);    //  控制器接收nl实时转速，获取燃油、vsv指令//输出改为燃油far
      //  double far_command = JT9D_Model_Dyn_old1_step(nl_real,nl_real);
        //vsv指令直接与时间挂钩
        if(nl_real < 816)
            vsv_command = 0;
        else if (nl_real >= 816 && nl_real<1500)
        {
            vsv_command = (nl_real - 800) / 700 + 0.5;
        }
        else if (nl_real >= 1500 && nl_real<3500)
        {
            vsv_command = (nl_real - 1500) / 2000 * 1.5 + 1.5;
        }
        nl_real = model_step(far_command,vsv_command);  // 模型接收燃油、vsv指令，改变（输出）nl转速值

        emit getVal(far_command,nl_real);  //给qt主线程发送要显示的值
        msleep(20);
    }
    /*
    QVariant q1,q2;
    q1.setValue(vd);
    q2.setValue(fd);
    emit getfuelsysVal(q1,q2);
    */
    //燃油

            //ExitExe(0);
            return;
        
    
}

ModelThread::~ModelThread(){

    printf("end\n");
    //EM9636_HcStop(pDev);
    //EM9636_DataClose(pDev);//关闭数据连接
   // EM9636_CmdClose(pDev);//关闭命令连接
  //  EM9636_DeviceClose(pDev);//释放设备资源
}
