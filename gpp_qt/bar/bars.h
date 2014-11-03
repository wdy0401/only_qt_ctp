#ifndef BARS
#define BARS

#include "bar.h"
#include <map>
#include<string>

//默认长度1分钟 即length=60

class bars
{
public:
	bars();
	void setbarname(const std::string &);
	void setlength(long);
	void updatebar(double);//only price
	void updatebar(double,long);//price and volume "trade"
	bar * mergebar(long);
	
private:
	long _length;
	std::string _barname;
	bar * _nowbar;
	std::map<long,bar *> _barmap;
};

#endif