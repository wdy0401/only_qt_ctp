#include"vnsnapshot.h"



void Vnsnapshot::setrecord(std::string InstrumentID,std::string callput, long tm, double StrikePrice, double BidPrice1 ,double AskPrice1, double BidSize1 ,double AskSize1)
{
	
	_InstrumentID=InstrumentID;
	_callput=callput;
	_tm=tm;
	_StrikePrice=StrikePrice;
	_BidPrice1=BidPrice1;
	_AskPrice1=AskPrice1;
	_BidSize1=BidSize1;
	_AskSize1=AskSize1;
}

std::string Vnsnapshot::get_InstrumentID(){return _InstrumentID;}	//eg IO1401

std::string Vnsnapshot::get_callput(){return _callput;}	//eg IO1401

long Vnsnapshot::get_tm(){return _tm;}								//eg 

double Vnsnapshot::get_StrikePrice(){return _StrikePrice;}			//eg 2350

double Vnsnapshot::get_BidPrice1(){return _BidPrice1;}				//eg 20

double Vnsnapshot::get_AskPrice1(){return _AskPrice1;}				//eg 25

double Vnsnapshot::get_BidSize1(){return _BidSize1;}				//eg 20

double Vnsnapshot::get_AskSize1(){return _AskSize1;}				//eg 25