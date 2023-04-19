#ifndef ZCD_TIMER_H
#define ZCD_TIMER_H

#include <sys/time.h>
#include <malloc.h>

typedef struct ZCDTIMER
{
	struct timeval clkStart;
	struct timeval clkNow;
}ZcdTimer;

ZcdTimer* ZcdTimer_CreateInit();

void ZcdTimer_Init( ZcdTimer* p );

long long ZcdTimer_GetTimeInterval( ZcdTimer* zt );//得到从创建对象到调用此函数为止经过的微秒数

void ZcdTimer_DelayUS( ZcdTimer* zt, long long us );//延迟微秒

void ZcdTimer_Delete( ZcdTimer* zt );

#endif
