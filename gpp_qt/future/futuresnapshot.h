#ifndef FUTURESNAPSHOT
#define FUTURESNAPSHOT

#include<string>

class Futuresnapshot
{
public:

	void setrecord(std::string InstrumentID, long tm, double BidPrice1 ,double AskPrice1, double BidSize1 ,double AskSize1);
	std::string get_InstrumentID();	//eg IO1401
	long get_tm();					//eg 
	double get_BidPrice1();			//eg 20
	double get_AskPrice1();			//eg 25
	double get_BidSize1();			//eg 20
	double get_AskSize1();			//eg 25

private:

	std::string _InstrumentID;	//eg IO1401
	long _tm;					//eg 123456789
	double _BidPrice1;			//eg 20
	double _AskPrice1;			//eg 25
	double _BidSize1;			//eg 20
	double _AskSize1;			//eg 25
};

#endif