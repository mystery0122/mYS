#ifndef MODEL_THREAD_H
#define MODEL_THREAD_H

#include <QObject>
#include <QThread>
#include <QMetaType>

#include <QVariant>
extern "C"{
//#include <Windows.h>
#include <stddef.h>
//#include <windows.h>
#include <stdio.h>              /* This ert_main.c example uses printf/fflush */
#include "model.h"                      /* Model's header file */
#include "JT9D_Model_Dyn_old1.h"   /* PI_CONTROLLER header file */
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#include "controller.h"
#include "controller_private.h"
#include "controller_types.h"

extern real32_T far;
extern real_T nl;
extern real32_T vsv;
extern real32_T controller_step(real_T arg_LP);
extern void controller_initialize();
extern void controller_terminate();
extern real_T model_step(real_T arg_Wf, real_T arg_VSV);
extern void model_initialize();

extern void model_terminate();



//void ExitExe(int i);

}

struct vsv_data{
    double vsv_aim,vsv_actual;
    double sysforce;
    double voltage;
};
struct fuel_data{
    double far_aim,far_actual;
    double voltage,timer;
};
Q_DECLARE_METATYPE(vsv_data)
Q_DECLARE_METATYPE(fuel_data)


class ModelThread : public QThread
{
    Q_OBJECT;
public:
    ModelThread();
    ~ModelThread();
    ModelThread(int aim[]){
        qRegisterMetaType<vsv_data>("vsv_data");
            qRegisterMetaType<fuel_data>("fuel_data");
             qRegisterMetaType<QVariant>("QVariant");
             aim_set[0] = aim[0];
              aim_set[1] = aim[1];
               aim_set[2] = aim[2];
                aim_set[3] = aim[3];
                 aim_set[4] = aim[4];

    }
    //void setJoyStick(JoyStick *joystick);
    void run();
    void stop();
    vsv_data vd;
    fuel_data fd;

    int aim_set[5];


private:
    //JoyStick *m_joystick;
    bool m_run = 1;

signals:
    //void getVal();

    void getVal(double val_far,double val_nl);
    void getfuelsysVal(QVariant d1,QVariant d2);
};

#endif // MODEL_THREAD_H
