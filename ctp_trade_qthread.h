#ifndef CTP_TRADE_QTHREAD
#define CTP_TRADE_QTHREAD
#include<QThread>
#include"mainwindow.h"
#include"ctp_trade.h"
#include"ctp_order_manager.h"

class ctp_trade_qthread :public QThread
{
	Q_OBJECT
public:
    bool check_init_para();
    void set_mainwindow(MainWindow *p){mw=p;}
    ctp_trade * get_tradep(){return trade;}
    void set_ctp_order_manager(ctp_order_manager * p){order_manager=p;}
    void init();

public slots:
    void check_add_order(const std::string &,const std::string &,const std::string &,const std::string &,const std::string &);

signals:protected:
    void run();

private:
    ctp_trade * trade;
    ctp_order_manager * order_manager;
    MainWindow * mw;
};
#endif
