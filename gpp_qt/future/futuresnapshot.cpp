#include"futuresnapshot.h"


void Futuresnapshot::setrecord(std::string InstrumentID, long tm, double BidPrice1 ,double AskPrice1, double BidSize1 ,double AskSize1)
{
	
	_InstrumentID=InstrumentID;
	_tm=tm;
	_BidPrice1=BidPrice1;
	_AskPrice1=AskPrice1;
	_BidSize1=BidSize1;
	_AskSize1=AskSize1;
}

std::string Futuresnapshot::get_InstrumentID(){return _InstrumentID;}	//eg IO1401

long Futuresnapshot::get_tm(){return _tm;}								//eg 

double Futuresnapshot::get_BidPrice1(){return _BidPrice1;}				//eg 20

double Futuresnapshot::get_AskPrice1(){return _AskPrice1;}				//eg 25

double Futuresnapshot::get_BidSize1(){return _BidSize1;}				//eg 20

double Futuresnapshot::get_AskSize1(){return _AskSize1;}				//eg 25