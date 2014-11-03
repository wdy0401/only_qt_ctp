#include"fillpolicy.h"
#include"../match_engine/match_engine.h"
#include"../wtimer/wtimer.h"
#include"../trans_event/trans_event.h"


//extern wtimer tm;

extern trans_event te;
using namespace std;
//updateorderlist时将消息放入某容器，待全部order处理后 发出消息
//对于tactic来说 会立刻得到fp的信息并反馈
//tactic 先得到fp的信息 后得到quote的信息 在截面数据的情形下是正确的 在实时情形下也应是正确的

//next add te part

void fillpolicy::updateorderlist(orderlist & ol,orderbook & ob)
{
	//消息fill					检测run上有哪些order可成交 成交之 
	//转区fill					将成交完成的移入done list
	//消息change ack rej done	检测run done这两个list中的change tag 并处理之
	//转区						将pend区转换到run区
	
	//消息fill
	//转区fill
	for(map<string,order *>::iterator iter=ol._run_order.begin(); iter!=ol._run_order.end();)
	{
		if((iter->second->_price>=ob.getaskprice() && iter->second->_buysell=="buy") || (iter->second->_price<=ob.getbidprice() &&iter->second->_buysell=="buy"))
		{
			iter->second->orderfill(iter->second->_sizetofill);
			ol._done_order[iter->first]=iter->second;
			ol._run_order.erase(iter++);
			//pme->fp_te_tactic_fill("");
		}
		else
		{
			++iter;
		}
	}
	
	//消息change
	//成功部分
	for(map<string,order *>::iterator iter=ol._run_order.begin(); iter!=ol._run_order.end();)
	{
		if(iter->second->_tag_cancel)
		{
			iter->second->changeack("cancel");
			ol._done_order[iter->first]=iter->second;
			iter->second->changedone("cancel");
			ol._run_order.erase(iter++);
			continue;
		}
		else
		{
			++iter;
			continue;
		}
		if(iter->second->_tag_changeprice)
		{
			iter->second->changeack("price");
			iter->second->_price=iter->second->_tag_changeprice;
			iter->second->changedone("price");
		}
		if(iter->second->_tag_changesize)
		{
			
			iter->second->changeack("size");
			iter->second->_price=iter->second->_tag_changesize;
			iter->second->changedone("size");
		}
		++iter;
	}
	//失败部分
	for(map<string,order *>::iterator iter=ol._done_order.begin();iter!=ol._done_order.end();iter++)
	{
		if(iter->second->_tag_cancel)
		{
			iter->second->changeack("cancel");
			iter->second->changerej("cancel");
		}
		if(iter->second->_tag_changeprice)
		{
			iter->second->changeack("price");
			iter->second->changerej("price");
		}
		if(iter->second->_tag_changesize)
		{
			iter->second->changeack("size");
			iter->second->changerej("size");
		}
	}

	//转区pend 并清空
	for(map<string,order *>::iterator iter=ol._pend_order.begin();iter!=ol._pend_order.end();iter++)
	{
		ol._run_order[iter->first]=iter->second;
	}
	ol._pend_order.clear();

	return;
}
	
