#ifndef CTP_LOG_H
#define CTP_LOG_H

#include"../libs/ctp/ThostFtdcMdApi.h"
#include"../gpp_qt/log_info/log_info.h"

#include<QObject>

class ctp_log :public QObject , public log_info
{
    Q_OBJECT
public:
    ctp_log();
public slots:
    void writeinfo(CThostFtdcDepthMarketDataField *pDepthMarketData);
};

#endif // CTP_LOG_H
