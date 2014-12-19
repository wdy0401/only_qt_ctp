#ifndef CTP_ORDER_H
#define CTP_ORDER_H

#include"../libs/ctp/ThostFtdcTraderApi.h"
class ctp_order_manager;
class ctp_order
{
public:
    ctp_order(CThostFtdcInputOrderField * p,ctp_order_manager * pcom);
    void set_uniq_order(CThostFtdcOrderField *pOrder);
    void set_uniq_trade(CThostFtdcTradeField *pTrade);

//这是确定order的组合

    TThostFtdcFrontIDType FrontID;
    TThostFtdcSessionIDType SessionID;
    CThostFtdcOrderField * of;
};

#endif // CTP_ORDER_H
