#ifndef CTP_QUOTE_QTHREAD
#define CTP_QUOTE_QTHREAD
#include<QThread>
#include"ctp_quote.h"
#include"../ctp/ThostFtdcMdApi.h"
class ctp_quote_qthread:public QThread
{
    Q_OBJECT
public:
    ctp_quote_qthread();
    void init();
signals:
    void broadcast_marketdata(CThostFtdcDepthMarketDataField *pDepthMarketData);
protected:
    void run();
private:
    ctp_quote * quote;
};

#endif // CTP_QUOTE_QTHREAD
