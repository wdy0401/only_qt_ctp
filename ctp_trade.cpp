#include "ctp_trade.h"
#include<Windows.h>

#include"../gpp_qt/wfunction/wfunction.h"

using namespace std;
ctp_trade::ctp_trade()
{

}
void ctp_trade::init(const string & confile_dir)
{
    this->CreateFtdcTraderApi(confile_dir.c_str());
}
