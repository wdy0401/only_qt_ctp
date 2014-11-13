#ifndef CTP_QUOTE
#define CTP_QUOTE

#include"ctp/ThostFtdcMdApi.h"
#include<QThread>
#define MAX_CONTRACT_NUMBER 1024
#define MAX_CONTRACT_NAME 1024

class ctp_quote_qthread;

class ctp_quote : public CThostFtdcMdSpi
{
public:
    ctp_quote();
    ctp_quote(ctp_quote_qthread *);
    void init();
    void login(CThostFtdcMdApi *);
	void ReqUserLogin();

    void OnRspError(CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast);
	void OnFrontDisconnected(int nReason);
	void OnFrontConnected();
    void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);
    void SubscribeMarketData();

    bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo);
	
private:
	CThostFtdcReqUserLoginField * req;
	int nRequestID;
	char * * ppInstrumentID;
	int nppInstrumentID;
    CThostFtdcMdApi * pUserApi;

	int ctp_time_length;
    ctp_quote_qthread * pfather;
};

#endif
