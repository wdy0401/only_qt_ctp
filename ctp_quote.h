#ifndef CTP_QUOTE
#define CTP_QUOTE

#include"ctp/ThostFtdcMdApi.h"

#define MAX_CONTRACT_NUMBER 1024
#define MAX_CONTRACT_NAME 1024

class ctp_quote : public CThostFtdcMdSpi
{
public:
	void init();
	void login(CThostFtdcMdApi *);
	void ReqUserLogin();
	void OnRspError(CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast);

	///        0x2003 收到错误报文
	void OnFrontDisconnected(int nReason);

	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	void OnFrontConnected();
	
	///登录请求响应
	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///订阅行情应答
	void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///取消订阅行情应答
	void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///深度行情通知
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
};

#endif