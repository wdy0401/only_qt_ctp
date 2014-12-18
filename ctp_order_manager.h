#ifndef CTP_ORDER_MANAGER_H
#define CTP_ORDER_MANAGER_H

#include"ctp_order.h"
#include"ctp_trade.h"
#include"tactic.h"

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
    void set_tactic(tactic * );
    void set_trade(ctp_trade *);
    std::string new_order(const std::string symbol,const std::string buysell, const std::string & openclose ,double price,long size);
    void cancel_order(const std::string & ordername);
    void change_order(const std::string & ordername,double price,long size);
    //还可加入查询order状态的函数

public slots:
    void show_warning(const std::string &);
    void rec_quote(const std::string & symbol, const std::string & ba, long level, double price, long size);
    void OnRtnOrder(CThostFtdcOrderField *pOrder);
    void OnRtnTrade(CThostFtdcTradeField *pTrade);
    void OnLogin(CThostFtdcRspUserLoginField *pRspUserLogin);

signals:
    void ack(const std::string & ordername,const std::string & type,const std::string & info);
    void done(const std::string & ordername,const std::string & type,const std::string & info);
    void rej(const std::string & ordername,const std::string & type,const std::string & info);
    void fill(const std::string & ordername,long size);
    void send_quote(const std::string & symbol, const std::string & ba, long level, double price, long size);

private:
    std::map <std::string, std::list<long>> _ordername_iRequestID;
    std::map <long, std::string> _iRequestID_ordername;
    std::map <long, CThostFtdcOrderField *> _iRequestID_porder;
    std::map <long, CThostFtdcTradeField *> _iRequestID_porder_trade;

    std::map <std::string,ctp_order *> _pend_order;
    std::map <std::string,ctp_order *> _run_order;
    std::map <std::string,ctp_order *> _done_order;
    long _ordercount;

    TThostFtdcFrontIDType       FRONT_ID;
    TThostFtdcSessionIDType    SESSION_ID;

    std::map<std::string, std::string> ordername_orderid; //user set id -> uniqid
    std::map<std::string, CThostFtdcOrderField*> orderid_op; //uniqid -> orderfield
    std::map<long, std::string> rid_orderid; //requestid -> uniqid

    tactic * tc;
    ctp_trade * trade;
    CThostFtdcInputOrderField * initorder(const std::string & InstrumentID, const std::string & side, const std::string & openclose, double price, long size);
    CThostFtdcInputOrderActionField * initorderchange(const std::string & ordername);
};

#endif
