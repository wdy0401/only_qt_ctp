#ifndef CTP_MANAGE_H
#define CTP_MANAGE_H

class ctp_manage
{
public:
    ctp_manage();

    bool check_quote_init_para();
    bool check_trade_init_para();
    void start_ctp_quote();
    void start_ctp_trade();

    //    bool ctp_manage::ctp_quote_running(){return ctp_quote_running;}
    //    bool ctp_manage::ctp_trade_running(){return ctp_trade_running;}
    bool is_quote_running(){return ctp_quote_running;}
    bool is_trade_running(){return ctp_trade_running;}

private:
    bool ctp_quote_running;
    bool ctp_trade_running;
};

#endif // CTP_MANAGE_H
