#include "far_controller.h"

#pragma warning(disable:4996)
//I32 ret;
////AD编程
//I32 m_beginCh = 1;
//I32 m_endCh = 8;
//I32 m_adChCount = 0;
//I32 m_codeCountms = 0;
//U16* m_code;
//EM9636_DevPara* pDev;
////IO编程
//I8 startOrStop;
//I8 iStatus[32] = { 0 };
//接收ctrl-c信号，主要是调试用

void ExitExe(int i)
{
	printf("end\n");
	//EM9636_HcStop(pDev);
	//EM9636_DataClose(pDev);//关闭数据连接
	EM9636_CmdClose(pDev);//关闭命令连接
	EM9636_DeviceClose(pDev);//释放设备资源
	exit(0);
}


void setTimer(int seconds, int mseconds)
 {
	 struct timeval temp;

	 temp.tv_sec = seconds;
	 temp.tv_usec = mseconds;//微秒

     //select(0, NULL, NULL, NULL, &temp);
	 return;
 }
void SetAd(EM9636_DevPara* pDev) //AD参数设置
{
	V_I32 gainInx(4, 0);
	//得到当前下位机增益值
	//设置AD采集范围为0~5V 0~20mA
	ret = EM9636_AdSetRange(pDev, EM9636_AD_RANGE_0_5V);
	if (ret < 0)
		throw "EM9636_AdSetRange";
	//设置通道方式为单端
	ret = EM9636_AdSetEndMode(pDev, EM9636_AD_SINGLE);
	if (ret < 0)
		throw "EM9636_AdSetEndMode";
	//设置增益为1倍
	ret = EM9636_AdSetGain(pDev, EM9636_AD_GAIN_1);
	if (ret < 0)
		throw "EM9636_AdSetGain";
	m_adChCount = m_endCh - m_beginCh + 1;
	F64 chFreq = 1000 * 8 ;
	////设置通道切换频率，在非伪同步下通道切换频率就是采集频率，每个通道的采集频率=通道切换频率/通道数
	/*ret = EM9636_DataConnect(pDev, 8001);
	if (ret < 0)
		throw "EM9636_DataConnect";*/
	m_codeCountms = (I32)(chFreq / m_adChCount) * m_adChCount;
	m_code = (U16*)malloc(m_codeCountms * sizeof(U16));
	if (!m_code)
		throw "m_code malloc error!";
}

void ShowAD(EM9636_DevPara* pDev, F64* adValue)
{
	int i, j;
	U32 ulAdValTotal[EM9636_MAXADCHCNT];
	U16 usAdVal[EM9636_MAXADCHCNT];
	memset(ulAdValTotal, 0, sizeof(ulAdValTotal));
	int dataCount = 0;
	for (i = 0; i < m_codeCountms; i += m_adChCount) {
		for (j = 0; j < m_adChCount; j++) {
			ulAdValTotal[j] += m_code[i + j];
		}
		dataCount++;
	}
	for (i = 0; i < m_adChCount; i++) {
		usAdVal[i] = (U16)(ulAdValTotal[i] / dataCount);
	}

	//读取一次AD原码值
	ret = EM9636_AdReadOnceCode(pDev, m_beginCh, m_endCh, m_code);
	if (ret < 0)
		throw "EM9636_AdReadOnceCode";
	//F64 adValue[EM9636_MAXADCHCNT];
	EM9636_AdGetValue(pDev, m_code, m_adChCount, adValue);

}

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
	pid_fuel.umax = 0.01;	//饱和上限
	pid_fuel.deadzone = 6;
	pid_fuel.changeline = 0.5;
	pid_fuel.I1 = 0.6;
	pid_fuel.ulimit = 10;
	pid_fuel.Kp = 0.006;
	pid_fuel.Ki = 0.005;
	pid_fuel.Kd = 0;
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
//积分衰减PID控制
F64 Fuel_PID(pid_fuel& fuel, F64 set, F64 actual)
{
	fuel.SetSpeed = set/1000;//给定瞬时流量 L
	fuel.ActualSpeed = actual/1000;//实际瞬时流量 L
	fuel.err = fuel.SetSpeed - fuel.ActualSpeed; //计算误差

	if (fuel.err < -fuel.ulimit)
        {
                fuel.err = -fuel.ulimit;
        }
        else if (fuel.err > fuel.ulimit)
        {
                fuel.err = fuel.ulimit;
        }

//	if(fuel.err<fuel.changeline&&fuel.err>-fuel.changeline)
//	{
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
	fuel.voltage = deltaf+ fuel.deadzone+0.1 * fuel.SetSpeed;

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

using namespace std;
int main(int argc, char* argv[])
{


	vector< vector<F64> > v;
	F64 duration; //时间
	int flag; //模式
	struct timeval start_t, cur_t;
	//初始化
	pid_fuel p1;
	pid_vsv p2;

	///////
	int semr = init_semr();
	int semw = init_semw();

	/////
	Fuel_PID_init(p1);
	char* vsv_Kp = argv[1];
	char* vsv_Ti = argv[2];
	char* vsv_Td = argv[3];
	char* fuel_Kp = argv[5];
	char* fuel_Ti = argv[6];
	char* fuel_Td = argv[7];
	char* mode = argv[4];
	//char* noise_flag = argv[5]
	p1.Kp = atof(fuel_Kp);
	p1.Ki = atof(fuel_Ti);
	p1.Kd = atof(fuel_Td);
	flag = atof(mode);
//	int noise_i = atof(noise_flag);
	printf("Kp=%f,Ki=%f,Kd=%f\n", p1.Kp, p1.Ki, p1.Kd);
	fflush(stdout);
	VSV_PID_init(p2);
	//Fuel_PID_init(p1);
	p2.Kp = atof(vsv_Kp);
	p2.Ki = atof(vsv_Ti);
	p2.Kd = atof(vsv_Td);
	//printf("%s,%s,%s", p2.Kp, p2.Ki, p2.Kd);
	fflush(stdout);

	fuel_data *pp = initshm_fuel();

	p1.umax = pp->umax;   //饱和上限
        p1.deadzone = pp->deadzone;
	p1.deadzone_d = p1.deadzone - 0.3;
        p1.changeline = pp->changeline;
        p1.I1 = pp->I1;
        p1.ulimit = pp->ulimit;
	close_sharememory(pp);

	F64 liquid = 0;         //流量传感器
	F64 level = 0;          //液位传感器
	F64 lvdt = 0;           //LVDT位移传感器
	F64 force = 0;         //拉压力传感器
	F64 laser = 0;         //激光位移传感器
	F64 sysforce = 0;      //系统压力

	
	F64 aim_S = 0;         //给定VSV位移
	F64 actual_S = 0;      //实际VSV位移
	F64 aim_fuel = 0;         //给定燃油
	F64 last_aim_fuel = 0;
	F64 actual_fuel = 0;     //实际燃油

	double davalue_vsv = 5;
	double davalue_fuel = 0;
	double step = p1.changeline * 1000000;
	//vsv_data *pshm = initshm();
    // aim_S = pshm->aim_s;
    //  printf("aim_S = %f",aim_S);
	//close_sharememory(pshm);
	//EM9636_IoGetAll(pDev, iStatus);//读取开关量输入： 开关量 输入 DI1~DI8 对应数组索引 16~23,开关量输出 DO1~DO8 对应数组索引 24~32。
	//DO 输出为反逻辑，也就当设置为 1 时表示输出为截止状态，设置为 0 时为导通状态
	//iStatus[24] = 1;//DO1
	F64 adValue[EM9636_MAXADCHCNT] = { 0 };
	signal(SIGINT, ExitExe); //接收ctrl-c信号，主要是为了停止采集，关闭连接等清理操作
	pDev = EM9636_DeviceCreate();
	if (pDev == 0)
	{
		printf("EM9636_DeviceCreate error!\n");
		return 0;
	}
	printf("begin\n");
	try
	{
		ret = EM9636_CmdConnect(pDev, (char*)"192.168.1.126", 0, 8000);
		if (ret < 0)
			throw "EM9106_CmdConnect";
		printf("EM9106_CmdConnect\n");
		SetAd(pDev);
		EM9636_DaSetOutMode(pDev, 1, 1, EM9636_DA_RANGE_N10_10V);
		davalue_vsv = -3 * 1000;
		EM9636_DaSet(pDev, 1, davalue_vsv);
		EM9636_DaSetOutMode(pDev, 2, 1, EM9636_DA_RANGE_N10_10V);
		davalue_fuel = 0;
		EM9636_DaSet(pDev, 2, davalue_fuel);
		gettimeofday(&start_t, NULL);
		printf("控制程序启动\n");
		int times = 0; //联合控制中用于计时

		while (1)
		{

        		if (flag == 1) {
				gettimeofday(&cur_t, NULL);
				duration = (cur_t.tv_sec - start_t.tv_sec) * 1000 + (cur_t.tv_usec - start_t.tv_usec) / 1000;
				fuel_data *p = initshm_fuel();
				sem_p(semw);
				//aim_fuel = p->aim_s;
				if (duration < 20000) {
					aim_fuel = 1000;
				}
				else if (duration < 50000) {
				//	aim_fuel = 1800;
					aim_fuel = 500 * sin(times*0.03) + 1000;
					times++;
				}
				else if (duration < 75000) {
				//	aim_fuel = 2600;
					aim_fuel = 500 * sin(times*0.03) + 2000;
                                        times++;
				}
				else if (duration < 100000) {
					aim_fuel = 1000;
				}
				else
					break;
/*
				if(aim_fuel!=last_aim_fuel)
				{
					davalue_fuel = aim_fuel/1000 * 0.1 + 1.5;
					EM9636_DaSet(pDev, 2, davalue_fuel * 1000);
					 ShowAD(pDev, adValue);
					liquid = adValue[0] / 249; //涡轮流量计（电流）AD1  管脚：25
                                printf("流量计电流：%.6fmA\n", liquid);
                                level = adValue[1] / 249;//液位传感器(电流）AD2 管脚：27
                                printf("液位：%.6fmA\n", level);
                                sysforce = adValue[6] / 1000 * 5; //系统压力  AD7 管脚：38
                                printf("系统压力：%.6fMPa\n", sysforce);
                                actual_fuel = (liquid - 4) / 16 * 10 * 1000;//实际瞬时流量

					p1.voltage=davalue_fuel;
					p->aim_s=aim_fuel;
                                p->actual_s=actual_fuel;
                                p->err=p1.err;
                                p->liquid = liquid;
                                p->voltage = p1.voltage;
                                p->level = level;
                                p->sysforce = sysforce;

                                sem_v(semw);
                                printf("时间：%f 给定Wf：%.6f 实际Wf：%.6f 系统压力：%.6f  控制输出：%.6f \n", duration, aim_fuel, actual_fuel, sysforce, p1.voltage);
                                fflush(stdout);

				//	printf("set:%f\n",davalue_fuel);
				//	fflush(stdout);
					usleep(600000);
				//	sleep(1);

				}
				last_aim_fuel = aim_fuel;*/
               // usleep(5000);
               // fuel_data *p = initshm_fuel();
	       			double fuel_temp = 0;
	       			for(int i =1;i<21;i++){
					ShowAD(pDev, adValue);
               // davalue_fuel = 0.01*t;

               // EM9636_DaSet(pDev, 2, davalue_fuel * 1000);
					liquid = adValue[0] / 249; //涡轮流量计（电流）AD1  管脚：25
					fuel_temp = fuel_temp + liquid;

					printf("流量计电流：%.6fmA\n", liquid);
					level = adValue[1] / 249;//液位传感器(电流）AD2 管脚：27
					printf("液位：%.6fmA\n", level);
					sysforce = adValue[6] / 1000 * 5; //系统压力  AD7 管脚：38
					printf("系统压力：%.6fMPa\n", sysforce);
				}
				actual_fuel = (fuel_temp/20 - 4) / 16 * 10 * 1000;//实际瞬时流量
				davalue_fuel = Fuel_PID(p1, aim_fuel, actual_fuel);//调节燃油
				EM9636_DaSet(pDev, 2, davalue_fuel * 1000);
				//关断阀
				//int key = 0;
				//while (key)
				//{
				//	iStatus[24] = 0;//DO1
				//	EM9636_IoSetAll(pDev, iStatus);//设置开关量输出
				//}
				//p1.voltage = davalue_fuel;
               // p->time = duration;
				p->aim_s=aim_fuel;
				p->actual_s=actual_fuel;
				p->err=p1.err;
				p->liquid = fuel_temp;
				p->voltage = p1.voltage;
				p->noise = adValue[7] / 249;	//噪声电流值  AD8 管脚：41
				p->level = level;
				p->sysforce = sysforce;

				sem_v(semw);
				close_sharememory(p);
				printf("时间：%f 给定Wf：%.6f 实际Wf：%.6f 系统压力：%.6f  控制输出：%.6f \n", duration, aim_fuel, actual_fuel, sysforce, p1.voltage);
				fflush(stdout);
				if(level>13)
				{
					davalue_fuel = 0;
					EM9636_DaSet(pDev, 2, davalue_fuel * 1000);
					return 0;
				}
			//	sleep(1);
				usleep(step);
			}
			if (flag == 0) {
                /*    for(int  t = 0; t < 1000; t++)
            {*/


                vsv_data *pshm = initshm();
		sem_p(semw);
				aim_S = pshm->aim_s;
				printf("aim_S = %f",aim_S);
				ShowAD(pDev, adValue);
				lvdt = adValue[3] / 1000;//LVDT位移 AD4 管脚：32
				//force = adValue[4] / 1000; //拉压力传感器 AD5 管脚：34
				//laser = adValue[5] / 1000; //激光位移传感器 AD6 管脚：36
				sysforce = adValue[6] / 1000 * 5; //系统压力  AD7 管脚：38
				actual_S = lvdt * 2;
				davalue_vsv = VSV_PID(p2, aim_S, actual_S);
				EM9636_DaSet(pDev, 1, davalue_vsv * 1000);  //（设备句柄 通道 DA输出值）

				pshm->aim_s = aim_S;
				pshm->actual_s = p2.ActualSpeed;
				pshm->err = p2.err;
				pshm->lvdt = lvdt;
				pshm->voltage = p2.voltage;
				sem_v(semw);
				close_sharememory(pshm);
				printf("给定位移：%4.4f 实际位移：%4.4f LVDT位移：%4.4f 实际误差：%4.4f  实际输出电压：%4.4f \n", aim_S, p2.ActualSpeed, lvdt, p2.err, p2.voltage);
				fflush(stdout);
			//	usleep(500000);


            //}
			}
			if (flag == 2) {
                    /***控制命令***/
				gettimeofday(&cur_t, NULL);
				duration = (cur_t.tv_sec - start_t.tv_sec) * 1000 + (cur_t.tv_usec - start_t.tv_usec) / 1000;
		/*		if (duration < 15000) {
					aim_fuel = 1000;
					aim_S = 0.44* duration  / 1000;
				}
				else if (duration < 30000) {
					aim_fuel = 1800;
					aim_S = 6.6-0.22* (duration-15000) / 1000;
				}
				else if (duration < 45000) {
					aim_fuel = 2600;
					aim_S = 3.3 - 0.22* (duration - 30000) / 1000;
				}
				else if (duration < 50000) {
					aim_fuel = 2000;
					aim_S = 3.3;
				}
				else if (duration < 55000) {
					aim_fuel = 1800;
					aim_S = 6.6;
				}
				else if (duration < 60000) {
					aim_fuel = 1000;
					aim_S = 3.3;
				}
				else
				{
					break;
				}
				*/
				/****vsv***/
                vsv_data *pshm = initshm();
                sem_p(semw);
				//aim_S = pshm->aim_s;
				printf("aim_S = %f",aim_S);
				ShowAD(pDev, adValue);
				lvdt = adValue[3] / 1000;//LVDT位移 AD4 管脚：32
				//force = adValue[4] / 1000; //拉压力传感器 AD5 管脚：34
				//laser = adValue[5] / 1000; //激光位移传感器 AD6 管脚：36
				sysforce = adValue[6] / 1000 * 5; //系统压力  AD7 管脚：38
				actual_S = lvdt * 2;
				aim_S = pshm->aim_s;
				davalue_vsv = VSV_PID(p2, aim_S, actual_S);
				EM9636_DaSet(pDev, 1, davalue_vsv * 1000);  //（设备句柄 通道 DA输出值）

				pshm->aim_s = aim_S;
				pshm->actual_s = p2.ActualSpeed;
				pshm->err = p2.err;
				pshm->lvdt = lvdt;
				pshm->voltage = p2.voltage;
				sem_v(semw);
				close_sharememory(pshm);
				/****fuel****/

				times++;
				if(times==50)
                {
                    times = 0;
                   // gettimeofday(&cur_t, NULL);
				//duration = (cur_t.tv_sec - start_t.tv_sec) * 1000 + (cur_t.tv_usec - start_t.tv_usec) / 1000;
				fuel_data *p = initshm_fuel();
				sem_p(semw);
				//aim_fuel = p->aim_s;
				/*
				if (duration < 25000) {
					aim_fuel = 1000;
				}
				else if (duration < 50000) {
					aim_fuel = 1800;
				}
				else if (duration < 75000) {
					aim_fuel = 2600;
				}
				else if (duration < 100000) {
					aim_fuel = 1000;
				}
				else
					break;


*/
	       			double fuel_temp = 0;
	       			for(int i =1;i<21;i++){
					ShowAD(pDev, adValue);
               // davalue_fuel = 0.01*t;

               // EM9636_DaSet(pDev, 2, davalue_fuel * 1000);
					liquid = adValue[0] / 249; //涡轮流量计（电流）AD1  管脚：25
					fuel_temp = fuel_temp + liquid;

					printf("流量计电流：%.6fmA\n", liquid);
					level = adValue[1] / 249;//液位传感器(电流）AD2 管脚：27
					printf("液位：%.6fmA\n", level);
					sysforce = adValue[6] / 1000 * 5; //系统压力  AD7 管脚：38
					printf("系统压力：%.6fMPa\n", sysforce);
				}
				actual_fuel = (fuel_temp/20 - 4) / 16 * 10 * 1000;//实际瞬时流量
				aim_fuel = p->aim_s;
				davalue_fuel = Fuel_PID(p1, aim_fuel, actual_fuel);//调节燃油
				EM9636_DaSet(pDev, 2, davalue_fuel * 1000);
				p->aim_s=aim_fuel;
				p->actual_s=actual_fuel;
			//	p->err=p1.err;
				p->liquid = fuel_temp;
				p->voltage = p1.voltage;
				p->noise = adValue[7] / 249;	//噪声电流值  AD8 管脚：41
				p->level = level;
				p->sysforce = sysforce;

				sem_v(semw);
				close_sharememory(p);
				printf("时间：%f 给定Wf：%.6f 实际Wf：%.6f 系统压力：%.6f  控制输出：%.6f \n", duration, aim_fuel, actual_fuel, sysforce, p1.voltage);
				//fflush(stdout);
				if(level>13)
				{
					davalue_fuel = 0;
					EM9636_DaSet(pDev, 2, davalue_fuel * 1000);
					return 0;
				}
				}
				/*********/
				printf("给定燃油：%.4f 实际燃油：%.4f 流量计：%.4f 实际误差：%.4f  实际输出电压：%.4f \n", aim_fuel, actual_fuel, liquid, p1.err, p1.voltage);
				printf("给定位移：%.4f 实际位移：%.4f LVDT位移：%.4f 实际误差：%.4f  实际输出电压：%.4f \n", aim_S, actual_S, lvdt, p2.err, p2.voltage);
                fflush(stdout);
            }

		}
	}
	//捕获并处理异常
	catch (const char* e)
	{
		printf("%s error code :%d!\n", e, ret);
	}
	ExitExe(0);
	return 0;
}


