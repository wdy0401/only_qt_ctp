#ifndef CTP_ORDER_MANAGER_H
#define CTP_ORDER_MANAGER_H


#include"ctp_order.h"

#include<list>
#include<map>
#include<string>

#include<QObject>

#include"../libs/ctp/ThostFtdcTraderApi.h"

class fillpolicy;

class ctp_order_manager :public QObject
{
    Q_OBJECT
    friend class fillpolicy;
public:
    void init();
    std::string new_order(const std::string symbol,const std::string buysell, const std::string & openclose ,double price,long size);//strategy call// new an order
    void cancel_order(const std::string & ordername);
    void change_order(const std::string & ordername,const std::string & change_cancel,double changeto);//strategy call// change size price etc
    //还可加入查询order状态的函数

public slots:
    void show_warning(const std::string &);
    void OnRtnOrder(CThostFtdcOrderField *pOrder);
    void OnRtnTrade(CThostFtdcTradeField *pTrade);

signals:

private:
    std::map <std::string, std::list<long>> _ordername_iRequestID;
    std::map <long, std::string> _iRequestID_ordername;
    std::map <long, CThostFtdcOrderField *> _iRequestID_porder;
    std::map <long, CThostFtdcTradeField *> _iRequestID_porder_trade;


    std::map <std::string,ctp_order *> _pend_order;
    std::map <std::string,ctp_order *> _run_order;
    std::map <std::string,ctp_order *> _done_order;
    long _ordercount;

    TThostFtdcFrontIDType           FRONT_ID;
    TThostFtdcSessionIDType         SESSION_ID;
};

#endif
