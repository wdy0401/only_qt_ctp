#ifndef CFG
#define CFG

#include<iostream>
#include<fstream>
#include<string>
#include<map>

//在参数数量增加时或参数数据结构复杂时 需要用xml来处理 
//xml有待实现 boost里有没有？

class cfg
{
public:
	cfg();
	~cfg();
    const std::string getparam(const std::string &);
	void setcfgfile(const std::string &);
	void addcfgfile(const std::string &);
	void setsep(const std::string &);
	void clearcfg();
	void loadfile();
private:
	std::map<std::string,std::string> _kvpair;
	std::string _cfgfile;
	std::string _sep;
	std::ifstream * _pfile;
};

#endif

