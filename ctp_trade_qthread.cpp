#include "ctp_trade_qthread.h"
#include "ctp_trade.h"



ctp_trade_qthread::ctp_trade_qthread()
{
}
void ctp_trade_qthread::run()
{
    trade = new ctp_trade(this);
}
void ctp_trade_qthread::addorder()
{
    trade->testfunc();
    trade->sendorder("IF1412","BUY","OPEN",3200,1);
}
