#include<map>
#include"match_engine.h"
#include"../wtimer/wtimer.h"
#include"../log_info/log_info.h"
#include"../fillpolicy/fillpolicy.h"
#include"../trans_event/trans_event.h"
#include"protobuf/stdafx.h"
#include"protobuf/quote.pb.h"

using namespace std;
using namespace QUOTE;

extern log_info loginfo;
extern trans_event te;

match_engine::match_engine()
{
	_fp.pme=this;
}
bool match_engine::loadtactic(std::string & tacticname)
{
    loginfo.writeinfo(tacticname);
    return 0;
}
bool match_engine::loadfillpolicy(std::string & fpname)
{
    loginfo.writeinfo(fpname);
    return 0;
}
void match_engine::setnowsymbol(const std::string & symbol)
{
	_nowsymbol=symbol;
}
void match_engine::rec_update(const std::string & symbol, const std::string & ba, long level, double price, long size)
{
	setnowsymbol(symbol);
	updateorderbook(symbol,ba,level,price,size);
	updatefp();
	updatetactic(symbol,ba,level,price,size);
	updatetacticbooks();
}
void match_engine::updateorderbook(const std::string & symbol, const std::string & ba, long level, double price, long size)//IF1405 bid 1 2100.2 5
{
	//auto it=_orderbooks.find(symbol);
	std::map<std::string,orderbook>::iterator iter=_orderbooks.find(symbol);
	if(iter==_orderbooks.end())//尚未添加此symbol之book
	{
		orderbook tmpob;
		tmpob.setsymbol(symbol);
		tmpob.updateorderbook(ba,level,price,size);
		_orderbooks[symbol]=tmpob;		
	}
	else
	{
		iter->second.updateorderbook(ba,level,price,size);
	}
	
}

void match_engine::updatefp()//改写orderlist各个order的状态
{
	_fp.updateorderlist(_ol,_orderbooks.find(_nowsymbol)->second);
}

void match_engine::updatetactic(const std::string & symbol, const std::string & ba, long level, double price, long size)//根据新的orderbook来判断时候发送order
{
	te.trans_quote(symbol,ba,level,price,size);
	te.fetch_tactic_info();
	//const orderlist & ol,const orderbook & ob
}
void match_engine::updatetacticbooks()//根据新的orderbooks来判断时候发送order
{
	//const orderlist & ol,const orderbook & ob
}
void match_engine::add_order(const std::string & symbol,const std::string & buysell, double price ,long size)
{
    std::cout<<symbol<<" "<<buysell<<" "<<price<<" "<<size<<std::endl;
	this->_ol.neworder(symbol,buysell,price,size);
}
void match_engine::add_order(const string & orderstr)
{
	_order_message.ParseFromString(orderstr);
	string buysell=_order_message.buysell()==0?"buy":"sell";
	add_order(_order_message.symbol(),buysell,_order_message.price(),_order_message.size());
}

void match_engine::fp_te_tactic_order_send_ack(const std::string & orderid)
{
	te.order_send_ack(orderid);
	return;
}

void match_engine::fp_te_tactic_order_change_size_ack(const std::string & orderid, long size)
{
	te.order_change_size_ack(orderid,size);
	return;
}
void match_engine::fp_te_tactic_order_change_price_ack(const std::string & orderid, double price)
{
	te.order_change_price_ack(orderid, price);
	return;
}

void match_engine::fp_te_tactic_order_fill(const std::string & orderid,long fillsize)
{
	te.order_fill(orderid,fillsize);
	return;
}

void match_engine::fp_te_tactic_order_change_size_rej(const std::string & orderid, long size)
{
	te.order_change_size_rej(orderid,size);
	return;
}

void match_engine::fp_te_tactic_order_change_price_rej(const std::string & orderid, double price)
{
	te.order_change_price_rej(orderid,price);
	return;
}

void match_engine::fp_te_tactic_order_change_size_done(const std::string & orderid, long size)
{
	te.order_change_size_done(orderid,size);
	return;
}
void match_engine::fp_te_tactic_order_change_price_done(const std::string & orderid, double price)
{
	te.order_change_price_done(orderid,price);
	return;
}
