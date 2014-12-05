#ifndef CTP_TRADE_QTHREAD
#define CTP_TRADE_QTHREAD
#include<QThread>
#include"ctp_trade.h"
class ctp_trade_qthread :public QThread
{
	Q_OBJECT
public:
    ctp_trade_qthread();

public slots:
    void addorder();

signals:protected:
    void run();
    ctp_trade * trade;
};

#endif
