#ifndef SPREAD_ERROR_CHECK
#define SPREAD_ERROR_CHECK

#include"../wfunction/wfunction.h"
#include"vnoption.h"
#include<set>


class Spread_error_check
{
	public:
		void eachfunction(Vnoption);
	
	private:
		void _check_error(Vnoption);
		void _updatelist(Vnsnapshot);
		std::map<std::string,std::set<std::string> >	_eachoptiongroup; //将IO1401C中各个执行价格的都放到一个group里面
};

#endif

/*
1.更新list
2.计算每个list的价差情况 并输出价差勘误表 暂定为stdout
*/