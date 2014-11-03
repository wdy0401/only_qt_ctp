#include"orderlist.h"
#include"../wfunction/wfunction.h"

using namespace std;

orderlist::orderlist()
{
	_ordercount=0;
}
string orderlist::neworder(std::string symbol,std::string buysell,double price,long size)
{
	_ordercount++;
	string ordername=symbol+wfunction::itos(_ordercount);
	order * porder=new order;
	porder->initorder(symbol,buysell,price,size);
	porder->setorderid(_ordercount);
	_pend_order[ordername.c_str()]=porder;
	return ordername;
}