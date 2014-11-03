//??????? ?????????map ?????snapshot ??????????or?????????queue
//??????map ????????????snapshot ?????????snap??
#include"vnoption.h"
#include"../wfunction/wfunction.h"
#include<stdlib.h>
#include<stdio.h>
using namespace std;


void Vnoption::updaterecord(string InstrumentID, string callput, long tm, double StrikePrice, double BidPrice1 ,double AskPrice1, double BidSize1 ,double AskSize1)
{
	Vnsnapshot nowsnapshot;
	nowsnapshot.setrecord(InstrumentID, callput, tm, StrikePrice, BidPrice1 , AskPrice1, BidSize1 , AskSize1);
	_lastsnapshot=nowsnapshot;
	
    string optioncpname=InstrumentID+"_"+callput+"_"+wfunction::itos((int) StrikePrice);
	
	//option queue????????????
	if (_optionqueue.find(optioncpname)==_optionqueue.end())
	{
		list<Vnsnapshot> nowlist;																//???queue
		nowlist.push_front(nowsnapshot);														//????queue??
		_optionqueue.insert(map<string,list<Vnsnapshot> >::value_type(optioncpname,nowlist));	//???? queue map
	}
	else
	{
		_optionqueue.find(optioncpname)->second.push_front(nowsnapshot);
		if(_maxqueuelength!=0 && _optionqueue.find(optioncpname)->second.size()>_maxqueuelength)											//????queue?????

		{
			_optionqueue.find(optioncpname)->second.pop_back();
		}
	}

	//option snapshot????????????
	if (_optionsnapshot.find(optioncpname)==_optionsnapshot.end())									
	{
		_optionsnapshot.insert(map<string,Vnsnapshot>::value_type(optioncpname,nowsnapshot));		//???? queue map
	}
	else
	{
		_optionsnapshot.erase(InstrumentID);														//option snapshot???????????? ??????
		_optionsnapshot.insert(map<string,Vnsnapshot>::value_type(optioncpname,nowsnapshot));		//???? queue map
	}
}

void Vnoption::set_maxqueuelength(unsigned int maxqueuelength)
{
	_maxqueuelength=maxqueuelength;
}
Vnsnapshot  Vnoption::get_lastsnapshot()
{
	return _lastsnapshot;
}
map<std::string,Vnsnapshot> Vnoption::get_optionsnapshot()
{
	return _optionsnapshot;
}

