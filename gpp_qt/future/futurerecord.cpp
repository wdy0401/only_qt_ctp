//??????? ?????????map ?????snapshot ??????????or?????????queue
//??????map ????????????snapshot ?????????snap??
#include"futurerecord.h"
#include"../wfunction/wfunction.h"
#include<stdlib.h>
#include<stdio.h>
using namespace std;


void Futurerecord::updaterecord(string InstrumentID, long tm,  double BidPrice1 ,double AskPrice1, double BidSize1 ,double AskSize1)
{
	Futuresnapshot nowsnapshot;
	nowsnapshot.setrecord(InstrumentID, tm, BidPrice1 , AskPrice1, BidSize1 , AskSize1);
	_lastsnapshot=nowsnapshot;
	
	//string InstrumentID=InstrumentID+"_"+"_"+Wfunction::itos((int) StrikePrice);
	
	//option queue????????????
	if (_futurequeue.find(InstrumentID)==_futurequeue.end())
	{
		list<Futuresnapshot> nowlist;																//???queue
		nowlist.push_front(nowsnapshot);														//????queue??
		_futurequeue.insert(map<string,list<Futuresnapshot> >::value_type(InstrumentID,nowlist));	//???? queue map
	}
	else
	{
		_futurequeue.find(InstrumentID)->second.push_front(nowsnapshot);
		if(_maxqueuelength!=0 && _futurequeue.find(InstrumentID)->second.size()>_maxqueuelength)											//????queue?????

		{
			_futurequeue.find(InstrumentID)->second.pop_back();
		}
	}

	//option snapshot????????????
	if (_futuresnapshot.find(InstrumentID)==_futuresnapshot.end())									
	{
		_futuresnapshot.insert(map<string,Futuresnapshot>::value_type(InstrumentID,nowsnapshot));		//???? queue map
	}
	else
	{
		_futuresnapshot.erase(InstrumentID);														//option snapshot???????????? ??????
		_futuresnapshot.insert(map<string,Futuresnapshot>::value_type(InstrumentID,nowsnapshot));		//???? queue map
	}
}

void Futurerecord::set_maxqueuelength(unsigned int maxqueuelength)
{
	_maxqueuelength=maxqueuelength;
}
Futuresnapshot Futurerecord::get_lastsnapshot()
{
	return _lastsnapshot;
}
map<std::string,Futuresnapshot> Futurerecord::get_futuresnapshot()
{
	return _futuresnapshot;
}

