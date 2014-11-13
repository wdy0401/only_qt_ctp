#ifndef CTP_QUOTE_QTHREAD
#define CTP_QUOTE_QTHREAD
#include<QThread>
#include"../ctp/ThostFtdcMdApi.h"
class ctp_quote_qthread:public QThread
{
    Q_OBJECT
public:
    ctp_quote_qthread();
signals:
    void broadcast_markerdata(CThostFtdcDepthMarketDataField *pDepthMarketData);
protected:
    void run();
};

#endif // CTP_QUOTE_QTHREAD
