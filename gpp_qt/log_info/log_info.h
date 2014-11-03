#ifndef LOG_INFO
#define LOG_INFO

#include<string>
#include<iostream>
#include<fstream>
#include<sstream>

class log_info
{
public:

	bool setfile(const std::string &);
	void closefile();
	void writeinfo(const std::string &);

private:
	std::ofstream outlog;
};

#endif

