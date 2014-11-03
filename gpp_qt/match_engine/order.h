#ifndef ORDER
#define ORDER

#include<string>
#include<map>
#include<set>
//主要功能
//管理order的生老病死


class orderlist;

class order
{

friend class orderlist;
friend class fillpolicy;

public:
		
	//tactic发起
	void initorder(const std::string &, const std::string &, double, long); //IF buy 2200 3 //ordid and timer will be added later
	void cancelorder();
	void changesize(long);
	void changeprice(double);

	//ME发起
	//void setorderid(long); //ME维护时间线 不维护orderlist;

	//fp发起
	void setorderid(long);
	void orderfill(long);
	void changerej(const std::string &);
	void changedone(const std::string &);
	void changeack(const std::string &);
	
private:
	//order基础信息
	long _orderid;//orderlist负责处理
	std::string _symbol;
	std::string _buysell;//buy sell btc//buy to cover stc//sell to cover
	double _price;
	long _size;
	double _tm;

	//order动态信息
	std::string tmpinfo;
	long _queueposition;
	long _sizefilled;
	long _sizetofill;
	long _eventid;//每个事件 有个id 递增

	//order错误fill信息
	long _sizeoverfilled;
	long _sizelackfilled;
	
	//记录order是否完全fill
	bool _alreadyfilled;

	//修改种类，此处存放待修改的内容
	bool _tag_cancel;
	long _tag_changesize;
	double _tag_changeprice;
	
	//增强扩展性 记录各类事件   事件类型_时间   时间各个特点
	std::map<std::string,std::set<std::string> >	_eachcharacter; //other information

};

#endif
