#include "far_controller.h"



void Fuel_PID_init(pid_fuel& pid_fuel)
{
	printf("PID_init begin \n");
	pid_fuel.SetSpeed = 0.0;	//设定值
	pid_fuel.ActualSpeed = 0.0;//实际值
	pid_fuel.err = 0.0;		//实际误差
	pid_fuel.err_last = 0.0;	//上一次的误差
	pid_fuel.err_next = 0.0;
	pid_fuel.voltage = 0.0;	//输出的电压
	pid_fuel.integral = 0.0;	//积分值
    pid_fuel.umax = 0.5;	//饱和上限
    pid_fuel.deadzone = 1.64;
	pid_fuel.changeline = 0.5;
    pid_fuel.I1 = 1;
    pid_fuel.ulimit = 0.2;
    pid_fuel.Kp = 0.08;
    pid_fuel.Ki = 0.01;
    pid_fuel.Kd = 0.08;
	pid_fuel.voltage_last = 0;
	printf("pid_fuel_init end \n");
}
void VSV_PID_init(pid_vsv& pid_vsv)
{
	printf("PID_init begin \n");
	pid_vsv.SetSpeed = 0.0;	//设定值
	pid_vsv.ActualSpeed = 0.0;//实际值
	pid_vsv.err = 0.0;		//实际误差
	pid_vsv.err_last = 0.0;	//上一次的误差
	pid_vsv.voltage = 0.0;	//输出的电压
	pid_vsv.integral = 0.0;	//积分值
	pid_vsv.umax = 0.01;					//饱和上限
	pid_vsv.deadzone = 0;
	pid_vsv.changeline = 0.5;
	pid_vsv.I1 = 0.6;
	pid_vsv.ulimit = 1.8;
	pid_vsv.Kp = 0.9;
	pid_vsv.Ki = 0.005;
	pid_vsv.Kd = 1.5;
	printf("pid_vsv_init end \n");
}
/*************
//param :
//*** ulimit: 误差的限制，是为了消除在燃油阀在滞后的空白期误差积分累积过快的现象
//*** deadzone: deadzone相当于前向调节过程，先根据经验将电压输出调节到目标值附近，再根据pid算法进一步调节，
//***  其中，根据燃油阀的特性voltage = a * fuel + b,则a=changeline,b = deadzone;
//*** umax: 对输出电压最大值的限制，voltage（max)=umax+ fuel.deadzone+changeline * fuel.SetSpeed
//***
//积分衰减PID控制
*****************/
F64 Fuel_PID(pid_fuel& fuel, F64 set, F64 actual)
{
	fuel.SetSpeed = set/1000;//给定瞬时流量 L
	fuel.ActualSpeed = actual/1000;//实际瞬时流量 L
	fuel.err = fuel.SetSpeed - fuel.ActualSpeed; //计算误差
/*
	if (fuel.err < -fuel.ulimit)
        {
                fuel.err = -fuel.ulimit;
        }
        else if (fuel.err > fuel.ulimit)
        {
                fuel.err = fuel.ulimit;
        }
*/
//	if(fuel.err<fuel.changeline&&fuel.err>-fuel.changeline)
//	{
    if(fuel.err < -fuel.ulimit)
        fuel.integral = fuel.I1*fuel.integral -fuel.ulimit;  //  积分衰减，这里的积分衰减为1（不衰减）
    else if(fuel.err > fuel.ulimit)
        fuel.integral = fuel.I1*fuel.integral +fuel.ulimit;
    else
        fuel.integral = fuel.I1*fuel.integral + fuel.err;
//	}*/
		double deltaf = fuel.Kp *fuel.err + fuel.Ki * fuel.integral +fuel.Kd*(fuel.err - fuel.err_last);


	if (deltaf < -fuel.umax)
	{
		deltaf = -fuel.umax;
	}
	else if (deltaf > fuel.umax)
	{
		deltaf = fuel.umax;
	}
    fuel.voltage = deltaf+ fuel.deadzone+fuel.changeline * fuel.SetSpeed;

/*	if (fuel.voltage > fuel.voltage_last + fuel.ulimit)
	{
		fuel.voltage = fuel.voltage_last + fuel.ulimit;
	}
*/
	/*if (fuel.voltage > fuel.ulimit)
	{
		fuel.voltage = fuel.ulimit;
	}*/
//	deltaf_last = deltaf;
	fuel.voltage_last = fuel.voltage;
	fuel.err_last = fuel.err;
	return fuel.voltage;
}

F64 VSV_PID(pid_vsv& pid_vsv, F64 set, F64 actual)
{
	pid_vsv.SetSpeed = set;
	pid_vsv.ActualSpeed = 10 - actual;//采集出实际位移值
	pid_vsv.err = pid_vsv.SetSpeed - pid_vsv.ActualSpeed; //计算误差
	pid_vsv.integral = pid_vsv.I1*pid_vsv.integral + pid_vsv.err;//k*i + err
	if (pid_vsv.err<pid_vsv.changeline && pid_vsv.err>-pid_vsv.changeline)
	{
		pid_vsv.Ki = pid_vsv.umax;
	}
	pid_vsv.voltage = pid_vsv.Kp *pid_vsv.err + pid_vsv.Ki*pid_vsv.integral + pid_vsv.Kd*(pid_vsv.err - pid_vsv.err_last);//电压限幅
	if (pid_vsv.voltage < -pid_vsv.ulimit)
	{
		pid_vsv.voltage = -pid_vsv.ulimit;
	}
	else if (pid_vsv.voltage > pid_vsv.ulimit)
	{
		pid_vsv.voltage = pid_vsv.ulimit;
	}

	pid_vsv.err_last = pid_vsv.err;

/*	if (pid_vsv.err > 0.02*pid_vsv.SetSpeed || pid_vsv.err < -0.02*pid_vsv.SetSpeed)
	{
		printf("超调\n");
	}
	else
		printf("未超调\n");*/
	return pid_vsv.voltage;
}

