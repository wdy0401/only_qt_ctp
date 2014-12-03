#include "ctp_trade_qthread.h"
#include "ctp_trade.h"
ctp_trade_qthread::ctp_trade_qthread()
{
}
void ctp_trade_qthread::run()
{
	ctp_trade * trade = new ctp_trade(this);
}
