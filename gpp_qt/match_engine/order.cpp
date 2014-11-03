#include"order.h"
#include"../wtimer/wtimer.h"
#include"../wfunction/wfunction.h"
#include"../log_info/log_info.h"
//主要功能
//管理order的生老病死

using namespace std;

extern wtimer tm;
extern log_info loginfo;


void order::initorder(const std::string &symbol, const std::string &buysell, double price, long size)//IF buy 2200 3 100(ordid)
{
	_symbol=symbol;
	_buysell=buysell;
	_price=price;
	_size=size;
	
	_tm=tm.nowtic();
	_eventid=1;
	
	_sizetofill=size;
	_sizefilled=0;
	_alreadyfilled=0;
	
	_tag_cancel=false;
	_tag_changesize=0;
	_tag_changeprice=0;
} 
void order::setorderid(long id)
{
	_orderid=id;	
}
void order::orderfill(long fillsize)
{
	if (fillsize==_sizetofill)
	{
		_eventid++;
		_sizetofill=0;
		_sizefilled=_size;
		_alreadyfilled=1;

		tmpinfo="";
		tmpinfo+="Filldone Fillsize ";
		tmpinfo+=wfunction::itos(fillsize);
		tmpinfo+=" orderid ";
		tmpinfo+=wfunction::itos(_orderid);
		tmpinfo+="\n";
		loginfo.writeinfo(tmpinfo);
		return;
	}	
	if (fillsize>_sizetofill)
	{
		_eventid++;
		_sizetofill=0;
		_sizefilled=_size+fillsize-_sizetofill;
		_alreadyfilled=1;

		_sizeoverfilled=fillsize-_sizetofill;

		tmpinfo="";
		tmpinfo+="ERROR overfilled Fillsize ";
		tmpinfo+=wfunction::itos(_sizeoverfilled);
		tmpinfo+=" orderid ";
		tmpinfo+=wfunction::itos(_orderid);
		tmpinfo+="\n";
		loginfo.writeinfo(tmpinfo);
		return;
	}
	if (fillsize<_sizetofill)
	{
		_eventid++;
		_sizetofill=_sizetofill-fillsize;
		_sizefilled=fillsize;
		_alreadyfilled=0;

		tmpinfo="";
		tmpinfo+="Fill_partial Fillsize ";
		tmpinfo+=wfunction::itos(fillsize);
		tmpinfo+=" orderid ";
		tmpinfo+=wfunction::itos(_orderid);
		tmpinfo+="\n";
		loginfo.writeinfo(tmpinfo);
		return;
	}
}
void order::cancelorder()//需要fp提供回馈以判断是否成功
{
	_eventid++;

	_tag_cancel=true;
	
	tmpinfo="";
	tmpinfo+="Cancel order send. Orderid ";
	tmpinfo+=wfunction::itos(_orderid);
	tmpinfo+="\n";
	loginfo.writeinfo(tmpinfo);
}
void order::changesize(long size)//需要fp提供回馈以判断是否成功
{
	_eventid++;
	
	_tag_changesize=size;
	
	tmpinfo="";
	tmpinfo+="Change order size. Orderid ";
	tmpinfo+=wfunction::itos(_orderid);
	tmpinfo+="Origin size";
	tmpinfo+=wfunction::itos(_sizetofill);
	tmpinfo+="Change size";
	tmpinfo+=wfunction::itos(size);
	tmpinfo+="\n";
	loginfo.writeinfo(tmpinfo);
}
void order::changeprice(double price)//需要fp提供回馈以判断是否成功
{
	_eventid++;
	
	_tag_changeprice=price;

	tmpinfo="";
	tmpinfo+="Change order price. Orderid ";
	tmpinfo+=wfunction::itos(_orderid);
	tmpinfo+="Origin price";
	tmpinfo+=wfunction::ftos(_price);
	tmpinfo+="Change price";
	tmpinfo+=wfunction::ftos(price);
	tmpinfo+="\n";
	loginfo.writeinfo(tmpinfo);
}
void order::changerej(const std::string & message)
{
	if(message=="cancel")
	{
		_tag_cancel=false;
		
		tmpinfo="";
		tmpinfo+="Cancel failed. Orderid ";
		tmpinfo+=wfunction::itos(_orderid);
		tmpinfo+="\n";
		loginfo.writeinfo(tmpinfo);
		
		return;
	}
	if(message=="price")
	{
		_tag_changeprice=0;
		
		tmpinfo="";
		tmpinfo+="Change price failed. Orderid ";
		tmpinfo+=wfunction::itos(_orderid);
		tmpinfo+="\n";
		loginfo.writeinfo(tmpinfo);
				
		return;
	}
	if(message=="size")
	{
		_tag_changesize=0;
		
		tmpinfo="";
		tmpinfo+="Change size failed. Orderid ";
		tmpinfo+=wfunction::itos(_orderid);
		tmpinfo+="\n";
		loginfo.writeinfo(tmpinfo);
		
		return;
	}
}

void order::changedone(const std::string & message)
{
	
	if(message=="cancel")
	{
		_eventid++;
		
		_tag_cancel=false;		
		_size=_alreadyfilled;

		tmpinfo="";
		tmpinfo+="Cancel done. Orderid ";
		tmpinfo+=wfunction::itos(_orderid);
		tmpinfo+="\n";
		loginfo.writeinfo(tmpinfo);
		
		return;
	}
	if(message=="price")
	{
		_eventid++;
		
		_price=_tag_changeprice;
		_tag_changeprice=0;
				
		tmpinfo="";
		tmpinfo+="Change price done. Orderid ";
		tmpinfo+=wfunction::itos(_orderid);
		tmpinfo+=" Price change to ";
		tmpinfo+=wfunction::ftos(_price);
		tmpinfo+="\n";
		loginfo.writeinfo(tmpinfo);
				
		return;
	}
	//先处理fill 后处理done 可避免 提交时与确认时fillsize可能不一样的问题
	if(message=="size")
	{
		
		_eventid++;

		_size=_sizefilled+_tag_changesize;
		_sizetofill=_tag_changesize;
		_tag_changesize=0;
		
		tmpinfo="";
		tmpinfo+="Change size done. Orderid ";
		tmpinfo+=wfunction::itos(_orderid);
		tmpinfo+="\n";
		loginfo.writeinfo(tmpinfo);
		
		return;
	}
}
void order::changeack(const std::string & message)
{
	
	if(message=="cancel")
	{
		_eventid++;

		tmpinfo="";
		tmpinfo+="Cancel ack. Orderid ";
		tmpinfo+=wfunction::itos(_orderid);
		tmpinfo+="\n";
		loginfo.writeinfo(tmpinfo);
		
		return;
	}
	if(message=="price")
	{
		_eventid++;
		
		tmpinfo="";
		tmpinfo+="Change price ack. Orderid ";
		tmpinfo+=wfunction::itos(_orderid);
		tmpinfo+="\n";
		loginfo.writeinfo(tmpinfo);
				
		return;
	}
	if(message=="size")
	{
		_eventid++;
		
		tmpinfo="";
		tmpinfo+="Change size ack. Orderid ";
		tmpinfo+=wfunction::itos(_orderid);
		tmpinfo+="\n";
		loginfo.writeinfo(tmpinfo);
		
		return;
	}
}
