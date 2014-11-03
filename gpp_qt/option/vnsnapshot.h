#ifndef VNSNAPSHOT
#define VNSNAPSHOT

#include<string>

//Vn含义为香草期权
//记录每一时点的截面数据
//目前记录lv1级信息

//		可扩展方向
//1. bid ask级数扩展
//2. 成交量 持仓量等信息
//3. Greek等信息

class Vnsnapshot
{
public:

	void setrecord(std::string InstrumentID, std::string callput, long tm, double StrikePrice, double BidPrice1 ,double AskPrice1, double BidSize1 ,double AskSize1);
	std::string get_InstrumentID();	//eg IO1401
	std::string get_callput();		//eg C
	long get_tm();					//eg 
	double get_StrikePrice();		//eg 2350
	double get_BidPrice1();			//eg 20
	double get_AskPrice1();			//eg 25
	double get_BidSize1();			//eg 20
	double get_AskSize1();			//eg 25

private:

	std::string _InstrumentID;	//eg IO1401
	std::string _callput;		//eg C
	long _tm;					//eg 123456789
	double _StrikePrice;		//eg 2350
	double _BidPrice1;			//eg 20
	double _AskPrice1;			//eg 25
	double _BidSize1;			//eg 20
	double _AskSize1;			//eg 25
};

#endif
