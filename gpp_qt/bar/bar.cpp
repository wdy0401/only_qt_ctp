#include"bar.h"
#include"../wtimer/wtimer.h"

extern wtimer tm;

bar::bar()
{
	_nowtime=0;
	_begtime=0;
	_endtime=0;
	
	_value=0;

	_open=0;
	_high=0;
	_low=0;
	_close=0;

	_volume=0;
}
void bar::setnowtime(double nowtime)
{
	_nowtime=nowtime;
	if(_begtime==0)
	{
		_begtime=nowtime;
	}
	_endtime=nowtime;
}
void bar::setnowtime()
{
	setnowtime(tm.nowtic());
}
void bar::setvalue(double value,double tm)
{
	if(tm==0)
	{
		setnowtime();
	}
	else
	{
		setnowtime(tm);
	}
	setvalue(value);
}
void bar::setvalue(double value)
{
	_value=value;
	if(_open==0)
	{
		_open=_value;
	}
	if(_high==0 || _high<_value)
	{
		_high=_value;
	}
	if(_low==0 || _low>_value)
	{
		_low=_value;
	}
	_close=_value;
}

void bar::setvolume(double volume)
{
	_volume+=volume;
}



double bar::getbegtime()
{
	return _begtime;
}
double bar::getendtime()
{
	return _endtime;
}
double bar::getopen()
{
	return _open;
}
double bar::gethigh()
{
	return _high;
}
double bar::getlow()
{
	return _low;
}
double bar::getclose()
{
	return _close;
}
double bar::getvolume()
{
	return _volume;
}