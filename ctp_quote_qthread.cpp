#include "ctp_quote_qthread.h"
#include "ctp_quote.h"
ctp_quote_qthread::ctp_quote_qthread()
{
}
void ctp_quote_qthread::run()
{
    ctp_quote * quote=new ctp_quote(this);
}
/*void ctp_quote_qthread::broadcast_markerdata(CThostFtdcDepthMarketDataField *pDepthMarketData)
{

}
*/
