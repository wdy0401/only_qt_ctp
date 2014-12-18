#include "ctp_quote_qthread.h"
#include "ctp_quote.h"
#include"ctp_order_manager.h"

ctp_quote_qthread::ctp_quote_qthread()
{
}
void ctp_quote_qthread::run()
{
    quote->init(this);
}
void ctp_quote_qthread::init()
{
    quote=new ctp_quote;
    QObject::connect(quote,&ctp_quote::broadcast_quote ,order_manager,&ctp_order_manager::rec_quote);
}
