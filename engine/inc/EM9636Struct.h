// EM9636_Server.h: interface for the CEM9636 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EM9636_Server_H__D1413467_66A2_475B_8398_F579D95B3FB0__INCLUDED_)
#define AFX_EM9636_Server_H__D1413467_66A2_475B_8398_F579D95B3FB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ZT_Type.h"
#include <vector>

typedef struct EM9636_ADPARA
{//AD相关参数
	I32 beginChNo;//起始通道号
	I32 endChNo;//终止通道号
	I32 endMode;//0，单端；1，差分
	I32 rangeInx;//采集范围，请参见“AD采集范围”宏设置
	I32 gainInx;//增益范围，请参见“AD增益”宏设置
}EM9636_AdPara;

typedef struct EM9636_IOPARA
{//开关量相关参数
	I32 chInFifo;//IO1~IO16是否进入FIFO
	I32 dir[4];//四组开关量方向，0，输入，1，输出
}EM9636_IoPara;

typedef struct EM9636_CTPARA
{//计数器相关参数
	U16 mode[EM9636_MAXCTCHCNT];//计数方式，具体请看“计数方式宏定义”
	double freqBase[EM9636_MAXCTCHCNT];//分频系数时基，以ms为单位，在测量高低频率时含义不同，计算方法请看示例程序
}EM9636_CtPara;

typedef struct ZTLC_PARA
{//设备共用参数
	ZTLC_PARA()
	{
		cmdFd = 0;
		dataFd = 0;
		isHcStart = 0;
		errorCode = 0;
		pthread_mutex_init( &sectCmd, 0 );
	}
	int cmdFd;//命令端口
	int  dataFd;//数据端口
	I32 isHcStart;
	I32 errorCode;//错误码，如果产生超时错误，需要重新建立连接。
	pthread_mutex_t sectCmd;
}ZTLC_Para;

typedef struct EM9636_DEVPARA
{//设备共用参数
	EM9636_AdPara adPara;
	EM9636_IoPara ioPara;
	EM9636_CtPara ctPara;
	F64 chFreq;//通道切换频率，如果AD使能
	F64 groupFreq;//组切换频率，只在伪同步下有效
	I32 startMode;//启动方式，具体请看“启动方式宏定义”
	I32 isPSync;//0,非伪同步；1伪同步
	I32 triSrc;
	I32 triMode;
	I8 strIP[256];//存放IP地址
	U16 cmdPort;
	ZTLC_PARA* hCmd;//命令端口操作句柄
	int dataFd;//数据端口
	I32 dataPort;
	I32 isHcStart;
	I32 TimeOutCnt;//超时次数，用于判断网络是否中断 //2014-04-24
	bool enableWtd;//是否使能看门狗 //2014-04-24
	I8 ioInFifo;
	I8 diInFifo;
	I8 ecInFifol16[EM9636_MAXECCHCNT];
	I8 ecInFifoh16[EM9636_MAXECCHCNT];
	I8 ctInFifo[EM9636_MAXCTCHCNT];
	I32 asCount;
	I32 threadError;
	U16 curFullCode[EM9636_MAXADCHCNT];
	int errorCode;
	pthread_mutex_t sectCmd;
}EM9636_DevPara;

typedef struct DAQTIME//采集时间段 
{
	//开始时间
	I8 startS;//秒
	I8 startM;//分
	I8 startH;//时
	//结束时间
	I8 endS;//秒
	I8 endM;//分
	I8 endH;//时
}DaqTime;

typedef struct OFFLINESET
{
	short version;//版本号
	//采集时间间隔设置
	I16 intervalMS;//毫秒
	I8 intervalS;//秒
	I8 intervalM;//分
	I8 intervalH;//小时
	I8 daqStyle; //daqStyle：采集方式：
	//0下位机上电启动采集；
	//1上位机控制启停
	I8 startMode;//启动方式 0 软件启动AD转换（慢速采集） 1 内时钟启动AD转换 2 外时钟启动AD转换 3 外部高电平启动AD采集
	I32 groupCount;//在高速采集时，从fifo中读取多少组数据读取一次不进入fifo的数据（io、ct、ec）
	I32 isPSync;//0非伪同步，1伪同步
	I32 chFreq;//通道切换采集频率
	I32 groupFreq;//组采集频率，伪同步有效
	I8 adBeginCh;//AD起始通道
	I8 adEndCh;//AD结束通道
	I8 adRange;//AD采集范围
	I8 adGain;//AD 增益
	I8 adEndMode;//AD单双端
	I8 ioInFifo;//io1~io16是否进入fifo
	I8 ioDir[4];//开关量方向
	I8 ctMode[6];//计数器方式
	I32 ctGateFreq[6];//门控信号频率
	I8 ad[EM9636_MAXADCHCNT];//对应ad通道是否存盘，0禁止，1允许
	I8 io[4];//对应组的开关量是否存盘，0禁止，1允许
	I8 ct[6];//计数器通道是否存盘，0禁止，1允许
	I8 ec[2];//编码器数据是否存盘，0禁止，1允许
	I16 zCode[EM9636_MAXADCHCNT];//全部18个通道的零点值
	I16 fCode[EM9636_MAXADCHCNT];//全部18个通道的满度值
	I8 daqTimeCnt;//采集时间段个数
	U32 savelength; //存盘数据量控制
	DaqTime* daqTime; //时间段起止时间
	U32 saveCtrlDport;//存盘控制信号端口(数字)
	U32 saveCtrlDvalue;//存盘控制信号值(数字)
	U32 saveCtrlAport;//存盘控制信号端口(模拟)
	I32 saveCtrlAvalue;//存盘控制信号值(模拟)
}OfflineSet;

typedef struct OFFLINEFILE{
	FILE* f;
	I32 dataBeginPos;//当前位置
	I32 dataSize;
	OfflineSet os;
	I32 adChCnt;//include adCh an ioInFifo
	I32 lsAdChCnt;
	I32 lsCtChCnt;
	I32 lsIoGroupCnt;
	I32 lsEcChCnt;
}OfflineFile;

#endif // !defined(AFX_EM9636_Server_H__D1413467_66A2_475B_8398_F579D95B3FB0__INCLUDED_)
