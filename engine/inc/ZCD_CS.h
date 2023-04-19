#ifndef ZCD_CS_H
#define ZCD_CS_H

class CZCD_CS
{
private:
	pthread_mutex_t* _pCS;
public:
	CZCD_CS( pthread_mutex_t* pCS )
	{
		_pCS = pCS;
		pthread_mutex_lock( _pCS );
	}
	~CZCD_CS()
	{
		pthread_mutex_unlock( _pCS );
	}
};

#endif
