#include "ctp_order.h"
#include"ctp_order_manager.h"
ctp_order::ctp_order(CThostFtdcInputOrderField * p,ctp_order_manager * pcom)
{
    FrontID=pcom->get_front_id();
    SessionID=pcom->get_session_id();
    of=new CThostFtdcOrderField;
    strcpy(of->OrderRef,p->OrderRef);
    strcpy(of->InvestorID,p->InvestorID);
    strcpy(of->UserID,p->UserID);
    strcpy(of->InstrumentID,p->InstrumentID);
}
void ctp_order::set_uniq_order(CThostFtdcOrderField *p)
{
    strcpy(of->OrderRef,p->OrderRef);
    of->BrokerOrderSeq = p->BrokerOrderSeq;
    strcpy(of->ExchangeID ,  p->ExchangeID);
    strcpy(of->TraderID ,  p->TraderID);
    strcpy(of->OrderLocalID ,  p->OrderLocalID);
    strcpy(of->OrderSysID ,  p->OrderSysID);
	of->OrderStatus=p->OrderStatus;
}
void ctp_order::set_uniq_trade(CThostFtdcTradeField *p)
{
    strcpy(of->OrderRef,p->OrderRef);
    of->BrokerOrderSeq = p->BrokerOrderSeq;
    strcpy(of->ExchangeID ,  p->ExchangeID);
    strcpy(of->TraderID ,  p->TraderID);
    strcpy(of->OrderLocalID ,  p->OrderLocalID);
    strcpy(of->OrderSysID ,  p->OrderSysID);
}
//这是确定order的组合

//FrontID
//SessionID
//OrderRef

//BrokerID
//BrokerOrderSeq

//exchangeID
//traderID
//OrderLocalID

//exchangeID
//OrderSysID
