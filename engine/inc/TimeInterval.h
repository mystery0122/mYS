#ifndef TIMEINERVAL_H
#define TIMEINERVAL_H

#include <sys/time.h>

class CTimeInterval
{
private:
	struct timeval clkStart;
public:
	CTimeInterval()
	{
		gettimeofday( &clkStart, 0 );
	}
	void Reset()
	{
		gettimeofday( &clkStart, 0 );
	}
	double GetIntervalMS()
	{
		return GetIntervalUS() / 1000.0;
	}
	double GetIntervalUS()
	{
		struct timeval clkNow;
		gettimeofday( &clkNow, 0 );
		return (clkNow.tv_sec - clkStart.tv_sec) * 1000000 + ( clkNow.tv_usec - clkStart.tv_usec );
	}

	void DelayUS( unsigned long us )
	{
		CTimeInterval tm;
		while( tm.GetIntervalUS() < us );
	}
};

#endif
