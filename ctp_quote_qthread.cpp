#include "ctp_quote_qthread.h"
#include "ctp_quote.h"
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
}
