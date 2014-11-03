#ifndef VNOPTION
#define VNOPTION

#include<map>
#include<list>
#include"vnsnapshot.h"


//												main
//VNOPTION 级							IO												HO
//VNOPTION 下属map级	IO1401	IO1402	IO1403				HO1401	HO1402	HO1403
//VNSNAPSHOT 级 			vnsnapshot	


//基于Vnsnapshot 每个vnoption实例包含一个option（IO非IO1401）的全部数据
//每个合约（IO1401）对应一个list和一个snapshot
//list与snapshot分别保存在两个map中 _optionqueue _optionsnapshot
//_optionqueue中存放着每个合约的历史信息，格式为list，可以设定list长度
//_optionsnapshot 中存放着每个合约的最新snapshot



class Vnoption
{
public:

	void updaterecord(std::string InstrumentID, std::string callput, long tm, double StrikePrice, double BidPrice1 ,double AskPrice1, double BidSize1 ,double AskSize1);
	void set_maxqueuelength(unsigned int);
	std::map<std::string,Vnsnapshot> get_optionsnapshot();
	Vnsnapshot  get_lastsnapshot();
	Vnsnapshot  get_lastsnapshot(std::string);


private:

	std::map<std::string,std::list<Vnsnapshot> >	_optionqueue;
	std::map<std::string,Vnsnapshot>				_optionsnapshot;
	Vnsnapshot										_lastsnapshot;
	unsigned int									_maxqueuelength;

};
#endif