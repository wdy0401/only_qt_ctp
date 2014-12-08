#ifndef CTP_TRADE_CFG_H
#define CTP_TRADE_CFG_H

#include<../ctp/ThostFtdcTraderApi.h>
#include<string>
#include<map>


class ctp_trade_qthread;
class ctp_trade_cfg
{
public:
        ctp_trade_cfg();
        CThostFtdcTraderApi				* pUserApi;
        TThostFtdcFrontIDType           FRONT_ID;
        TThostFtdcSessionIDType         SESSION_ID;
        ctp_trade_qthread * ptfather ;

        int maxdelaytime;

        //可以添加iRequestID对应的map 以便于查询order状态
        std::map<std::string, std::string> ordername_orderid; //user set id -> uniqid
        std::map<std::string, CThostFtdcOrderField*> orderid_op; //uniqid -> orderfield
        std::map<long, std::string> rid_orderid; //requestid -> uniqid
};

#endif // CTP_TRADE_CFG_H
