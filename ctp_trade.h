#ifndef CTP_TRADE
#define CTP_TRADE
#include "./ctp/ThostFtdcTraderApi.h"
#include<string>
#include<map>

class ctp_trade : public CThostFtdcTraderSpi
{
public:
    ctp_trade();
    void init();//set con file  dir
    char * mk_trade_con_dir();

    virtual void OnFrontConnected();
    virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    virtual void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    virtual void OnFrontDisconnected(int nReason);
    virtual void OnHeartBeatWarning(int nTimeLapse);
    virtual void OnRtnOrder(CThostFtdcOrderField *pOrder);
    virtual void OnRtnTrade(CThostFtdcTradeField *pTrade);





private:
    void ReqQryOrder();
    void QryOrder();
    bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo);
    bool IsMyOrder(CThostFtdcOrderField *pOrder);
    bool IsTradingOrder(CThostFtdcOrderField *pOrder);
    void ReqUserLogin();
    void ReqSettlementInfoConfirm();
    void ReqQryInstrument();
    void ReqQryTradingAccount();
    void ReqQryInvestorPosition();
    void ReqOrderInsert();
    void ReqOrderAction(CThostFtdcOrderField *pOrder);

    CThostFtdcTraderApi                     * pUserApi;
    CThostFtdcReqUserLoginField       * req;
    TThostFtdcFrontIDType                FRONT_ID;	//«∞÷√±‡∫≈
    TThostFtdcSessionIDType             SESSION_ID;	//ª·ª∞±‡∫≈

    long iRequestID;
    std::map<std::string,CThostFtdcOrderField*> ordermap;

};
#endif // CTP_TRADE_H
