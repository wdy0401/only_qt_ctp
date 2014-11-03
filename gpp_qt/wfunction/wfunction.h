#ifndef WFUNCTION
#define WFUNCTION

#include<string>
#include<iostream> 
#include<stdlib.h>
#include<sstream>
#include<list>
#include<windows.h>

#include <fstream>
#include <iostream>

/*
namespace WFUNCTION {
	class wfunction;
}
*/
class wfunction
{
public:
	static std::string itos(long);
	static std::string ftos(double);
	static std::list<std::string> splitstring(std::string);
	static std::list<std::string> splitstring(std::string,const std::string &);
	static char * gbk2utf8(const char*);
	static char * utf82gbk(const char*);


	static char * ctp_time_char_convert(char *,int );
};
#endif