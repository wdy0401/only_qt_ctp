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
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
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
	static void UnZipStream(std::ifstream& inputFile,std::ofstream& outputFile);
	static void ZipStream(std::ifstream& inputFile,std::ofstream& outputFile);

	static char * ctp_time_char_convert(char *,int );
};
#endif