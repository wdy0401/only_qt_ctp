#ifndef BARS_MANAGE
#define BARS_MANAGE

#include "bars.h"
#include<map>
#include<string>

//默认的时间间隔为1分钟
//目前尚无调整时间间隔的需求 
class bars_manage
{
public:
	void addbarlist(const std::string &);
	void newbars(const std::string &);
	void newbars(const std::string &,long);
	void setlength(const std::string &,long);
	void updatebar(const std::string &,double);//only price
	void updatebar(const std::string &,double,long);//price and volume "trade"
	bool isbarsexist(const std::string &);
	bar * mergebar(const std::string &,long);
	
private:
	std::map<std::string,bars *> _barsmap;
	bars * _nowbars;
};

#endif