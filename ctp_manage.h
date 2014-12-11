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

};

#endif // CTP_MANAGE_H
