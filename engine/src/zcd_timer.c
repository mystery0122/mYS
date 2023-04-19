#include "../inc/zcd_timer.h"
ZcdTimer* ZcdTimer_CreateInit()
{
	ZcdTimer* p = (ZcdTimer*)malloc( sizeof(ZcdTimer) );
	gettimeofday( &p->clkStart, 0 );
	gettimeofday( &p->clkNow, 0 );
	return p;
}

void ZcdTimer_Init( ZcdTimer* p )
{
	gettimeofday( &p->clkStart, 0 );
	gettimeofday( &p->clkNow, 0 );
}

long long ZcdTimer_GetTimeInterval( ZcdTimer* zt )//得到从创建对象到调用此函数为止经过的微秒数
{
	gettimeofday( &zt->clkNow, 0 );
	return (zt->clkNow.tv_sec - zt->clkStart.tv_sec) * 1000000 + ( zt->clkNow.tv_usec - zt->clkStart.tv_usec );
}

void ZcdTimer_DelayUS( ZcdTimer* zt, long long us )//延迟微秒
{
	while( ZcdTimer_GetTimeInterval( zt ) < us );
}

void ZcdTimer_Delete( ZcdTimer* zt )
{
	free( zt );
}
