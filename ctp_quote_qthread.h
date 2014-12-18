#ifndef CTP_QUOTE_QTHREAD
#define CTP_QUOTE_QTHREAD
#include<QThread>
#include"ctp_quote.h"
#include"ctp_order_manager.h"
#include"../ctp/ThostFtdcMdApi.h"
class ctp_quote_qthread:public QThread
{
    Q_OBJECT
public:
    ctp_quote_qthread();
    void init();
    void set_ctp_order_manager(ctp_order_manager * p){order_manager=p;}
signals:
    void broadcast_marketdata(CThostFtdcDepthMarketDataField *pDepthMarketData);
protected:
    void run();
private:
    ctp_quote * quote;
    ctp_order_manager * order_manager;
};

#endif // CTP_QUOTE_QTHREAD
