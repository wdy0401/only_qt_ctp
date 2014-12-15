#ifndef CTP_TRADE
#define CTP_TRADE
#include "../libs/ctp/ThostFtdcTraderApi.h"
#include<string>
#include<map>
#include<QObject>

class ctp_trade_qthread;
class ctp_trade : public QObject, public CThostFtdcTraderSpi
{
    Q_OBJECT
public:
//	ctp_trade();
    void init(ctp_trade_qthread *);
    void init();//set con file  dir
    char * mk_trade_con_dir();
    void testfunc();

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

    void ReqQryOrder(const std::string &);
    void ReqQryOrder(const std::string &,bool);
    void ReqQryInstrument(const std::string & );
    void ReqQryInstrument(const std::string & ,bool);
    void ReqQryInvestorPosition(const std::string &);
    void ReqQryInvestorPosition(const std::string & ,bool);

	void ReqQryTradingAccount(bool);
    void ReqQryTradingAccount();
    bool IsFlowControl(int );
    bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo);
    bool IsMyOrder(CThostFtdcOrderField *pOrder);
    bool IsTradingOrder(CThostFtdcOrderField *pOrder);
    void ReqUserLogin();
    void ReqSettlementInfoConfirm();
    void ReqQryInvestorPosition();
	
	void ReqOrderInsert(CThostFtdcInputOrderField *);
	CThostFtdcInputOrderField * initorder(const std::string & InstrumentID, const std::string & side, const std::string & openclose, double price, long size);
	void ReqOrderAction(CThostFtdcInputOrderActionField *pOrder);
	CThostFtdcInputOrderActionField * initorderchange(const std::string & ordername);

signals:
    void show_warning(const std::string &);

public slots:
    //发单函数
    void addorder(const std::string & InstrumentID, const std::string & side, const std::string & openclose, double price, long size);
    void change_order(const std::string & ordername, double price, long size);
    void delete_order(const std::string & ordername);
    void delete_all_order();

private:
    CThostFtdcTraderApi * pUserApi;
    TThostFtdcFrontIDType           FRONT_ID;
    TThostFtdcSessionIDType         SESSION_ID;
    int maxdelaytime;
    int iRequestID;
    ctp_trade_qthread * ptfather ;
    //可以添加iRequestID对应的map 以便于查询order状态
    std::map<std::string, std::string> ordername_orderid; //user set id -> uniqid
    std::map<std::string, CThostFtdcOrderField*> orderid_op; //uniqid -> orderfield
    std::map<long, std::string> rid_orderid; //requestid -> uniqid

};
#endif // CTP_TRADE_H
