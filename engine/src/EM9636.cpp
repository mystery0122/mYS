// EM9636.cpp : 定义 DLL 应用程序的导出函数。
//

#include <math.h>
#include <time.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <memory.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <sys/io.h>
#include <algorithm>

#include "../inc/ZT_Type.h"
#include "../inc/EM9636.h"
#include "../inc/EM9636Struct.h"
#include "../inc/EM9636_Errors.h"
#include "../inc/TimeInterval.h"
#include "../inc/ZCD_CS.h"
#define SOCKET_ERROR -1
#define ZCDFIONBIO 0
#define ZCDFIONREAD 1

int net_start(char * serverip, unsigned int port){
	int sockfd;
	struct sockaddr_in svraddr;
	bzero(&svraddr,sizeof(svraddr));

	svraddr.sin_family=AF_INET;
	svraddr.sin_port=htons(port);
    if(inet_aton(serverip, &svraddr.sin_addr) == 0){
        printf("\nServer IP Address Error!");
    	return -1;
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		printf("\nCan not create socket");
		return -1;
	}

	socklen_t length=sizeof(struct sockaddr_in);
	printf("\nConnecting to data port...\n");

	if (connect(sockfd,(struct sockaddr*)&svraddr, length) < 0){
        printf("\nCan Not Connect To %s !", serverip);
        close(sockfd);
        return -1;
    }

	return sockfd;
}

int ioctlsocket( int fd, int temp, unsigned long* noBlock )
{
	switch( temp )
	{
	case ZCDFIONBIO:
		int flags;
		if (flags = fcntl(fd, F_GETFL, 0) < 0)
		{
			perror("fcntl");
			return -1;
		}
		//设为阻塞方式
		if( *noBlock )
		{
			flags |= O_NONBLOCK;
		}else{
			flags &= ~O_NONBLOCK;
		}
		if (fcntl(STDIN_FILENO, F_SETFL, flags) < 0)
		{
			perror("fcntl");
			return -1;
		}
		break;
	case ZCDFIONREAD:
		return ioctl( fd, FIONREAD, noBlock );
		break;
	default:
		return -1;
	}
	return 0;
}

ZTLC_Para* _stdcall ZTLC_CmdConnect( I8* strIP, U16 port, I32 timeoutMS )
{
	ZTLC_Para* pPara = new ZTLC_Para;
	if( pPara == 0 )
		return 0;
	if( strIP == 0 )
	{
		delete pPara;
		return 0;
	}
	//建立命令套接字，TCP协议
	int cmdFd = socket( AF_INET, SOCK_STREAM, 0 );
	if ( cmdFd == SOCKET_ERROR  ) {
		delete pPara;
		return 0;
	}
//	printf( "%s IP:%s, port:%d\n", __FUNCTION__, strIP, port );
	//设置非阻塞方式连接
	int ret;
	unsigned long ul = 1;
	ret = ioctlsocket( cmdFd, ZCDFIONBIO, (unsigned long*)&ul );
	if( ret == SOCKET_ERROR){
		delete pPara;
		return 0;
	}
	//连接   
	//设置地址信息
	struct sockaddr_in cmdAddress;
	memset( &cmdAddress, 0, sizeof(cmdAddress) );
	cmdAddress.sin_family = AF_INET;
	cmdAddress.sin_addr.s_addr = inet_addr(strIP);
	cmdAddress.sin_port = htons(port);
	printf( "connect:%s\n", strIP );
	ret = connect( cmdFd, (struct sockaddr*)&cmdAddress, sizeof(cmdAddress) );
	if( ret < 0 )
	{
		int err = errno;
		printf( "%s connect failed!%s\n", __FUNCTION__, strerror(err) );
	}

	//设置超时
	struct timeval timeout;
	fd_set r,w;

	FD_ZERO( &r );   
	FD_SET( cmdFd, &r );
	timeout.tv_sec = timeoutMS / 1000;
	timeout.tv_usec = (timeoutMS % 1000) * 1000000;
	ret = select( cmdFd+1, 0, &r, 0, &timeout );
	int err = errno;
	if( ret <= 0 )
	{   
		::close( cmdFd );
		delete pPara;
		return 0;
	}

	//设回阻塞模式   
	unsigned long ul1 = 0;   
	ret = ioctlsocket( cmdFd, ZCDFIONBIO, (unsigned long*)&ul1 );
	if( ret == SOCKET_ERROR ){   
		close( cmdFd );
		delete pPara;
		return 0;
	}
	//	ZTLC_InitDev( pDev );
	pPara->cmdFd = cmdFd;

	return pPara;
}

void ZTLC_CmdClose( ZTLC_PARA* p )
{
	close( p->cmdFd );
	delete p;
}

void MakeSendFrame( U16 addr, const I8 vData[256], U32 bytesTotal, I8 v[256], U32* vSize )
{
	memset( v, 0, 13 );
	v[5] = (U8)bytesTotal + 7;//后面的字符数
	v[6] = 1;
	v[7] = 16;
	v[8] = (addr >> 8) & 0xff;
	v[9] = addr & 0xff;
	v[10] = ((bytesTotal / 2) >> 8) & 0xff;
	v[11] = (bytesTotal / 2) & 0xff;
	v[12] = bytesTotal & 0xff;

	memcpy( v + 13, vData, bytesTotal );
	*vSize = 13 + bytesTotal;
}

void MakeRecvFrame( U16 addr, U32 bytesCount, I8 v[256], U32* vSize )
{
	memset( v, 0, 12 );
	U16 regCount = (U16)bytesCount / 2;
	v[5] = 6;//后面的字符数
	v[6] = 1;
	v[7] = 3;
	v[8] = (addr >> 8) & 0xff;
	v[9] = addr & 0xff;
	v[10] = (regCount >> 8) & 0xff;
	v[11] = regCount & 0xff;
	*vSize = 12;
}

I32 ClearRecvBuffer( ZTLC_Para* pDev )
{//每次读取失败后，都要清空一下缓冲区，否则就会发生错位
	//设置非阻塞方式
	//	EnterCriticalSection( &pDev->sectCmd );
	CZCD_CS cs( &pDev->sectCmd );
	U32 ul = 1;
	I32 ret = ioctlsocket( pDev->cmdFd, ZCDFIONBIO, (U32*)&ul );
	if( ret == SOCKET_ERROR){
		return EM9636_FAILURE;

	}

	char buf[256];
	while( recv( pDev->cmdFd, buf, sizeof(buf), 0 ) > 0 );

	//设置阻塞方式连接
	ul = 0;
	ret = ioctlsocket( pDev->cmdFd, ZCDFIONBIO, (unsigned long*)&ul );
	if( ret == SOCKET_ERROR){
		return EM9636_FAILURE;
	}
	//	LeaveCriticalSection( &pDev->sectCmd );
	return 0;
}

I32 ZTLC_SendCommand( ZTLC_Para* pDev, I8 cmd[256], U32 cmdSize, I8* retInfo, U32 retSize, I32 outtime )
{
	I32 retv;
	//	EnterCriticalSection( &pDev->sectCmd );
	CZCD_CS cs( &pDev->sectCmd );
	if( ( retv = send( pDev->cmdFd, cmd, cmdSize, 0 ) ) != cmdSize ){
		int err = errno;
		printf( "%s,send:%s\n", __FUNCTION__, strerror(errno));
		if( err == ECONNRESET  )
			return EM9636_CONNECT_ERROR;
		else
			return EM9636_SEND_ERROR;
	}

	struct timeval timeout;
	timeout.tv_sec = outtime / 1000;
	timeout.tv_usec = (outtime % 1000) * 1000000;
	//设定接收超时时间
	if( setsockopt( pDev->cmdFd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout) ) == SOCKET_ERROR )
	{
		int err = errno;
		printf( "%s,setsockopt:%s\n", __FUNCTION__, strerror(errno));
		if( err == ECONNRESET  )
			return EM9636_CONNECT_ERROR;
		else
			return EM9636_SEND_ERROR;
	}

	if( retSize == 0 )
		return retv;

	//	CTimeInterval tv;
	retv = recv( pDev->cmdFd, retInfo, retSize, 0 );
	if( retv < 0 )
	{
		printf( "%s,recv:%s\n", __FUNCTION__, strerror(errno));
		int err = errno;
		//		ClearRecvBuffer();
		if( err == ETIMEDOUT  )
		{
			ClearRecvBuffer( pDev );
			pDev->errorCode = EM9636_TIMEOUT_ERROR;
			return EM9636_TIMEOUT_ERROR;
		}
		else
		{
			ClearRecvBuffer( pDev );
			if( err == ECONNRESET  )
			{
				pDev->errorCode = EM9636_CONNECT_ERROR;
				return EM9636_CONNECT_ERROR;
			}
			else
				return EM9636_SEND_ERROR;
		}
	}
	//	LeaveCriticalSection( &pDev->sectCmd );
	//	TRACE( "SendCommand:%f\n", tv.GetIntervalMS() );
	return retv;
}

I32 _stdcall ZTLC_SendAndVerify( ZTLC_Para* pDev, U16 addr, I8* vcData, U32 vcSize, int outtime )
{
	if( pDev == (ZTLC_Para*)-1 )
		return EM9636_FAILURE;
	I8 cmd[256];
	U32 cmdSize;
	MakeSendFrame( addr, vcData, vcSize, cmd, &cmdSize );
	I8 retInfo[12];
	I32 ret = ZTLC_SendCommand( pDev, cmd, cmdSize, retInfo, sizeof(retInfo), outtime );
	if( ret )
		return ret;
	//	MyTrace( "%2x ", cmd );
	//	MyTrace( "%2x ", retInfo );
	U8 regCnt = 0;
	regCnt |= retInfo[10];
	regCnt = (regCnt<<8) | retInfo[11];

	if( regCnt * 2 != vcSize )
	{
		ClearRecvBuffer( pDev );
		return EM9636_CMDVERIFY_ERROR;
	}
	return 0;
}

I32 _stdcall ZTLC_RecvAndVerify( ZTLC_Para* pDev, U16 addr, I8* vcData, U32 vcSize, I32 outtime )
{
	if( pDev == (ZTLC_Para*)-1 )
		return EM9636_FAILURE;

	I8 cmd[256];
	U32 cmdSize;
	MakeRecvFrame( addr, vcSize, cmd, &cmdSize );
	//	MyTrace( "%2x ", cmd );
	I8 retInfo[256];
	U32 retSize = vcSize + 9;
	I32 ret = ZTLC_SendCommand( pDev, cmd, cmdSize, retInfo, retSize, outtime );
	if( ret < 0 )
		return ret;

	char fnCode = retInfo[7];
	unsigned char byteCnt = (unsigned char)retInfo[8];
	if( (fnCode & 0x80) )
	{
		if( retInfo[8] == 4 )
			return EM9636_DATANOTREADY;
		else
			return EM9636_FAILURE;
	}else if( fnCode != 3 || byteCnt != vcSize )
	{
		//		MyTrace( "%2x ", retInfo );
		ClearRecvBuffer( pDev );
		return EM9636_RECVVERIFY_ERROR;
	}
	memcpy( vcData, retInfo + 9, vcSize );
	return 0;
}

EM9636_DevPara* _stdcall EM9636_DeviceCreate()
{
	EM9636_DevPara* pDev = new EM9636_DevPara;
	if( !pDev )
		return 0;

	memset( pDev->strIP, 0, sizeof(pDev->strIP) );
	pDev->cmdPort = 0;

	pDev->adPara.beginChNo = 1;
	pDev->adPara.endChNo = EM9636_MAXADCHCNT;
	pDev->adPara.endMode = EM9636_AD_SINGLE;
	pDev->adPara.gainInx = EM9636_AD_GAIN_1;
	pDev->adPara.rangeInx = EM9636_AD_RANGE_0_10V;

	I32 i;
	for( i = 0; i < EM9636_MAXADCHCNT; ++i )
	{
		pDev->curFullCode[i] = 65535 * 19 * 249 / 5000;
	}

	for( i = 0; i < EM9636_MAXCTCHCNT; ++i )
	{
		pDev->ctPara.mode[i] = EM9636_CT_MODE_COUNT;
		pDev->ctPara.freqBase[i] = 1000;
	}

	pDev->ioPara.chInFifo = EM9636_IOINFIFO_NO;
	pDev->ioPara.dir[0] = EM9636_IO_IN;
	pDev->ioPara.dir[1] = EM9636_IO_IN;

	pDev->chFreq = 100000;
	pDev->groupFreq = 1000;
	pDev->isPSync = EM9636_PSYNC_NO;
	pDev->ioInFifo = 0;
	pDev->triSrc = EM9636_TRI_IN;
	pDev->triMode = EM9636_TRI_UPEDGE;
	pDev->hCmd = 0;
	pDev->dataFd = 0;
	pDev->dataPort = 8001;
	pDev->isHcStart = 0;
	pDev->asCount = 512;
	pDev->threadError = EM9636_SUCCESS;
//	pDev->codeFifo.Resize( 16 * 1024 * 1024 );
//	pDev->hReadThreadOver = CreateEvent( NULL, FALSE, FALSE, NULL );
	pDev->diInFifo = 0;
	memset( pDev->ecInFifol16, 0, sizeof(pDev->ecInFifol16) );
	memset( pDev->ecInFifoh16, 0, sizeof(pDev->ecInFifoh16) );
	memset( pDev->ctInFifo, 0, sizeof(pDev->ctInFifo) );
	pDev->errorCode = 0;
	return pDev;
}

void _stdcall EM9636_DeviceClose( EM9636_DevPara* hDevice )
{
	if( hDevice == 0 )
		return;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;
	delete pDev;
}

I32 _stdcall EM9636_CmdConnect( EM9636_DevPara* hDevice, char* strIP, I32 ipBC, I32 cmdPort, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;
	if( strIP == 0 )
		return EM9636_SOCKET_ERROR;

	if( ipBC == 0 )
		ipBC = (I32)strlen( strIP );

	if( ipBC && ipBC < 256 )
	{
		memcpy( pDev->strIP, strIP, ipBC );
		pDev->strIP[ipBC] = 0;
	}

	pDev->cmdPort = (U16)cmdPort;

	pDev->hCmd = ZTLC_CmdConnect( pDev->strIP, (U16)cmdPort, timeOutMS );
	if( pDev->hCmd == 0 )
	{
		pDev->hCmd = 0;
		return EM9636_FAILURE;
	}

	pDev->TimeOutCnt = 0;
	pthread_mutex_init( &pDev->sectCmd, 0 );
	return EM9636_SUCCESS;
}

I32 SetAutoSend( EM9636_DevPara* pDev, I8 isSutoSend, I32 timeOutMS )
{
	V_I8 vc(2,0);
	vc[1] = isSutoSend;
	I32 ret = ZTLC_SendAndVerify( pDev->hCmd, 23, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	return 0;
}

I32 _stdcall EM9636_DataConnect( EM9636_DevPara* hDevice, I32 dataPort, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	if( pDev->strIP[0] == 0 )
		return EM9636_SOCKET_ERROR;

	if( pDev->hCmd == 0 )
		return EM9636_SOCKET_ERROR;

	//先使能自动传输数据
	int ret = SetAutoSend( pDev, 1, timeOutMS );
	if( ret < 0 )
		return ret;

	//等待下位机数据线程建立完毕
	usleep(100000);
	//建立命令套接字，TCP协议
	//此处和windows不一样，如果使用windows方式，连接不成功也不会报告错误
	int dataFd = net_start(pDev->strIP, dataPort);
	if (dataFd < 0)
	{
		printf( "Connect data port failed!\n");
		return EM9636_SOCKET_ERROR;
	}
	printf( "Connect data port sucess!\n");
	pDev->dataFd = dataFd;
	pDev->dataPort = dataPort;
	return EM9636_SUCCESS;
}

void _stdcall EM9636_CmdClose( EM9636_DevPara* hDevice, I32 timeOutMS )
{
	if( hDevice == 0 )
		return;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	if( pDev->dataFd )
		EM9636_DataClose( hDevice, timeOutMS );

	if( pDev->hCmd )
	{
		ZTLC_CmdClose( pDev->hCmd );
		pDev->hCmd = 0;
		pthread_mutex_destroy( &pDev->sectCmd );
	}
}

void _stdcall EM9636_DataClose( EM9636_DevPara* hDevice, I32 timeOutMS )
{
	if( hDevice == 0 )
		return;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;
	if( pDev->dataFd == 0 )
		return;
	close( pDev->dataFd );
	//先禁止自动传输数据
	SetAutoSend( pDev, 0, timeOutMS );

//	closesocket( pDev->dataFd );
	pDev->dataFd = 0;
}

bool IsAdChRight( I32 beginNo, I32 endNo )
{
	return beginNo <= endNo && ( 1 <= beginNo && endNo <= EM9636_MAXADCHCNT );
}

I32 _stdcall EM9636_AdSetChRange( EM9636_DevPara* hDevice, I32 beginNo, I32 endNo, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;
	V_I8 vc( 2, 0 );
	vc[0] = beginNo & 0xff;
	vc[1] = endNo & 0xff;
	I32 ret = ZTLC_SendAndVerify( pDev->hCmd, 15, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	pDev->adPara.beginChNo = beginNo;
	pDev->adPara.endChNo = endNo;

	return EM9636_SUCCESS;
}

I32 _stdcall EM9636_AdSetEndMode( EM9636_DevPara* hDevice, I32 endMode, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	if(endMode)
		pDev->adPara.endMode = 1;
	else
		pDev->adPara.endMode = 0;

	return EM9636_SUCCESS;
}


I32 EM9636_RomWrite( EM9636_DevPara* hDevice, U16 addr, U16 data, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	V_I8 vc(4);
	addr*=2;
	vc[0] = (addr >> 8) & 0xff;
	vc[1] = addr & 0xff;
	vc[2] = (data >> 8) & 0xff;
	vc[3] = data & 0xff;

	I32 ret = ZTLC_SendAndVerify( pDev->hCmd, 200, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	return 0;
}

I32 EM9636_RomRead( EM9636_DevPara* hDevice, U16 beginAddr, U8 dataCount, U16* oData, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	if( dataCount > 120 )
		return -1;
	beginAddr*=2;
	V_I8 vc(4);
	vc[0] = 0;
	vc[1] = 0;
	vc[2] = (beginAddr>>8) & 0xff;
	vc[3] = beginAddr & 0xff;

	I32 ret = ZTLC_SendAndVerify( pDev->hCmd, 202, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	vc.resize( dataCount * 2 );
	ret = ZTLC_RecvAndVerify( pDev->hCmd, 200, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;
	for( int i = 0; i < dataCount; ++i )
	{
		oData[i] = ((vc[i*2]<<8)&0xff00) | (vc[i*2+1]&0xff);
	}

	return 0;
}

I32 EM9636_CurSetFull( EM9636_DevPara* hDevice, I32 chNo, U16 fullCode )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	if( chNo < 1 || chNo > EM9636_MAXADCHCNT )
		return -1;
	I32 chInx = chNo - 1;
	return EM9636_RomWrite( hDevice, (chInx)&0xffff, fullCode );
}

I32 EM9636_CurGetFULL( EM9636_DevPara* hDevice, I32 beginChNo, U8 chCnt, U16* fullCode )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	if( !fullCode )
		return -1;
	if( beginChNo + chCnt - 1 > EM9636_MAXADCHCNT )
		return -1;
	I32 beginAddr = (beginChNo - 1);
	I32 ret = EM9636_RomRead( hDevice, beginAddr&0xffff, chCnt, fullCode );
	if( ret < 0 )
		return ret;

	return 0;
}

I32 EM9636_AdGetCurrentMA( EM9636_DevPara* hDevice, I32 chNo, U16* usCode, I32 codeCount, double* adValue )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	if( chNo < 1 || chNo > EM9636_MAXADCHCNT )
		return -1;
	double fullVal = 19000.0;

	for( I32 i = 0; i < codeCount; ++i)
		adValue[i] = usCode[i] * fullVal / pDev->curFullCode[chNo-1];

	return 0;
}

I32 _stdcall EM9636_AdSetRange( EM9636_DevPara* hDevice, I32 rangeInx, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	V_I8 vc( 2, 0 );
	//if 0~40mA then to use 0~5V
	vc[1] = rangeInx == EM9636_AD_RANGE_0_20mA ? EM9636_AD_RANGE_0_5V : rangeInx & 0xff;
	I32 ret = ZTLC_SendAndVerify( pDev->hCmd, 10, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	pDev->adPara.rangeInx = rangeInx;

	if( rangeInx == EM9636_AD_RANGE_0_20mA )
	{
		ret = EM9636_CurGetFULL( hDevice, 1, EM9636_MAXADCHCNT, pDev->curFullCode );
		//有可能是由于下位机固件不支持，因此也不能算是错误
		if( ret < 0 )
			return EM9636_SUCCESS;
		for( I32 i = 0; i < EM9636_MAXADCHCNT; ++i )
		{
			if( pDev->curFullCode[i] < 32768 || pDev->curFullCode[i] == 65535 )
			{
				pDev->curFullCode[i] = 65535 * 19 * 249 / 5000;
			}
		}
	}

	return EM9636_SUCCESS;
}

I32 _stdcall EM9636_AdSetGain( EM9636_DevPara* hDevice, I32 gainInx, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	if( gainInx < 0 || gainInx > 3 )
		return EM9636_FAILURE;

	V_I8 cmd(2, 0);
	cmd[1] = gainInx & 0xff;
	I32 ret = ZTLC_SendAndVerify( pDev->hCmd, 56, &cmd[0], (U32)cmd.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	pDev->adPara.gainInx = gainInx;

	return EM9636_SUCCESS;
}

I32 _stdcall EM9636_AdReadOnceCode( EM9636_DevPara* hDevice, I32 beginChNo, I32 endChNo, U16* adCode, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	if( !IsAdChRight( beginChNo, endChNo ) )
		return EM9636_FAILURE;

	I32 beginChInx = beginChNo - 1;
	I32 endChInx = endChNo - 1;

	I32 chCnt = endChInx - beginChInx + 1;
	V_I8 vc(chCnt * 2, 0);
	I32 ret = ZTLC_RecvAndVerify( pDev->hCmd, 256 + (U16)beginChInx, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	for( I32 i = 0; i < chCnt; ++i )
	{
		adCode[i] = (vc[i*2] & 0xff);
		adCode[i] <<= 8;
		adCode[i] |= (vc[i*2 + 1]&0xff);
	}

	return EM9636_SUCCESS;
}

I32 AdGetRangeMaxMin( I32 rangeInx, F64* maxVal, F64* minVal )
{
	F64 maxV, minV;
	switch( rangeInx )
	{
	case EM9636_AD_RANGE_N10_10V:
		maxV = 10000.0;
		minV = -10000.0;
		break;
	case EM9636_AD_RANGE_N5_5V:
		maxV = 5000.0;
		minV = -5000.0;
		break;
	case EM9636_AD_RANGE_0_10V:
		maxV = 10000.0;
		minV = 0.0;
		break;
	case EM9636_AD_RANGE_0_5V:
		maxV = 5000.0;
		minV = 0.0;
		break;
	case EM9636_AD_RANGE_0_20mA:
		maxV = 5000.0/249*1000;
		minV = 0.0;
		break;
	default:
		return EM9636_FAILURE;
	}
	if( maxVal )
		*maxVal = maxV;
	if( minVal )
		*minVal = minV;

	return 0;
}

I32 EM9636_AdGetRangeMaxMin( EM9636_DevPara* pDev, F64* maxVal, F64* minVal )
{
	return AdGetRangeMaxMin( pDev->adPara.rangeInx, maxVal, minVal );
}

I32 _stdcall EM9636_IoGetCode( EM9636_DevPara* hDevice, U16* usCode, I32 codeCount, U16* ioCode, I32* ioCodeCount )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	if( !usCode || !ioCode )
	{
		return EM9636_FAILURE;
	}

	if( !pDev->ioInFifo )
	{
		return EM9636_FAILURE;
	}

	I32 adChCount = pDev->adPara.endChNo - pDev->adPara.beginChNo + 1;
	if( adChCount < 0 )
		return EM9636_FAILURE;

	I32 ioInx = 0;
	for( I32 i = adChCount; i < codeCount; i+= adChCount + 1 )
	{
		ioCode[ioInx++] = usCode[i];
	}
	if( ioCodeCount )
		*ioCodeCount = ioInx;

	return EM9636_SUCCESS;
}

I32 _stdcall EM9636_AdGetCode( EM9636_DevPara* hDevice, U16* usCode, I32 codeCount, U16* adCode, I32* adCodeCount )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	if( !usCode || !adCode )
	{
		return EM9636_FAILURE;
	}

	if( !pDev->ioInFifo )
	{
		memcpy( adCode, usCode, codeCount * sizeof(U16) );
		if( adCodeCount )
			*adCodeCount = codeCount;
		return EM9636_SUCCESS;
	}

	I32 adChCount = pDev->adPara.endChNo - pDev->adPara.beginChNo + 1;
	if( adChCount <= 0 )
		return EM9636_FAILURE;

	I32 adInx = 0;
	for( I32 i = 0; i < codeCount; i+= adChCount + 1 )
	{
		for( I32 j = 0; j < adChCount; ++j )
			adCode[adInx++] = usCode[i+j];
	}
	if( adCodeCount )
		*adCodeCount = adInx;

	return EM9636_SUCCESS;
}

I32 AdGetValue(  I32 rangeInx, U16* usCode, I32 codeCount, double* adValue )
{
	double minVal,maxVal;
	I32 ret = AdGetRangeMaxMin( rangeInx, &maxVal, &minVal );
	if( ret < 0 )
		return ret;

	if( !usCode || !adValue )
	{
		return EM9636_FAILURE;
	}

	//	V_U16 abc(codeCount);

	for( I32 i = 0; i < codeCount; ++i)
	{
		adValue[i] = usCode[i] * (maxVal - minVal)
			/ 65535	+ minVal;
		//		abc[i] = usCode[i];
	}

	return EM9636_SUCCESS;
}

I32 _stdcall EM9636_AdGetValue( EM9636_DevPara* hDevice, U16* usCode, I32 codeCount, double* adValue )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	return AdGetValue( pDev->adPara.rangeInx, usCode, codeCount, adValue );
}

I32 _stdcall EM9636_HcSetChFreq( EM9636_DevPara* hDevice,  F64 chFreq, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	if( chFreq < 1 || chFreq > 250000 )
		return EM9636_FAILURE;
	U32 freqDiv = (U32)(EM9636_BASE_FREQ / chFreq);
	V_I8 vc(4);
	vc[0] = (freqDiv >> 8) & 0xff;
	vc[1] = freqDiv & 0xff;
	vc[2] = (freqDiv >> 24) & 0xff;
	vc[3] = (freqDiv >> 16) & 0xff;

	I32 ret = ZTLC_SendAndVerify( pDev->hCmd, 18, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	pDev->chFreq = chFreq;

	return EM9636_SUCCESS;
}

I32 _stdcall EM9636_HcSetGroupFreq( EM9636_DevPara* hDevice,  F64 groupFreq, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	if( groupFreq < 1 || groupFreq > 250000 )
		return EM9636_FAILURE;
	U32 freqDiv = (U32)(EM9636_BASE_FREQ / groupFreq);
	V_I8 vc(4);
	vc[0] = (freqDiv >> 8) & 0xff;
	vc[1] = freqDiv & 0xff;
	vc[2] = (freqDiv >> 24) & 0xff;
	vc[3] = (freqDiv >> 16) & 0xff;

	I32 ret = ZTLC_SendAndVerify( pDev->hCmd, 16, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	pDev->groupFreq = groupFreq;

	return EM9636_SUCCESS;
}

I32 SendStartOrStop( EM9636_DevPara* pDev, I32 isPSync, I32 startMode, I32 timeOutMS )
{
	V_I8 vc(2);
	vc[0] = pDev->adPara.endMode & 0xff;
	if( startMode )
		vc[1] = (startMode | (isPSync<<2) | (pDev->triSrc<<3) | (pDev->triMode<<4)) & 0xff;
	else
		vc[1] = 0;
	I32 ret = ZTLC_SendAndVerify( pDev->hCmd, 22, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	pDev->isHcStart = startMode ? true : false;
	pDev->startMode = startMode;
	pDev->isPSync = isPSync;

	return 0;
}

I32 _stdcall EM9636_TriSetSrc( EM9636_DevPara* hDevice, I32 triSrc, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	if( triSrc != EM9636_TRI_IN && triSrc != EM9636_TRI_EXTERN )
		return EM9636_FAILURE;
	pDev->triSrc = triSrc & 1;

	return EM9636_SUCCESS;
	//	return SendStartOrStop( pDev, 0, startMode & 3, timeOutMS );
}

I32 _stdcall EM9636_TriSetMode( EM9636_DevPara* hDevice, I32 triMode, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	if( triMode < EM9636_TRI_UPEDGE || triMode > EM9636_TRI_LOWLEVEL )
		return EM9636_FAILURE;
	pDev->triMode = triMode & 3;

	return EM9636_SUCCESS;
}

I32 SetInFifo( EM9636_DevPara* pDev, I32 timeOutMS )
{
	V_I8 vc(2, 0);
	vc[1] = pDev->ioInFifo | (pDev->diInFifo << 1) |
		(pDev->ecInFifol16[0] << 2) | (pDev->ecInFifoh16[0] << 3) |
		(pDev->ecInFifol16[1] << 4) | (pDev->ecInFifol16[1] << 5) |
		(pDev->ctInFifo[0] << 6) | (pDev->ctInFifo[1] << 7);
	vc[0] = (pDev->ctInFifo[2] << 0) | (pDev->ctInFifo[3] << 1) |
		(pDev->ctInFifo[4] << 2) | (pDev->ctInFifo[5] << 3);

	I32 ret = ZTLC_SendAndVerify( pDev->hCmd, 35, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;
	return 0;
}

I32 _stdcall EM9636_HcStart( EM9636_DevPara* hDevice, I32 isPSync, I32 clkSrc, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	I32 startMode;
	if( clkSrc )
		startMode = 2;
	else
		startMode = 1;

	I32 ret = SetInFifo( pDev, timeOutMS );
	if( ret < 0 )
		return ret;

	return SendStartOrStop( pDev, isPSync & 1, startMode & 3, timeOutMS );
//	return SendStartOrStop( pDev, 0, startMode & 3, timeOutMS );
}

I32 _stdcall EM9636_HcStop( EM9636_DevPara* hDevice, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	return SendStartOrStop( pDev, 0, 0, timeOutMS );
}

I32 _stdcall EM9636M_HcFifoStatus( EM9636_DevPara* hDevice, I32* hFifoStatus, I32* sFifoStatus, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	V_I8 vc(2);
	I32 ret = ZTLC_RecvAndVerify( pDev->hCmd, 155, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	if( hFifoStatus )
		*hFifoStatus = vc[1] & 1;
	if( sFifoStatus )
		*sFifoStatus = (vc[1]>>1) & 1;
	return 0;
}

I32 _stdcall EM9636_HcReadData( EM9636_DevPara* hDevice, I32 dataCount, U16* dataBuffer, I32* realReadCount, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	if( !pDev->dataFd )
		return EM9636_CONNECT_ERROR;
	U32 dataBC = dataCount * 2;
	if( dataBC < 0 )
	{
		printf( "%s,dataBC < 0:%u\n", __FUNCTION__, (unsigned int)dataBC );
		return EM9636_FAILURE;
	}
	struct timeval timeout;
	timeout.tv_sec = timeOutMS / 1000;
	timeout.tv_usec = (timeOutMS % 1000) * 1000000;
	//设定接收超时时间
	if( setsockopt( pDev->dataFd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout) ) == SOCKET_ERROR )
	{
		printf("%s,setsockopt,%s\n", __FUNCTION__, strerror(errno));
		int err = errno;
		if (err == ECONNRESET)
			return EM9636_CONNECT_ERROR;
		else
		{
			return EM9636_FAILURE;
		}
	}

	I32 leftBC = dataBC;
	I32 readBC = 0;
	CTimeInterval tv;
	do{
		int retv = recv( pDev->dataFd, (char*)dataBuffer + readBC, leftBC, 0 );
		if( retv < 0 )
		{
			int err = errno;
			if( err == ETIMEDOUT  )
			{
				return EM9636_TIMEOUT_ERROR;
			}
			else
			{
				if( err == ECONNRESET  )
					return EM9636_CONNECT_ERROR;
				else
					return EM9636_FAILURE;
			}
		}else if( retv == 0 ){
			return EM9636_CONNECT_ERROR;
		}
		readBC += retv;
		leftBC -= retv;
	}while( tv.GetIntervalMS() < timeOutMS && leftBC > 0);

/*	V_U16 tt(dataCount);
	memcpy( &tt[0], dataBuffer, dataBC );*/

	if( realReadCount )
		*realReadCount = readBC / 2;

	//	TRACE( "EM9636_HCReadData:%d\n", retv );

	return EM9636_SUCCESS;
}

bool DaChIsRight( long chNo )
{
	return 1 <= chNo && chNo <= 4;
}

I32 _stdcall EM9636_DaSetOutMode( EM9636_DevPara* hDevice, I32 chNo, I32 codeOrVal, long rangeInx, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	if( !DaChIsRight( chNo ) )
		return EM9636_FAILURE;
	V_I8 vc(2);
	vc[0] = codeOrVal & 1;
	vc[1] = rangeInx & 0xff;

	I32 chInx = chNo - 1;
	I32 ret = ZTLC_SendAndVerify( pDev->hCmd, 58 + (U16)chInx * 2, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	return EM9636_SUCCESS;
}

I32 _stdcall EM9636_DaSet( EM9636_DevPara* hDevice, I32 chNo, I16 daValue, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	if( !DaChIsRight( chNo ) )
		return EM9636_FAILURE;

	V_I8 vc(2);
	vc[0] = (daValue>>8) & 0xff;
	vc[1] = daValue & 0xff;

	I32 chInx = chNo - 1;
	I32 ret = ZTLC_SendAndVerify( pDev->hCmd, 26 + (U16)chInx * 2, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	return EM9636_SUCCESS;
}

I32 _stdcall EM9636_DaAutoSet( EM9636_DevPara* hDevice, I16 daValue[4], I32 stepCnt, I32 stepTime, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	if( daValue == 0 )
		return EM9636_FAILURE;

	if( stepCnt < 32 || stepCnt > 1000 )
		return EM9636_FAILURE;
	if( stepTime < 1 || stepTime > 100 )
		return EM9636_FAILURE;

	V_I8 vc(12, 0);
	for( I32 i = 0; i < 4; ++i )
	{
		vc[i * 2] = (daValue[i]>>8) & 0xff;
		vc[i * 2 + 1] = daValue[i] & 0xff;
	}

	vc[8] = (stepCnt>>8) & 0xff;
	vc[9] = (stepCnt) & 0xff;
	vc[10] = (stepTime>>8) & 0xff;
	vc[11] = (stepTime) & 0xff;

	I32 ret = ZTLC_SendAndVerify( pDev->hCmd, 1024, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	return EM9636_SUCCESS;
}

I32 _stdcall EM9636_DaAutoGet( EM9636_DevPara* hDevice, I16 daValue[4], I32* stepCnt, I32* stepTime, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	V_I8 vc(12);

	I32 ret = ZTLC_RecvAndVerify( pDev->hCmd, 1024, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	if( daValue )
		for( I32 i = 0; i < 4; ++i )
		{
			daValue[i] = vc[i*2+1] | (vc[i*2]<<8);
		}

	if( stepCnt )
		*stepCnt = (vc[8] << 8) | vc[9];
	if( stepTime )
		*stepTime = (vc[10] << 8) | vc[11];

	return EM9636_SUCCESS;
}

I32 _stdcall EM9636_IoSetDir( EM9636_DevPara* hDevice, I8 dir[4], I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	//注意：通用产品只有dir[0]和dir[1]有效
	I8 dirAll = 0;
	for( int i = 0; i < 4; ++i )
	{
		if( dir[i] )
			dirAll |= 1 << i;
	}
	V_I8 vc(2);
	vc[0] = 0;
	vc[1] = dirAll;

	I32 ret = ZTLC_SendAndVerify( pDev->hCmd, 34, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	return EM9636_SUCCESS;
}

I32 _stdcall EM9636_IoGetAll( EM9636_DevPara* hDevice, I8 iStatus[32], I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	//iStatus[0]~iStatus[15]对应IO1~IO16
	//iStatus[16]~iStatus[23]对应DI1~DI8
	//iStatus[24]~iStatus[31]对应DO1~DO8
	V_I8 vc(4);
	I32 ret = ZTLC_RecvAndVerify( pDev->hCmd, 300, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	//将开关量顺序调换成小端排列
	I8 temp;
	temp = vc[0]; vc[0] = vc[1]; vc[1] = temp;
	temp = vc[2]; vc[2] = vc[3]; vc[3] = temp;
	//	MyTrace( "%2x ", vc );

	for( U32 i = 0; i < vc.size(); ++i )
	{
		for( I32 j = 0; j < 8; ++j )
		{
			I32 chInx = i * 8 + j;
			iStatus[chInx] = (vc[i] >> j) & 1;
		}
	}

	return EM9636_SUCCESS;
}

I32 _stdcall EM9636_IoSetAll( EM9636_DevPara* hDevice, I8 iStatus[32], I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	//iStatus[0]~iStatus[15]对应IO1~IO16
	//iStatus[16]~iStatus[23]保留
	//iStatus[24]~iStatus[31]对应DO1~DO8
	V_I8 vc(4, 0);
	for( U32 i = 0; i < vc.size(); ++i )
	{
		for( I32 j = 0; j < 8; ++j )
		{
			I32 chInx = i * 8 + j;
			vc[i] |= iStatus[chInx] << j;
		}
	}
	reverse( vc.begin(), vc.end() );

	I32 ret = ZTLC_SendAndVerify( pDev->hCmd, 36, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	return EM9636_SUCCESS;
}

I32 _stdcall EM9636_IoInFifo( EM9636_DevPara* hDevice, I8 isInFifo, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	V_I8 vc(2, 0);
	vc[1] = isInFifo & 1;

	I32 ret = ZTLC_SendAndVerify( pDev->hCmd, 35, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;
	pDev->ioInFifo = isInFifo & 1;

	return EM9636_SUCCESS;
}

I32 _stdcall EM9636_DiInFifo( EM9636_DevPara* hDevice, I8 isInFifo )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	pDev->diInFifo = isInFifo & 1;

	return EM9636_SUCCESS;
}

I32 _stdcall EM9636_EcInFifo( EM9636_DevPara* hDevice, I8 l16isInFifo[EM9636_MAXECCHCNT], I8 h16isInFifo[EM9636_MAXECCHCNT] )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	for( I32 i = 0; i < EM9636_MAXECCHCNT; ++i )
	{
		pDev->ecInFifol16[i] = l16isInFifo[i] & 1;
		pDev->ecInFifoh16[i] = h16isInFifo[i] & 1;
	}

	return EM9636_SUCCESS;
}

I32 _stdcall EM9636_CtInFifo( EM9636_DevPara* hDevice, I8 isInFifo[EM9636_MAXCTCHCNT] )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	for( I32 i = 0; i < EM9636_MAXCTCHCNT; ++i )
	{
		pDev->ctInFifo[i] = isInFifo[i] & 1;
	}

	return EM9636_SUCCESS;
}

I32 _stdcall EM9636_EcClear( EM9636_DevPara* hDevice, I32 chNo, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	V_I8 vc(2, 0);
	vc[0] = 0;
	vc[1] = 1 << (chNo - 1);

	I32 ret = ZTLC_SendAndVerify( pDev->hCmd, 193, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	return EM9636_SUCCESS;
}

I32 _stdcall EM9636_EcClearAll( EM9636_DevPara* hDevice, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	V_I8 vc(2, 255);
	I32 ret = ZTLC_SendAndVerify( pDev->hCmd, 193, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	return EM9636_SUCCESS;
}

I32 _stdcall EM9636_EcReadCodeAll( EM9636_DevPara* hDevice, I32 abCode[EM9636_MAXECCHCNT], I16 zCode[EM9636_MAXECCHCNT], I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	V_I8 vc(sizeof(I32) * 2 * EM9636_MAXECCHCNT);

	I32 ret = ZTLC_RecvAndVerify( pDev->hCmd, 302, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	//	MyTrace( "%2x", vc );
	memset( abCode, 0, sizeof(I32) * EM9636_MAXECCHCNT );
	memset( zCode, 0, sizeof(I16) * EM9636_MAXECCHCNT );//2015-12-3 ZCD,之前是I32
	I32 vcInx = 0;
	for( I32 codeInx = 0; codeInx < EM9636_MAXECCHCNT; ++codeInx )
	{
		//得到AB值
		abCode[codeInx] |= vc[vcInx];
		for( I32 byteInx = 1; byteInx < 4; ++byteInx )
		{
			abCode[codeInx] <<= 8;
			++vcInx;
			abCode[codeInx] |= (U8)vc[vcInx];
		}
		//得到Z值
		vcInx += 3;
		zCode[codeInx] = ((vc[vcInx]&0xff) << 8) | (vc[vcInx + 1]&0xff);
		vcInx += 2;
	}
	return 0;
}


I32 _stdcall EM9636_CtSetModeAll( EM9636_DevPara* hDevice, U16 ctMode[EM9636_MAXCTCHCNT], I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	U16 ctModeAll = 0;
	I32 ctSize = sizeof(U16) * EM9636_MAXCTCHCNT;
	for( I32 i = 0; i < ctSize; ++i )
	{
		ctModeAll |= (ctMode[i] & 3) << (i*2);
	}
	V_I8 vc(2, 0);
	vc[0] = (ctModeAll>>8) & 0xff;
	vc[1] = ctModeAll & 0xff;
	I32 ret = ZTLC_SendAndVerify( pDev->hCmd, 52, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	memcpy( pDev->ctPara.mode, ctMode, ctSize );

	return 0;
}

bool IsCtChRight( I32 chNo )
{
	return 1 <= chNo && chNo <= 6;
}

I32 _stdcall EM9636_CtSetFreqBase( EM9636_DevPara* hDevice, I32 chNo, F64 freqBase_ms, F64* real_ms, I32 timeOutMS )
{
	if( !IsCtChRight( chNo ) )
		return EM9636_FAILURE;
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	U32 div = (U32)(EM9636_BASE_FREQ / (1000.0 / freqBase_ms));
	V_I8 vc(4, 0);
	vc[0] |= ((div >> 24) & 0xff);
	vc[1] |= ((div >> 16) & 0xff);
	vc[2] |= ((div >> 8) & 0xff);
	vc[3] |= (div & 0xff);
	I32 ret = ZTLC_SendAndVerify( pDev->hCmd, (U16)(40 + (chNo - 1) * 2), &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	I32 chInx = chNo - 1;
	pDev->ctPara.freqBase[chInx] = 1000.0 / (EM9636_BASE_FREQ / div);
	if( real_ms )
		*real_ms = pDev->ctPara.freqBase[chInx];
	return 0;
}

I32 _stdcall EM9636_CtReadCodeAll( EM9636_DevPara* hDevice, U32 ctCode[EM9636_MAXCTCHCNT], I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	V_I8 vc(sizeof(U32) * EM9636_MAXCTCHCNT);
	I32 ret = ZTLC_RecvAndVerify( pDev->hCmd, 288, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	//	MyTrace( "%2x", vc );
	memset( ctCode, 0, (U32)vc.size() );
	I32 vcInx = 0;
	for( I32 codeInx = 0; codeInx < EM9636_MAXCTCHCNT; ++codeInx )
	{
		ctCode[codeInx] |= vc[vcInx];
		for( I32 byteInx = 1; byteInx < 4; ++byteInx )
		{
			ctCode[codeInx] <<= 8;
			++vcInx;
			ctCode[codeInx] |= (U8)vc[vcInx];
		}
		++vcInx;
		ctCode[codeInx] &= 0xffff;
		if( ctCode[codeInx] > 100 )
			vcInx = vcInx;
	}
	return 0;
}

I32 _stdcall EM9636_CtCodeToValue( EM9636_DevPara* hDevice, I32 chNo, U32 ctCode, F64* ctValue )
{
	if( !IsCtChRight( chNo ) )
		return EM9636_FAILURE;
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	F64 v;
	I32 chInx = chNo - 1;
	switch( pDev->ctPara.mode[chInx] )
	{
	case EM9636_CT_MODE_COUNT:
		v = ctCode;
		break;
	case EM9636_CT_MODE_HFREQ:
		v = 1000.0 * ctCode / ( pDev->ctPara.freqBase[chInx] );
		break;
	case EM9636_CT_MODE_LFREQ:
		if(ctCode)
			v = 1000.0 / ( pDev->ctPara.freqBase[chInx] * ctCode );
		else
			v = 0;
		break;
	default:
		v = 0;
	}
	if( ctValue )
		*ctValue = v;
	return 0;
}

I32 _stdcall EM9636_CtBatchCodeToValue( EM9636_DevPara* hDevice, I32 chNo, U32 codesCount, U32* ctCode, F64* ctValue )
{
	if( !IsCtChRight( chNo ) )
		return EM9636_FAILURE;
	if( hDevice == 0 )
		return EM9636_FAILURE;
	if( !ctCode || !ctValue )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	I32 chInx = chNo - 1;
	switch( pDev->ctPara.mode[chInx] )
	{
	case EM9636_CT_MODE_COUNT:
		for( U32 i = 0; i < codesCount; ++i )
			ctValue[i] = ctCode[i];
		break;
	case EM9636_CT_MODE_HFREQ:
		for( U32 i = 0; i < codesCount; ++i )
			ctValue[i] = 1000.0 * ctCode[i] / ( pDev->ctPara.freqBase[chInx] );
		break;
	case EM9636_CT_MODE_LFREQ:
		for( U32 i = 0; i < codesCount; ++i )
			if(ctCode[i])
				ctValue[i] = 1000.0 / ( pDev->ctPara.freqBase[chInx] * ctCode[i] );
			else
				ctValue[i] = 0;
		break;
	default:
		memset( ctValue, 0, sizeof(F64) * codesCount );
	}
	return 0;
}

I32 _stdcall EM9636_CtClear( EM9636_DevPara* hDevice, I32 chNo, I32 timeOutMS )
{
	if( !IsCtChRight(chNo) )
		return EM9636_FAILURE;
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	I32 chInx = chNo - 1;
	F64 tempBase = pDev->ctPara.freqBase[chInx];
	EM9636_CtSetFreqBase( pDev, chNo, 1, 0 );
	pDev->ctPara.mode[chInx] = 1;
	EM9636_CtSetModeAll( pDev, pDev->ctPara.mode );
	usleep(2000);
	pDev->ctPara.mode[chInx] = 0;
	EM9636_CtSetModeAll( pDev, pDev->ctPara.mode );
	usleep(2000);
	EM9636_CtSetFreqBase( pDev, chNo, tempBase, 0 );

	return 0;
}

I32 _stdcall EM9636_CmdEnableWTD( EM9636_DevPara* hDevice, U16 overTimeS, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	V_I8 vc(2);
	vc[0] = (overTimeS >> 8) & 0xff;
	vc[1] = overTimeS & 0xff;

	I32 ret = ZTLC_SendAndVerify( pDev->hCmd, 180, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;
	return 0;
}

bool IsPwmChRight( I32 chNo )
{
	return 0 < chNo && chNo <= EM9636_MAXPWMCHCNT;
}

I32 _stdcall EM9636_PwmSetPulse( EM9636_DevPara* hDevice, I32 chNo, F64 freq, F64 duty, F64* realFreq, F64* realDuty, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	if( !IsPwmChRight(chNo) )
		return EM9636_FAILURE;
	U16 pwmFreqDiv = 0;
	if( freq > 0 )
		pwmFreqDiv = (U16)(EM9636_BASE_FREQ / freq);//得到分频系数

	if( realFreq )
		if( pwmFreqDiv > 0 )
			*realFreq = EM9636_BASE_FREQ / pwmFreqDiv;
		else
			*realFreq = 0;

	if( duty < 0 || duty > 1 )
		return EM9636_FAILURE;

	U16 pwmDutyHight = (U16)(pwmFreqDiv * duty);//得到高电平系数

	V_I8 vc(6, 0);
	vc[0] = 0;
	vc[1] = (I8)chNo - 1;
	vc[2] = pwmFreqDiv / 256;
	vc[3] = pwmFreqDiv & 0xff;
	vc[4] = pwmDutyHight / 256;
	vc[5] = pwmDutyHight & 0xff;

	I32 ret = ZTLC_SendAndVerify( pDev->hCmd, 194, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	if( realDuty )
		if( pwmFreqDiv )
			*realDuty = pwmDutyHight / pwmFreqDiv;
		else
			*realDuty = 0;

	return 0;
}

I32 _stdcall EM9636_PwmSet1Pulse32bit( EM9636_DevPara* hDevice, I32 chNo, F64 freq, F64 duty, F64* realFreq, F64* realDuty, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	if( !IsPwmChRight(chNo) )
		return EM9636_FAILURE;
	U32 pwmFreqDiv = 0;
	if( freq > 0 )
		pwmFreqDiv = (U32)(EM9636_BASE_FREQ / freq);//得到分频系数

	if( realFreq )
		if( pwmFreqDiv > 0 )
			*realFreq = EM9636_BASE_FREQ / pwmFreqDiv;
		else
			*realFreq = 0;

	if( duty < 0 || duty > 1 )
		return EM9636_FAILURE;

	U32 pwmDutyHight = (U32)(pwmFreqDiv * duty);//得到高电平系数

	V_I8 vc(6, 0);
	vc[0] = 0;
	vc[1] = 0;//(I8)chNo - 1;
	//low 16bit
	vc[2] = (pwmFreqDiv >> 8) & 0xff;
	vc[3] = pwmFreqDiv & 0xff;
	vc[4] = (pwmDutyHight >> 8) & 0xff;
	vc[5] = pwmDutyHight & 0xff;

	I32 ret = ZTLC_SendAndVerify( pDev->hCmd, 194, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;
	//hight 16bit
	vc[1] = 1;//(I8)chNo - 1;
	vc[2] = (pwmFreqDiv >> 24) & 0xff;
	vc[3] = (pwmFreqDiv >> 16) & 0xff;
	vc[4] = (pwmDutyHight >> 24) & 0xff;
	vc[5] = (pwmDutyHight >> 16) & 0xff;

	ret = ZTLC_SendAndVerify( pDev->hCmd, 194, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	if( realDuty )
		if( pwmFreqDiv )
			*realDuty = pwmDutyHight / pwmFreqDiv;
		else
			*realDuty = 0;

	return 0;
}

//使能或禁止PWM输出，目前只能全部使能和全部禁止
I32 _stdcall EM9636_PwmStartOrStopAll( EM9636_DevPara* hDevice, I8 startOrStop, I32 timeOutMS  )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	V_I8 vc(2, 0);
	vc[0] = 0;
	vc[1] = startOrStop ? 7 : 0;

	I32 ret = ZTLC_SendAndVerify( pDev->hCmd, 197, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	return 0;
}

I32 _stdcall EM9636M_PwmStartAll( EM9636_DevPara* hDevice, I8 startOrStop[EM9636_MAXPWMCHCNT], I8 is90[EM9636_MAXPWMCHCNT], I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	V_I8 vcStart(2, 0), vcIs90(2, 0);
	for( int i = 0; i < EM9636_MAXPWMCHCNT; ++i )
	{
		startOrStop[i] &= 1;
		vcStart[1] |= (startOrStop[i] << i);
		is90[i] &= 1;
		vcIs90[1] |= (is90[i] << i);
	}

	ZTLC_SendAndVerify( pDev->hCmd, 200, &vcIs90[0], (U32)vcIs90.size(), timeOutMS );
	I32 ret = ZTLC_SendAndVerify( pDev->hCmd, 197, &vcStart[0], (U32)vcStart.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	return 0;
}

I32 _stdcall EM9636M_PwmSetCount( EM9636_DevPara* hDevice, I32 chNo, U32 pwmCount, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;
	if( !pDev )
		return EM9636_FAILURE;
	if( !IsPwmChRight( chNo ) )
		return EM9636_FAILURE;
	V_I8 vc(4, 0);
	vc[1] = (chNo-1) & 0xff;
	vc[2] = (pwmCount>>8) & 0xff;
	vc[3] = pwmCount & 0xff;
	I32 ret = ZTLC_SendAndVerify( pDev->hCmd, 198, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	return EM9636_SUCCESS;
}

//PWM脉冲是否输出到指定个数
I32 _stdcall EM9636M_PwmIsOver( EM9636_DevPara* hDevice, I8 isOver[EM9636_MAXPWMCHCNT], I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	V_I8 vc(2);
	I32 ret = ZTLC_RecvAndVerify( pDev->hCmd, 197, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;
	if( isOver )
		for( int i = 0; i < EM9636_MAXPWMCHCNT; ++i )
		{
			isOver[i] = (vc[1] >> i) & 1;
		}

		return 0;
}

I32 _stdcall EM9636_ReadW( EM9636_DevPara* hDevice, U32 regAddress, U32* regData, I32 timeOutMS  )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	V_I8 vc(4, 0);
	vc[0] = (regAddress >> 24) & 0xff;
	vc[1] = (regAddress >> 16) & 0xff;
	vc[2] = (regAddress >> 8) & 0xff;
	vc[3] = (regAddress) & 0xff;
	I32 ret = ZTLC_SendAndVerify( pDev->hCmd, 100, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	ret = ZTLC_RecvAndVerify( pDev->hCmd, 102, &vc[0], 2, timeOutMS );
	if( ret < 0 )
		return ret;
	if( regData )
	{
		*regData = (U32(vc[0]&0xff) << 8) | U32(vc[1]&0xff);
	}
	return 0;
}


I32 _stdcall EM9636_WriteW( EM9636_DevPara* hDevice, U32 regAddress, U32 regData, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	V_I8 vc(6, 0);
	vc[0] = (regAddress >> 24) & 0xff;
	vc[1] = (regAddress >> 16) & 0xff;
	vc[2] = (regAddress >> 8) & 0xff;
	vc[3] = (regAddress) & 0xff;
	vc[4] = (regData >> 8) & 0xff;
	vc[5] = (regData) & 0xff;
	I32 ret = ZTLC_SendAndVerify( pDev->hCmd, 103, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	return 0;
}

inline I32 GetGroupBytesCount( OfflineFile* p )
{//High speed
	if( p->os.startMode == 0 )
		return 0;
	U32 adChCnt = p->os.adEndCh - p->os.adBeginCh + 1;
	if( adChCnt > EM9636_MAXADCHCNT )
		return 0;
	U32 ioInFifo = p->os.ioInFifo & 1;
	p->adChCnt = adChCnt + ioInFifo;
	return p->adChCnt * 2;
}

inline I32 GetLsGroupBytesCount( OfflineFile* p )
{//Low speed
	U32 i = 0;
	p->lsAdChCnt = 0;
	for( i = 0; i < EM9636_MAXADCHCNT; ++i )
		if( p->os.ad[i] )
			++p->lsAdChCnt;

	p->lsCtChCnt = 0;
	for( i = 0; i < EM9636_MAXCTCHCNT; ++i )
		if( p->os.ct[i] )
			++p->lsCtChCnt;

	p->lsIoGroupCnt = 0;
	for( i = 0; i < 4; ++i )
		if( p->os.io[i] )
			++p->lsIoGroupCnt;

	p->lsEcChCnt = 0;
	for( i = 0; i < EM9636_MAXECCHCNT; ++i )
		if( p->os.ec[i] )
			++p->lsEcChCnt;

	return p->lsAdChCnt * 2 + p->lsCtChCnt * 4 + p->lsIoGroupCnt + p->lsEcChCnt * 8;
}

I32 _stdcall EM9636_OlFileOpen( I8* filePathName )
{
	FILE* f = fopen( filePathName, "rb" );
	if ( !f ) {
		return 0;
	}
	OfflineSet os;
	I32 filePos = 0;
	fread( &os.version, 1, sizeof(os.version), f );//2
	filePos +=  sizeof(os.version);
	fread( &os.version, 1, sizeof(os.version), f );//2
	filePos +=  sizeof(os.version);
	fread( &os.intervalMS, 1, sizeof(os.intervalMS), f );//2
	filePos += sizeof(os.intervalMS);
	fread( &os.intervalS, 1, sizeof(os.intervalS), f );//1
	filePos += sizeof(os.intervalS);
	fread( &os.intervalM, 1, sizeof(os.intervalM), f );//1
	filePos += sizeof(os.intervalM);
	fread( &os.intervalH, 1, sizeof(os.intervalH), f );//1
	filePos += sizeof(os.intervalH);
	fread( &os.daqStyle, 1, sizeof(os.daqStyle), f );//1
	filePos += sizeof(os.daqStyle);
	fread( &os.startMode, 1, sizeof(os.startMode), f );//1
	filePos += sizeof(os.startMode);
	fread( &os.groupCount, 1, sizeof(os.groupCount), f );//4
	filePos += sizeof(os.groupCount);
	fread( &os.isPSync, 1, sizeof(os.isPSync), f );//4
	filePos += sizeof(os.isPSync);
	fread( &os.chFreq, 1, sizeof(os.chFreq), f );//4
	filePos += sizeof(os.chFreq);
	fread( &os.groupFreq, 1, sizeof(os.groupFreq), f );//4
	filePos += sizeof(os.groupFreq);
	fread( &os.adBeginCh, 1, sizeof(os.adBeginCh), f );//1
	filePos += sizeof(os.adBeginCh);
	fread( &os.adEndCh, 1, sizeof(os.adEndCh), f );//1
	filePos += sizeof(os.adEndCh);
	fread( &os.adRange, 1, sizeof(os.adRange), f );//1
	filePos += sizeof(os.adRange);
	fread( &os.adGain, 1, sizeof(os.adGain), f );//1
	filePos += sizeof(os.adGain);
	fread( &os.adEndMode, 1, sizeof(os.adEndMode), f );//1
	filePos += sizeof(os.adEndMode);
	fread( &os.ioInFifo, 1, sizeof(os.ioInFifo), f );//1
	filePos += sizeof(os.ioInFifo);
	fread( &os.ioDir, 1, sizeof(os.ioDir), f );//4
	filePos += sizeof(os.ioDir);
	fread( &os.ctMode, 1, sizeof(os.ctMode), f );//6
	filePos += sizeof(os.ctMode);
	fread( &os.ctGateFreq, 1, sizeof(os.ctGateFreq), f );//24
	filePos += sizeof(os.ctGateFreq);
	fread( &os.ad, 1, sizeof(os.ad), f );//32
	filePos += sizeof(os.ad);
	fread( &os.io, 1, sizeof(os.io), f );//4
	filePos += sizeof(os.io);
	fread( &os.ct, 1, sizeof(os.ct), f );//4
	filePos += sizeof(os.ct);
	fread( &os.ec, 1, sizeof(os.ec), f );//2
	filePos += sizeof(os.ec);

/*	for( I32 i = 0; i < EM9636_ADCH_COUNT * 2; i+=2 )
	{
		I32 chInx = i / 2;
		fread( &os.zCode[chInx], 1, sizeof(I16), f );
		fread( &os.fCode[chInx], 1, sizeof(I16), f );
	}*/

	size_t ss = sizeof( os );
	OfflineFile* of = new OfflineFile;
	if( !of )
		return -1;
	of->f = f;
	of->dataBeginPos = ftell( f );
/*	if( of->dataBeginPos )
	{
		return -1;
	}*/
	fseek(f, 0, SEEK_END);
	of->dataSize = ftell(f) - of->dataBeginPos;
	if( of->dataSize < 0 )
		return -1;
	fseek( f, of->dataBeginPos, SEEK_SET );

	memcpy( &of->os, &os, sizeof(os) );

	GetGroupBytesCount( of );
	GetLsGroupBytesCount( of );
	
	return (I32)of;
}


void _stdcall EM9636_OlFileClose( I32 fileHANDLE )
{
    if( !fileHANDLE )
		return;
    OfflineFile *p = (OfflineFile*)fileHANDLE;
	fclose( p->f );
	delete p;
}

I32 _stdcall EM9636_OlGetAdEnCh( I32 fileHANDLE, I8 enCh[EM9636_MAXADCHCNT] )
{
    if( !fileHANDLE )
		return -1;
    OfflineFile *p = (OfflineFile*)fileHANDLE;

	I32 chCnt = 0;
	
	for( int i = 0; i < EM9636_MAXADCHCNT; ++i )
	{

		if( enCh )
			enCh[i] = p->os.ad[i];
		if( p->os.ad[i] )
			++chCnt;
	}

	return chCnt;
}

I32 _stdcall EM9636_OlGetAdChRange( I32 fileHANDLE, I32* beginChNo, I32* endChNo )
{
    if( !fileHANDLE )
		return -1;
    OfflineFile *p = (OfflineFile*)fileHANDLE;
	if( beginChNo )
		*beginChNo = p->os.adBeginCh;
	if( endChNo )
		*endChNo = p->os.adEndCh;
	I32 cnt = p->os.adEndCh - p->os.adBeginCh + 1;
	if( cnt < 1 || cnt > EM9636_MAXADCHCNT )
		return -1;
	return cnt;
}

I32 _stdcall EM9636_OlGetGroupFreq( I32 fileHANDLE, F64* groupFreq )
{
    if( !fileHANDLE )
		return -1;
    OfflineFile* p = (OfflineFile*)fileHANDLE;

	if( groupFreq )
		*groupFreq = p->os.groupFreq;

	return 0;
}

I32 _stdcall EM9636_OlGetOriginalCode( I32 fileHANDLE, I32 readPos, U32 bytesCount, U8* originalCode, U32* realBC )
{
    if( !fileHANDLE )
		return -1;
    OfflineFile *p = (OfflineFile*)fileHANDLE;

	if( readPos > p->dataSize )
		return -1;

	if( readPos >= 0 )
	{
		int ret = fseek( p->f, readPos + p->dataBeginPos, SEEK_SET );
		if( ret != 0 )
			return -1;
	}

	size_t siz = fread( originalCode, 1, bytesCount, p->f );

	if( realBC )
		*realBC = (U32)siz;
	return ftell( p->f );
}

I32 _stdcall EM9636_OlGetGroupBytesCount( I32 fileHANDLE )
{
    if( !fileHANDLE )
		return -1;
    OfflineFile *p = (OfflineFile*)fileHANDLE;
	return GetGroupBytesCount( p );
}

I32 _stdcall EM9636_OlGetLsGroupBytesCount( I32 fileHANDLE )
{
    if( !fileHANDLE )
		return -1;
    OfflineFile *p = (OfflineFile*)fileHANDLE;
	return GetLsGroupBytesCount( p );
}

I32 _stdcall EM9636_OlGetDataBytesCount( I32 fileHANDLE )
{
    if( !fileHANDLE )
		return -1;
    OfflineFile *p = (OfflineFile*)fileHANDLE;
	return p->dataSize;
}

I32 _stdcall EM9636_OlGetAdChCode( I32 fileHANDLE, I32 chInx, U32 bytesCount, U8* originalCode, U16* adChCode, U32* adCodeCount )
{
    if( !fileHANDLE || !originalCode  || !adChCode )
		return -1;
    OfflineFile *p = (OfflineFile*)fileHANDLE;

	if( chInx >= p->adChCnt )
		return -1;

	U16* adCode = (U16*)originalCode;
	I32 gBC = GetGroupBytesCount( p );
	U32 codeCount = bytesCount / gBC * p->adChCnt;
	U32 j = 0;
	for( U32 i = chInx; i < codeCount; i += p->adChCnt )
	{
		adChCode[j++] = adCode[i];
	}

	if( adCodeCount )
		*adCodeCount = j;
	return 0;
}

I32 _stdcall EM9636_OlAdGetValue( I32 fileHANDLE, U16* usCode, I32 codeCount, double* adValue )
{
    if( !fileHANDLE || !usCode  || !adValue )
		return -1;
    OfflineFile *p = (OfflineFile*)fileHANDLE;

	return AdGetValue( p->os.adRange, usCode, codeCount, adValue );
}

I32 _stdcall EM9636_OlGetIoInFifoCode( I32 fileHANDLE, U32 bytesCount, U8* originalCode, U16* ioCode, U32* ioCodeCount )
{
    if( !fileHANDLE || !originalCode  || !ioCode )
		return -1;
    OfflineFile *p = (OfflineFile*)fileHANDLE;

	if( !p->os.ioInFifo || !p->os.startMode )
		return -1;

	U16* adCode = (U16*)originalCode;
	I32 gBC = GetGroupBytesCount( p );
	U32 codeCount = bytesCount / gBC * p->adChCnt;
	U32 j = 0;
	for( U32 i = p->adChCnt - 1; i < codeCount; i += p->adChCnt )
	{
		ioCode[j++] = adCode[i];
	}

	if( ioCodeCount )
		*ioCodeCount = j;
	return 0;
}

I32 _stdcall EM9636_OlGetLsAdChCode( I32 fileHANDLE, I32 chInx, U32 bytesCount, U8* originalCode, U16* adCode, U32* adCodeCount )
{
    if( !fileHANDLE || !originalCode  || !adCode )
		return -1;
    OfflineFile *p = (OfflineFile*)fileHANDLE;

	if( p->os.startMode )
		return -1;

	I32 gBC = GetLsGroupBytesCount( p );
	U32 j = 0;
	for( U32 i = 0; i < bytesCount; i += gBC )
	{
		adCode[j++] = *(U16*)(originalCode + i + chInx * 2);
	}

	if( adCodeCount )
		*adCodeCount = j;
	return 0;
}

I32 _stdcall EM9636_OlGetLsIoGroupCode( I32 fileHANDLE, I32 groupInx, U32 bytesCount, U8* originalCode, U8* ioCode, U32* ioCodeCount )
{
    if( !fileHANDLE || !originalCode  || !ioCode )
		return -1;
    OfflineFile *p = (OfflineFile*)fileHANDLE;

	if( p->os.startMode && !p->os.groupCount )
		return -1;

	I32 gBC = GetLsGroupBytesCount( p );
	U32 j = 0;
	for( U32 i = p->lsAdChCnt * 2; i < bytesCount; i += gBC )
	{
		ioCode[j++] = *(originalCode + i + groupInx );
	}

	if( ioCodeCount )
		*ioCodeCount = j;
	return 0;
}

I32 _stdcall EM9636_OlGetLsCtChCode( I32 fileHANDLE, I32 chInx, U32 bytesCount, U8* originalCode, U32* ctCode, U32* ctCodeCount )
{
    if( !fileHANDLE || !originalCode  || !ctCode )
		return -1;
    OfflineFile *p = (OfflineFile*)fileHANDLE;

	if( p->os.startMode && !p->os.groupCount )
		return -1;

	I32 gBC = GetLsGroupBytesCount( p );
	U32 j = 0;
	for( U32 i = p->lsAdChCnt * 2 + p->lsIoGroupCnt; i < bytesCount; i += gBC )
	{
		ctCode[j++] = (*(U32*)(originalCode + i + chInx * 4)) & 0xffff;
	}

	if( ctCodeCount )
		*ctCodeCount = j;
	return 0;
}

F64 GetHGroupPeriodUS( OfflineFile *p )
{
	if( p->os.isPSync )
	{
		if( p->os.groupFreq )
			return 1000000.0 / p->os.groupFreq;
		else
			return 0;
	}else{
		I32 chCnt = GetGroupBytesCount( p ) / 2;
		if( p->os.chFreq )
			return 1000000.0 / p->os.chFreq * chCnt;
		else
			return 0;
	}
}

I32 _stdcall EM9636_OlGetLsPeriod( I32 fileHANDLE, U32* msPeriod )
{
    if( !fileHANDLE || !msPeriod )
		return -1;
    OfflineFile *p = (OfflineFile*)fileHANDLE;

	if( p->os.startMode )
	{
		*msPeriod = (U32)(GetHGroupPeriodUS( p ) / 1000.0 * p->os.groupCount);
		return 0;
	}

	*msPeriod = p->os.intervalH * 3600000 + p->os.intervalM * 60000 + p->os.intervalS * 1000 + p->os.intervalMS;

	return 0;
}

I32 _stdcall EM9636_OlGetLsEcChCode( I32 fileHANDLE, I32 chInx, U32 bytesCount, U8* originalCode, I32* abCode, I32* zCode, U32* ecCodeCount )
{
    if( !fileHANDLE || !originalCode  || !abCode )
		return -1;
    OfflineFile *p = (OfflineFile*)fileHANDLE;

	if( p->os.startMode && !p->os.groupCount )
		return -1;

	I32 gBC = GetLsGroupBytesCount( p );
	U32 j = 0;
	for( U32 i = p->lsAdChCnt * 2 + p->lsIoGroupCnt + p->lsCtChCnt * 4; i < bytesCount; i += gBC )
	{
		abCode[j++] = *(I32*)(originalCode + i + chInx * 8);
		if( zCode)
			zCode[j++] = *(I32*)(originalCode + i + chInx * 8 + 4);
	}

	if( ecCodeCount )
		*ecCodeCount = j;
	return 0;
}

I32 _stdcall EM9636_OlAdGetRange( I32 fileHANDLE, I8* rangeInx )
{
    if( !fileHANDLE )
		return -1;
    OfflineFile *p = (OfflineFile*)fileHANDLE;
	if( rangeInx )
		*rangeInx = p->os.adRange;

	return EM9636_SUCCESS;
}

I32 _stdcall EM9636_OlGetChFreq( I32 fileHANDLE, F64* chFreq )
{
    if( !fileHANDLE )
		return -1;
    OfflineFile* p = (OfflineFile*)fileHANDLE;

	if( chFreq )
		*chFreq = p->os.chFreq;

	return 0;
}

I32 _stdcall EM9636_OlGetIsPSync( I32 fileHANDLE, I32* isPSync )
{
    if( !fileHANDLE)
		return -1;
    OfflineFile* p = (OfflineFile*)fileHANDLE;

	if( isPSync )
		*isPSync = p->os.isPSync;

	return 0;
}

I32 _stdcall EM9636_OlGetCtEnCh( I32 fileHANDLE, I8* enCh )
{
    if( !fileHANDLE)
		return -1;
    OfflineFile *p = (OfflineFile*)fileHANDLE;
	if( enCh )
		memcpy( enCh, p->os.ct, sizeof(p->os.ct) );

	return 0;
}

I32 _stdcall EM9636_OlGetCtMode( I32 fileHANDLE, I8* ctMode )
{
    if( !fileHANDLE)
		return -1;
    OfflineFile *p = (OfflineFile*)fileHANDLE;
	if( ctMode )
		memcpy( ctMode, p->os.ctMode, sizeof(p->os.ctMode) );

	return 0;
}

I32 _stdcall EM9636_OlGetCtGate( I32 fileHANDLE, I32* ctGate )
{
    if( !fileHANDLE)
		return -1;
    OfflineFile *p = (OfflineFile*)fileHANDLE;
	if( ctGate )
		memcpy( ctGate, p->os.ctGateFreq, sizeof(p->os.ctGateFreq) );

	return 0;
}

I32 _stdcall EM9636_OlGetEcEnCh( I32 fileHANDLE, I8* enCh )
{
    if( !fileHANDLE)
		return -1;
    OfflineFile *p = (OfflineFile*)fileHANDLE;
	if( enCh )
		memcpy( enCh, p->os.ec, sizeof(p->os.ec) );

	return 0;
}

I32 _stdcall EM9636_OlGetIoEnCh( I32 fileHANDLE, I8* enCh )
{
    if( !fileHANDLE)
		return -1;
    OfflineFile *p = (OfflineFile*)fileHANDLE;
	if( enCh )
		memcpy( enCh, p->os.io, sizeof(p->os.io) );

	return 0;
}

I32 _stdcall EM9636_OlGetIoInFifo( I32 fileHANDLE, I8* ioInFifo )
{
    if( !fileHANDLE)
		return -1;
    OfflineFile *p = (OfflineFile*)fileHANDLE;
	if( ioInFifo )
		memcpy( ioInFifo, &p->os.ioInFifo, sizeof(p->os.ioInFifo) );

	return 0;
}

typedef struct EM9636_OLDIR
{
	FILE* f;
	I64 dataBeginPos;//数据开始位置
	I64 dataNowPos;//数据当前位置
	I64 dataSize;//数据总大小
	I32 fileCount;//数据文件个数
	V_STR fileName;//数据文件名数组，每个大小是1024
	OfflineSet os;
	I32 adChCnt;
}EM9636_OlDir;

int IsOlDir( const string& str )
{
	if( str.length() != 6 )
		return 0;
	for( size_t i = 0; i < str.length(); ++i )
	{
		if( str[i] < '0' || str[i] > '9'  )
			return 0;
	}
	return 1;
}

I32 _stdcall EM9636_OlDirOpen( I8* path )
{
/*	size_t len = strlen( path );
	if( path[len-1] == '\\' )
	{
		path[len] = '*';
		path[len+1] = 0;
	}else
	{
		path[len] = '\\';
		path[len+1] = '*';
		path[len+2] = 0;
	}
	EM9636_OlDir* pDir = new EM9636_OlDir;
	WIN32_FIND_DATA wd;
    EM9636_DevPara* h = FindFirstFile( path, &wd );

    if( h == INVALID_EM9636_DevPara*_VALUE )
	{
		return -1;
	}

	BOOL b;
	V_STR strDir;
	do
	{
		b = FindNextFile( h, &wd );
		DWORD dir = GetFileAttributes( wd.cFileName );
		if( dir == FILE_ATTRIBUTE_DIRECTORY )
		{
			if( IsOlDir( wd.cFileName ) )
				strDir.push_back( wd.cFileName );
		}
	}while( b );
//	判断问题

	if( !strDir.size() )
		return -1;*/

	return (I32)0;//pDir;
}

/*UINT __stdcall ReadThread( PVOID p)
{
	EM9636_DevPara* pDev = (EM9636_DevPara*)p;
	while( pDev->isHcStart )
	{
		I32 fifoStatus1, fifoStatus2;
		I32 ret = EM9636M_HcFifoStatus( pDev, &fifoStatus1, &fifoStatus2 );
		if( ret < 0 )
		{
			pDev->threadError = ret;
			break;
		}
		V_U16 retData( pDev->asCount / 2 );
		I32 realReadCount;
		ret = EM9636_HcReadData( pDev, (I32)retData.size(), &retData[0], &realReadCount );
		if( ret == EM9636_TIMEOUT_ERROR )
			continue;
		if( ret < 0 )
		{
			pDev->threadError = ret;
//			EM9636_DataClose( (I32)pDev );
//			EM9636_DataConnect( (I32)pDev, pDev->dataPort );
			break;
		}
		pDev->codeFifo.Write( (I8*)&retData[0], realReadCount * sizeof(U16) );

	}
	SetEvent( pDev->hReadThreadOver );
	//	_endthread();
	return 0;
}*/

//#pragma comment(lib,"ws2_32.lib")

/*I32 _stdcall EM9636M_HcStart( EM9636_DevPara* hDevice, I32 isPSync, I32 clkSrc, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;
	if( !pDev->dataFd )
	{
		I32 ret = EM9636_DataConnect( hDevice, pDev->dataPort );
		if( ret < 0 )
		{
			pDev->dataFd = 0;
			return EM9636_DATA_CONNECT_ERROR;d
		}
	}

	WSAIoctl(pDev->dataFd,SIO_FLUSH,NULL,0,NULL,0,NULL,NULL,NULL);
	pDev->codeFifo.Clear();
	pDev->isHcStart = 1;
    pDev->hReadThread = (EM9636_DevPara*)_beginthreadex(NULL, 0, ReadThread, pDev, 0, NULL);


	I32 startMode;
	if( clkSrc )
		startMode = 2;
	else
		startMode = 1;

	I32 ret = SetInFifo( pDev, timeOutMS );
	if( ret < 0 )
		return ret;

	pDev->threadError = EM9636_SUCCESS;

	return SendStartOrStop( pDev, isPSync & 1, startMode & 3, timeOutMS );
}

I32 _stdcall EM9636M_HcStop( EM9636_DevPara* hDevice, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	//关闭端口后，阻塞调用的recv会自动返回错误
	EM9636_DataClose( hDevice );
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;
	if( pDev->isHcStart )
	{
		pDev->isHcStart = 0;
		WaitForSingleObject( pDev->hReadThreadOver , 3100 );
	}
	I32 ret = SendStartOrStop( pDev, 0, 0, timeOutMS );

	return ret;
}

I32 _stdcall EM9636M_HcSFifoCanReadCount( EM9636_DevPara* hDevice, I32* canReadCount )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;
	if( canReadCount )
		*canReadCount = pDev->codeFifo.CanReadBytesCount() / 2;
	return pDev->threadError;
}

I32 _stdcall EM9636M_HcSFifoRead( EM9636_DevPara* hDevice, I32 dataCount, U16* dataBuffer, I32* realReadCount )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;
	I32 readCount = min( (U32)dataCount, pDev->codeFifo.CanReadBytesCount() / 2 );
	if( readCount )
		pDev->codeFifo.Read( (I8*)dataBuffer, readCount * sizeof(U16) );
	if( realReadCount )
		*realReadCount = readCount;

	return pDev->threadError;
}*/

I32 _stdcall EM9636_FifoGetGroupCC( EM9636_DevPara* hDevice )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;

	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	I32 adBC = (pDev->adPara.endChNo - pDev->adPara.beginChNo + 1);
	I32 ioBC = (pDev->ioInFifo + pDev->diInFifo);
	I32 ecBC = 0;
	for( I32 i = 0; i < EM9636_MAXECCHCNT; ++i )
	{
		ecBC += pDev->ecInFifol16[i];
		ecBC += pDev->ecInFifoh16[i];
	}
	I32 ctBC = 0;
	for( I32 i = 0; i < EM9636_MAXCTCHCNT; ++i )
	{
		ctBC += pDev->ctInFifo[i];
	}

	return adBC + ioBC + ecBC + ctBC;
}

I32 _stdcall EM9636_FifoAdChGetCode( EM9636_DevPara* hDevice, I32 chInx, U32 codesCount, U16* dataBuffer, U16* adCode, U32* adCodeCount )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;

	if( !dataBuffer || !adCode )
		return EM9636_FAILURE;

	EM9636_DevPara* p = (EM9636_DevPara*)hDevice;

	if( chInx > p->adPara.endChNo - p->adPara.beginChNo )
		return EM9636_FAILURE;

	U32 stepCount = EM9636_FifoGetGroupCC( hDevice );
	U32 j = 0;

	for( U32 i = chInx; i < codesCount; i += stepCount )
	{
		adCode[j++] = dataBuffer[i];
	}

	if( adCodeCount )
		*adCodeCount = j;
	return 0;
}

I32 _stdcall EM9636_FifoIoGetCode( EM9636_DevPara* hDevice, U32 codesCount, U16* dataBuffer, U16* ioCode, U32* ioCodeCount )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;

	if( !dataBuffer || !ioCode )
		return EM9636_FAILURE;

	EM9636_DevPara* p = (EM9636_DevPara*)hDevice;
	if( !p->ioInFifo )
		return EM9636_FAILURE;

	U32 stepCount = EM9636_FifoGetGroupCC( hDevice );
	U32 j = 0;
	U32 beginInx = p->adPara.endChNo - p->adPara.beginChNo + 1;
	for( U32 i = beginInx; i < codesCount; i += stepCount )
	{
		ioCode[j++] = dataBuffer[i];
	}

	if( ioCodeCount )
		*ioCodeCount = j;
	return 0;
}

I32 _stdcall EM9636_FifoDiGetCode( EM9636_DevPara* hDevice, U32 codesCount, U16* dataBuffer, U16* diCode, U32* diCodeCount )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;

	if( !dataBuffer || !diCode )
		return EM9636_FAILURE;

	EM9636_DevPara* p = (EM9636_DevPara*)hDevice;
	if( !p->diInFifo )
		return EM9636_FAILURE;

	U32 stepCount = EM9636_FifoGetGroupCC( hDevice );
	U32 j = 0;
	U32 beginInx = p->adPara.endChNo - p->adPara.beginChNo + 1 + p->ioInFifo;
	for( U32 i = beginInx; i < codesCount; i += stepCount )
	{
		diCode[j++] = dataBuffer[i];
	}

	if( diCodeCount )
		*diCodeCount = j;
	return 0;
}

I32 _stdcall EM9636_FifoEcChGetCode( EM9636_DevPara* hDevice, I32 chInx, U32 codesCount, U16* dataBuffer, I32* ecCode, U32* ecCodeCount )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;

	if( !dataBuffer || !ecCode )
		return EM9636_FAILURE;

	EM9636_DevPara* p = (EM9636_DevPara*)hDevice;

	I32 chCnt = 0;
	for( I32 i = 0; i < EM9636_MAXECCHCNT; ++i )
		if( p->ecInFifoh16[i] || p->ecInFifol16[i] )
			++chCnt;
	if( chInx >= chCnt )
		return EM9636_FAILURE;

	U32 stepCount = EM9636_FifoGetGroupCC( hDevice );
	U32 j = 0;
	U32 beginInx = p->adPara.endChNo - p->adPara.beginChNo + 1 + p->ioInFifo + p->diInFifo;
	if( chInx )
		beginInx += p->ecInFifoh16[0] + p->ecInFifol16[0];

	for( U32 i = beginInx; i < codesCount; i += stepCount )
	{
		ecCode[j++] = *(I32*)(dataBuffer+i);
	}

	if( ecCodeCount )
		*ecCodeCount = j;
	return 0;
}

I32 _stdcall EM9636_FifoCtChGetCode( EM9636_DevPara* hDevice, I32 chInx, U32 codesCount, U16* dataBuffer, U32* ctCode, U32* ctCodeCount )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;

	if( !dataBuffer || !ctCode )
		return EM9636_FAILURE;

	EM9636_DevPara* p = (EM9636_DevPara*)hDevice;

	I32 chCnt = 0;
	for( I32 i = 0; i < EM9636_MAXCTCHCNT; ++i )
		if( p->ctInFifo[i] )
			++chCnt;
	if( chInx >= chCnt )
		return EM9636_FAILURE;

	U32 stepCount = EM9636_FifoGetGroupCC( hDevice );
	U32 j = 0;
	U32 beginInx = p->adPara.endChNo - p->adPara.beginChNo + 1 + p->ioInFifo + p->diInFifo;
	for( I32 i = 0; i < EM9636_MAXECCHCNT; ++i )
	{
		beginInx += p->ecInFifoh16[i];
		beginInx += p->ecInFifol16[i];
	}
	beginInx += chInx;

	for( U32 i = beginInx; i < codesCount; i += stepCount )
	{
		ctCode[j++] = dataBuffer[i];//counter is 16bit;
	}

	if( ctCodeCount )
		*ctCodeCount = j;
	return 0;
}

I32 _stdcall EM9636_OlGetStorageInfo( EM9636_DevPara* hDevice, I8* storageDevice, U32* storageSize, U32* usedSize, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	V_I8 vc(10);
	I32 ret = ZTLC_RecvAndVerify( pDev->hCmd, 150, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;
	if( storageDevice )
	{
		*storageDevice = vc[1];
	}
	if( storageSize )
	{
		*storageSize = ((vc[2]&0xff) << 24) | ((vc[3]&0xff) << 16) | ((vc[4]&0xff) << 8) | (vc[5]&0xff);
	}
	if( usedSize )
	{
		*usedSize = ((vc[6]&0xff) << 24) | ((vc[7]&0xff) << 16) | ((vc[8]&0xff) << 8) | (vc[9]&0xff);
	}

	return 0;
}

I32 _stdcall EM9636_OlGetIsSaving( EM9636_DevPara* hDevice, I8* isSaving, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	V_I8 vc(2);
	I32 ret = ZTLC_RecvAndVerify( pDev->hCmd, 25, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;
	if( isSaving )
	{
		*isSaving = vc[1];
	}

	return 0;
}

I32 _stdcall EM9636_OlSetSaving( EM9636_DevPara* hDevice, I8 isSaving, I32 timeOutMS  )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	V_I8 vc(2, 0);
	vc[0] = 0;
	vc[1] = isSaving;

	I32 ret = ZTLC_SendAndVerify( pDev->hCmd, 25, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	return 0;
}

I32 _stdcall EM9636_SetClientTime( EM9636_DevPara* hDevice, I8* timeArray, I32 timeOutMS  )
{
/*	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	V_I8 vcTime(6, 0);
	if( timeArray )
		memcpy( &vcTime[0], timeArray, vcTime.size() );
	else
	{
		SYSTEMTIME st;
		GetLocalTime( &st );
		vcTime[0] = st.wYear % 100;
		vcTime[1] = st.wMonth % 13;
		vcTime[2] = st.wDay % 32;
		vcTime[3] = st.wHour % 24;
		vcTime[4] = st.wMinute % 60;
		vcTime[5] = st.wSecond % 60;
	}


	V_I8 vc(8, 0);
	copy( vcTime.begin(), vcTime.end(), vc.begin() );

	I32 ret = ZTLC_SendAndVerify( pDev->hCmd, 189, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;*/

	return 0;
}

I32 _stdcall EM9636_GetClientTime( EM9636_DevPara* hDevice, I8* timeArray, I32 timeOutMS  )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;
	if( !timeArray )
		return EM9636_FAILURE;

	V_I8 vc(8, 0);

	I32 ret = ZTLC_RecvAndVerify( pDev->hCmd, 189, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;
	memcpy( timeArray, &vc[0], 6 );

	return 0;
}


I32 _stdcall EM9636_IpSetInfo( EM9636_DevPara* hDevice, I32 ip[4], I32 mask[4], I32 gate[4], I32 cmdPort, I32 dataPort, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;
	V_I8 vcIP(4), vcMask(4), vcGate(4), vcCmdPort(2), vcDataPort(2);
	for( size_t i = 0; i < vcIP.size(); ++ i )
	{
		vcIP[i] = ip[i] & 0xff;
		vcMask[i] = mask[i] & 0xff;
		vcGate[i] = gate[i] & 0xff;
	}
	vcCmdPort[0] = (cmdPort >> 8) & 0xff;
	vcCmdPort[1] = (cmdPort) & 0xff;
	vcDataPort[0] = (dataPort >> 8) & 0xff;
	vcDataPort[1] = (dataPort) & 0xff;
	I32 ret =ZTLC_SendAndVerify( pDev->hCmd, 0, &vcIP[0], (U32)vcIP.size(), timeOutMS );
	if( ret < 0 )
		return ret;
	ret = ZTLC_SendAndVerify( pDev->hCmd, 2, &vcMask[0], (U32)vcMask.size(), timeOutMS );
	if( ret < 0 )
		return ret;
	ret = ZTLC_SendAndVerify( pDev->hCmd, 7, &vcGate[0], (U32)vcGate.size(), timeOutMS );
	if( ret < 0 )
		return ret;
	ret = ZTLC_SendAndVerify( pDev->hCmd, 9, &vcCmdPort[0], (U32)vcCmdPort.size(), timeOutMS );
	if( ret < 0 )
		return ret;
	return ZTLC_SendAndVerify( pDev->hCmd, 4, &vcDataPort[0], (U32)vcDataPort.size(), timeOutMS );
}

I32 _stdcall EM9636_IpGetInfo( EM9636_DevPara* hDevice, I32 ip[4], I32 mask[4], I32 gate[4], I32* cmdPort, I32* dataPort, I32 mac[6], I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;
	V_I8 vc(22);
	if( ZTLC_RecvAndVerify( pDev->hCmd, 0, &vc[0], (U32)vc.size(), timeOutMS ) < 0 )
		return -1;
	for( int i = 0; i < 4; ++i )
	{
		ip[i] = vc[i] & 0xff;
		mask[i] = vc[i + 4] & 0xff;
		mac[i] = vc[i + 8] & 0xff;
		gate[i] = vc[i + 14] & 0xff;
	}
	mac[4] = vc[12] & 0xff;
	mac[5] = vc[13] & 0xff;
	*cmdPort = vc[18] * 256 + vc[19];
	*dataPort = vc[20] * 256 + vc[21];
	return 0;
}

I32 _stdcall EM9636_SetInitOut( EM9636_DevPara* hDevice, I8 doWrite, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;

	V_I8 vc(2, 0);
	vc[0] = 0;
	vc[1] = doWrite;

	I32 ret = ZTLC_SendAndVerify( pDev->hCmd, 38, &vc[0], (U32)vc.size(), timeOutMS );
	if( ret < 0 )
		return ret;

	return 0;
}

typedef struct UDP_HEADER
{
	U8 beginChar;
	U8 id;
	U16 bytesCnt;
	U16 cmdInx;
}UdpHeader;//size=6;
#define UDP_HEADER_SIZE 6
#define UDP_MAX_BYTES       512 //internet标准MTU576，除去包头，最大值位508，因此取512

I32 _stdcall UdpSendAndVerify( EM9636_DevPara* pDev, char* cmd, I32 cmdLen, char* recvChar, I32* retLen, U32 timeOutMS  )
{
	if( !pDev->strIP[0] || !pDev->cmdPort || !cmd || !recvChar )
		return EM9636_FAILURE;
	static unsigned char sendId = 0;

	int sock = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(pDev->cmdPort);
	sin.sin_addr.s_addr = inet_addr(pDev->strIP);
	cmd[1] = sendId;
	int ret = sendto( sock, cmd, cmdLen, 0, (sockaddr*)&sin, sizeof(sin) );
	if( ret == SOCKET_ERROR )
	{
		pDev->errorCode = errno;
		close( sock );
		return EM9636_SOCKET_ERROR;
	}
	else if( ret < (int)cmdLen )
	{
		close( sock );
		return EM9636_SEND_ERROR;
	}
	//	timeval tv = {timeOutMS/1000, timeOutMS%1000};
	int tv = timeOutMS;
	ret = setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(tv));
	if (ret)
	{
		pDev->errorCode = errno;
		close( sock );
		return EM9636_SOCKET_ERROR;
	}

	socklen_t len = sizeof(sin);
	ret = recvfrom( sock, recvChar, UDP_MAX_BYTES, 0, (sockaddr*)&sin, &len );
	if( ret == SOCKET_ERROR )
	{
		pDev->errorCode = errno;
		close( sock );
		if( pDev->errorCode == ECONNRESET )
		{
			return EM9636_TIMEOUT_ERROR;
		}
		return EM9636_RECVVERIFY_ERROR;
	}
/*	if( ret < 7 )
	{
		if( retLen )
			*retLen = ret;
		closesocket( sock );
		return EM9636_RECVVERIFY_ERROR;
	}*/
	if( sendId != recvChar[1] )
	{
		if( retLen )
			*retLen = ret;
		close( sock );
		sendId++;
		return EM9636_RECVVERIFY_ERROR;
	}
	sendId++;
	UdpHeader* ud = (UdpHeader*)recvChar;
	if( !ud->cmdInx )
	{
		pDev->errorCode = recvChar[6];
		if( retLen )
			*retLen = ret;
		close( sock );
		return EM9636_PARA_ERROR;
	}

	if( retLen )
		*retLen = ret;

	close( sock );
	return EM9636_SUCCESS;
}

I32 _stdcall EM9636_UdpSetCmdPort( EM9636_DevPara* hDevice, I32 cmdPort, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;
	char cmd[] = {0x55, 0, 4, 0, 1, 0, cmdPort & 0xff, (cmdPort>>8)&0xff};
	char recvChar[UDP_MAX_BYTES];
	I32 retlen;
	return UdpSendAndVerify( pDev, cmd, sizeof(cmd), recvChar, &retlen, timeOutMS );
}

I32 _stdcall EM9636_UdpSetDataPort( EM9636_DevPara* hDevice, I32 dataPort, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;
	char cmd[] = {0x55, 0, 4, 0, 2, 0, dataPort & 0xff, (dataPort>>8)&0xff};
	char recvChar[UDP_MAX_BYTES];
	I32 retlen;
	return UdpSendAndVerify( pDev, cmd, sizeof(cmd), recvChar, &retlen, timeOutMS );
}

I32 _stdcall EM9636_UdpGetCmdPort( EM9636_DevPara* hDevice, I32* cmdPort, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;
	char cmd[] = {0x55, 0, 4, 0, 1, 0, 0, 0};
	char recvChar[UDP_MAX_BYTES];
	I32 retlen;
	I32 ret = UdpSendAndVerify( pDev, cmd, sizeof(cmd), recvChar, &retlen, timeOutMS );
	if( ret < 0 )
		return ret;
	if( cmdPort )
		*cmdPort = *(U16*)(recvChar + 6);
	return EM9636_SUCCESS;
}

I32 _stdcall EM9636_UdpGetDataPort( EM9636_DevPara* hDevice, I32* dataPort, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;
	char cmd[] = {0x55, 0, 4, 0, 2, 0, 0, 0};
	char recvChar[UDP_MAX_BYTES];
	I32 retlen;
	I32 ret = UdpSendAndVerify( pDev, cmd, sizeof(cmd), recvChar, &retlen, timeOutMS );
	if( ret < 0 )
		return ret;
	if( dataPort )
		*dataPort = *(U16*)(recvChar + 6);
	return EM9636_SUCCESS;
}

I32 _stdcall EM9636_UdpCloseAll( EM9636_DevPara* hDevice, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;
	char cmd[] = {0x55, 0, 2, 0, 3, 0};
	char recvChar[UDP_MAX_BYTES];
	I32 retlen;
	I32 ret = UdpSendAndVerify( pDev, cmd, sizeof(cmd), recvChar, &retlen, timeOutMS );
	if( ret < 0 )
		return ret;
	return EM9636_SUCCESS;
}

I32 _stdcall EM9636_UdpGetConnectCnt( EM9636_DevPara* hDevice, I8* cmdCnt, I8* dataCnt, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;
	char cmd[] = {0x55, 0, 2, 0, 4, 0};
	char recvChar[UDP_MAX_BYTES];
	I32 retlen;
	I32 ret = UdpSendAndVerify( pDev, cmd, sizeof(cmd), recvChar, &retlen, timeOutMS );
	if( ret < 0 )
		return ret;
	if( cmdCnt )
		*cmdCnt = recvChar[6];
	if( dataCnt )
		*dataCnt = recvChar[7];
	return EM9636_SUCCESS;
}

I32 _stdcall EM9636_UdpReboot( EM9636_DevPara* hDevice, I32 timeOutMS )
{
	if( hDevice == 0 )
		return EM9636_FAILURE;
	EM9636_DevPara* pDev = (EM9636_DevPara*)hDevice;
	char cmd[] = {0x55, 0, 2, 0, 5, 0};
	char recvChar[UDP_MAX_BYTES];
	I32 retlen;
	I32 ret = UdpSendAndVerify( pDev, cmd, sizeof(cmd), recvChar, &retlen, timeOutMS );
	if( ret < 0 )
		return ret;
	return EM9636_SUCCESS;
}
//void PID_init(pid& pid)
//{
//	printf("PID_init begin \n");
//	pid.SetSpeed = 0.0;	//设定值
//	pid.ActualSpeed = 0.0;//实际值
//	pid.err = 0.0;		//实际误差
//	pid.err_last = 0.0;	//上一次的误差
//	pid.voltage = 0.0;	//输出的电压
//	pid.integral = 0.0;	//积分值
//	pid.umax =  0;					//饱和上限
//	pid.deadzone = 0;
//	pid.changeline = 0;
//	pid.I1 = 0;
//	pid.ulimit = 0;
//	pid.Kp = 0;
//	pid.Ki = 0;
//	pid.Kd = 0;
//	printf("PID_init end \n");
//}
//F64 PID_realize(pid& pid, double set, double actual)
//{
//	pid.SetSpeed = set;
//	pid.ActualSpeed = 10.0 - actual;//采集出实际位移值
//	pid.err = pid.SetSpeed - pid.ActualSpeed; //计算误差
//	pid.integral = pid.I1*pid.integral + pid.err;//k*i + err
//	////积分上限限制
//	//if (pid.integral > pid.umax)  
//	//{
//	//	pid.integral = pid.umax;
//	//}
//	//else if (pid.integral < -pid.umax)
//	//{
//	//	pid.integral = -pid.umax;
//	//}
//	if (pid.err <pid.changeline && pid.err>-pid.changeline)
//	{
//		pid.Ki = pid.umax ;
//	}
//	pid.voltage = pid.Kp *pid.err +  pid.Ki*pid.integral + pid.Kd*(pid.err - pid.err_last);
//	//死区限制
//	//if (pid.voltage < -pid.changeline)
//	//{
//	//	pid.voltage -= pid.deadzone;
//	//}
//	//else if (pid.voltage > pid.changeline)
//	//{
//	//	pid.voltage += pid.deadzone;
//	//}
//	//电压限幅
//	if (pid.voltage < -pid.ulimit)
//	{
//		pid.voltage = -pid.ulimit;
//	}
//	else if (pid.voltage > pid.ulimit)
//	{
//		pid.voltage = pid.ulimit;
//	}
//
//	pid.err_last = pid.err;
//	//printf("设定值 %f ", set);
//	//printf("位移 %f ", pid.ActualSpeed);
//	//printf("误差 %f ", pid.err);
//	//printf("积分 %f ", pid.integral);
//	//printf("输出 %f ", pid.voltage);
//	//if (pid.err > 0.02*pid.SetSpeed || pid.err < -0.02*pid.SetSpeed)
//	//{
//	//	printf("超调\n");
//	//}
//	//else
//	//	printf("未超调\n");
//	return pid.voltage;
//}
