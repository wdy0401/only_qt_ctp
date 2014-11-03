#ifndef FUTURERECORD
#define FUTURERECORD

//维护两份 对应着两个map 一份是snapshot 一份是有时限or个数限制的queue
//有两个map 一个是对应到一个snapshot 一个是对应到snap串

#include<map>
#include<list>
#include"futuresnapshot.h"

class Futurerecord
{
public:

	void updaterecord(std::string InstrumentID,  long tm,  double BidPrice1 ,double AskPrice1, double BidSize1 ,double AskSize1);
	void set_maxqueuelength(unsigned int);
	std::map<std::string,Futuresnapshot> get_futuresnapshot();
	Futuresnapshot  get_lastsnapshot();


private:

	std::map<std::string,std::list<Futuresnapshot> >	_futurequeue;
	std::map<std::string,Futuresnapshot>				_futuresnapshot;
	Futuresnapshot										_lastsnapshot;
	unsigned int									_maxqueuelength;

};
#endif