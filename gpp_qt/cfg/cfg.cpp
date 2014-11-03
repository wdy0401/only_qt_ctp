#include"cfg.h"

#include<iostream>
#include<fstream>
#include<string>
using namespace std;

cfg::cfg()
{
	_cfgfile="c:\\cfg\\simu.cfg";
	_sep="=";
}
cfg::~cfg()
{
	delete _pfile;
}
const std::string cfg::getparam(const std::string & param)
{
	if(_kvpair.find(param)!=_kvpair.end())
	{
		return _kvpair[param];
	}
	else
	{
		return "";
	}
}
void cfg::setcfgfile(const std::string & cfgfile)
{
	_cfgfile=cfgfile;
	clearcfg();
	loadfile();
}
void cfg::addcfgfile(const std::string & cfgfile)
{
	_cfgfile=cfgfile;
	loadfile();
}
void cfg::setsep(const std::string & sep)
{
	_sep=sep;
}
void cfg::clearcfg()
{
	_kvpair.clear();
}
void cfg::loadfile()
{
	_pfile=new ifstream;
	_pfile->open(_cfgfile.c_str());
	if(! _pfile->is_open()) //检测文件存在性
	{
		delete _pfile;
		_pfile=NULL;
		cerr << "********************************************\n*\n*\n*\n";
		cerr << "Cannot openfile " << _cfgfile.c_str() << endl;
		cerr << "Please set cfgfile and restart";
		cerr << "\n*\n*\n*\n********************************************"<<endl;
		getchar();
		return;
	}
	string tmpstring;
	string key,value;
	while(getline(*_pfile,tmpstring))
	{
		if(tmpstring.size()==0 || tmpstring[0]=='#')//排除空行和#开头的注释行
		{
			continue;
		}
        if(tmpstring.find(_sep)==string::npos)
		{
			cerr << "ERROR : CFG_FILE line; "<<tmpstring<<endl;
			continue;
		}
		unsigned int fp=tmpstring.find_first_of(_sep);
		key=tmpstring.substr(0,fp);
		value=tmpstring.substr(fp+1,tmpstring.size());
		_kvpair[key]=value;
	}
}
/*
int main()
{
	cfg simucfg;
	simucfg.loadfile();
	return 0;
}
*/
