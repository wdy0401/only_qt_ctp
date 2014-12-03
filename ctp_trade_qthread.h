#ifndef CTP_TRADE_QTHREAD
#define CTP_TRADE_QTHREAD
#include<QThread>
//#include"../ctp/ThostFtdcMdApi.h"
class ctp_trade_qthread :public QThread
{
	Q_OBJECT
public:
	ctp_trade_qthread();
signals:
//	void broadcast_markerdata(CThostFtdcDepthMarketDataField *pDepthMarketData);
protected:
	void run();
};

#endif