#ifndef FAR_CONTROLLER_H
#define FAR_CONTROLLER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <signal.h>
#include <string.h>
#include "inc/EM9636.h"
#include "inc/EM9636_Errors.h"
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <iostream>

#include <QMetaType>
#pragma warning(disable:4996)


struct pid_fuel
 {
     F64 SetSpeed;            	//定义设定值
     F64 ActualSpeed;        	//定义实际值
     F64 err;                	//定义偏差值
     F64 err_last;	 //定义上一个偏差值
     F64 err_next;
     F64 Kp, Ki, Kd;           //定义比例、积分、微分系数
     F64 voltage;            	//定义电压值（控制执行器的变量）
     F64 integral;            	//定义积分值
     float umax;
     float umin;				    //饱和值
     float ulimit;
     float I1;
     float deadzone;
     float deadzone_d;
     float changeline;
     float voltage_last;

 };
Q_DECLARE_METATYPE(pid_fuel)
 struct pid_vsv
 {
     F64 SetSpeed;            	//定义设定值
     F64 ActualSpeed;        	//定义实际值
     F64 err;                	//定义偏差值
     F64 err_last;            	//定义上一个偏差值
     F64 Kp, Ki, Kd; //定义比例、积分、微分系数
     F64 voltage;            	//定义电压值（控制执行器的变量）
     F64 integral;            	//定义积分值
     float umax;
     float umin;				    //饱和值
     float ulimit;
     float I1;
     float deadzone;
     float changeline;
 };
extern void ExitExe(int i);

extern void Fuel_PID_init(pid_fuel& pid_fuel);
extern void VSV_PID_init(pid_vsv& pid_vsv);
extern F64 Fuel_PID(pid_fuel& fuel, F64 set, F64 actual);
extern F64 VSV_PID(pid_vsv& pid_vsv, F64 set, F64 actual);
#endif // FAR_CONTROLLER_H
