#ifndef ORDERLIST
#define ORDERLIST

#include<map>
#include<list>
#include"order.h"
//主要功能
//管理order在ME中的进进出出

//fp可以修改order队列
//tactic通过调用public里的函数 实现增减order


class fillpolicy;

class orderlist
{

public:
	
	friend class fillpolicy;
	
	orderlist();
	std::string neworder(std::string symbol,std::string buysell,double price,long size);//strategy call// new an order
	void changeorder(std::string ordername);//strategy call// change size price etc

	void fillorder(std::string ordername);//fp call //when order filled
	void statuschange(std::string ordername,std::string atatus_info);//fp call //when changeorder's feed back

private:
	std::map <std::string,order *> _pend_order;
	std::map <std::string,order *> _run_order;
	std::map <std::string,order *> _done_order;
	long _ordercount;
};

#endif
//提供两种接口  分别是给fp使用及发单程序使用
//如何使程序也可在ctp上使用 

//直接在ctp里的callback中调用对应函数
//这类似于在fp中写好函数

//ctp写好后，仅改变dll名字即可测试新策略
//测试环境同ctp

//?这是否等价于对于任意一个ctp callback 都要写对应函数
//?如此看来亦须对照飞马与ctp 方可写得
//CTP 飞马中的函数包罗万象，只能简化为之。


//各种config信息，数据源等 通过config文件or直接命令行指定

