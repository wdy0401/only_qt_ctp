#include "ctp_order_manager.h"
#include"mainwindow.h"
#include<QMessageBox>

#include<iostream>

#include"../gpp_qt/wfunction/wfunction.h"

#include"../../libs/ctp/ThostFtdcTraderApi.h"

extern MainWindow * mw;

using namespace std;

void ctp_order_manager::init()
{
    _ordercount=0;
}
void ctp_order_manager::show_warning(const string & warninfo)
{
    cerr << "Warning from ctp_order_manager" << endl;
    cerr << warninfo <<endl;
}
std::string ctp_order_manager::new_order(const std::string symbol,const std::string buysell, const std::string & openclose ,double price,long size)
{
    string ordername="";
    return ordername;
}
void ctp_order_manager::cancel_order(const std::string & ordername)
{

}
void ctp_order_manager::change_order(const std::string & ordername,const std::string & change_cancel,double changeto)
{

}
void ctp_order_manager::OnRtnOrder(CThostFtdcOrderField *p)
{
    cerr << endl << "--->>> OnRtnOrder" <<endl;
    string mapid=wfunction::itos(p->FrontID)+"_"+wfunction::itos(p->SessionID)+"_"+p->OrderRef;
/*
    switch (p->OrderStatus)
    {
    ///全部成交
    case THOST_FTDC_OST_AllTraded: orderid_op.erase(mapid); break;
    ///部分成交还在队列中
    case THOST_FTDC_OST_PartTradedQueueing:break;
    ///部分成交不在队列中
    case THOST_FTDC_OST_PartTradedNotQueueing: orderid_op.erase(mapid); break;
    ///未成交还在队列中
    case THOST_FTDC_OST_NoTradeQueueing: break;
    ///未成交不在队列中
    case THOST_FTDC_OST_NoTradeNotQueueing: orderid_op.erase(mapid); break;
    ///撤单
    case THOST_FTDC_OST_Canceled: orderid_op.erase(mapid); break;
    ///未知， 表示 Thost已经接受用户 的委托指令，还没有 转发到交易所
    case THOST_FTDC_OST_Unknown: orderid_op[mapid] = p; break;
    ///尚未触发
    case THOST_FTDC_OST_NotTouched: break;

    }
  */
    cerr << "map id\t" << mapid << endl;
    cerr << "FrontID\t" << p->FrontID << endl;
    cerr << "SessionID\t" << p->SessionID << endl;
    cerr << "OrderRef\t" << p->OrderRef << endl;
    cerr << "OrderStatus\t" << p->OrderStatus << endl;
    cerr << "iRequestID\t" << p->RequestID << endl;
    show_warning("Warning from OnRtnOrder");

//    cerr << "OrderRef" << p->OrderRef << endl;


    //
    //继续添加功能
    //
}
void ctp_order_manager::OnRtnTrade(CThostFtdcTradeField *pTrade)
{

}
