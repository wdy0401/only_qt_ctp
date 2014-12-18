#ifndef CTP_MANAGER_H
#define CTP_MANAGER_H
#include"tactic.h"
#include"ctp_order_manager.h"
#include"mainwindow.h"
#include"QObject"
class ctp_manager:public QObject
{
    Q_OBJECT
public:

    void init();
    bool check_quote_init_para();
    bool check_trade_init_para();
    void start_ctp_quote();
    void start_ctp_trade();

    bool is_quote_running(){return ctp_quote_running;}
    bool is_trade_running(){return ctp_trade_running;}

    void set_ctp_order_mamager(ctp_order_manager * p){om=p;}
    void set_tactic(tactic * p){tc=p;}
    void set_mainwindow(MainWindow *p){mw=p;}

    MainWindow * get_mainwindow(){return mw;}
    ctp_order_manager * get_ctp_order_mamager(){return om;}

public slots:
    void run_tactic();

private:
    bool ctp_quote_running;
    bool ctp_trade_running;

    MainWindow *mw;
    ctp_order_manager * om;
    tactic * tc;
};

#endif // CTP_MANAGE_H
