#ifndef CTP_TRADE_QTHREAD
#define CTP_TRADE_QTHREAD
#include<QThread>
#include"ctp_trade.h"

#include"ctp_order_manager.h"

class ctp_trade_qthread :public QThread
{
	Q_OBJECT
public:
    bool check_init_para();
    ctp_trade * get_tradep(){return trade;}
    void init();

public slots:
    void delete_all_pending_order();
    void check_add_order(const std::string &,const std::string &,const std::string &,const std::string &,const std::string &);

signals:protected:
    void run();

private:
    ctp_trade * trade;
};
#endif
