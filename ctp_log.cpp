#include "ctp_log.h"

#include<iostream>
#include<iomanip>

#include"../libs/ctp/ThostFtdcMdApi.h"

using namespace std;
ctp_log::ctp_log()
{
}

void ctp_log::writeinfo(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
    ostringstream os;
    os<< pDepthMarketData->TradingDay;
    os<< "," << pDepthMarketData->UpdateTime;
    os<< ":" << pDepthMarketData->UpdateMillisec;
    os<< "," << pDepthMarketData->InstrumentID;
    os<< "," << pDepthMarketData->BidPrice1;
    os<< "," << pDepthMarketData->AskPrice1;
    os<< "," << pDepthMarketData->BidVolume1;
    os<< "," << pDepthMarketData->AskVolume1;
    os<< "," << pDepthMarketData->LastPrice;
    os<< "," << pDepthMarketData->HighestPrice;
    os<< "," << pDepthMarketData->LowestPrice;
    os<< "," << pDepthMarketData->Turnover;
    os.setf(ios::fixed);
    os<<setprecision(10);
    os<< "," << pDepthMarketData->AveragePrice;
    os.setf(ios::fixed);
    os<<setprecision(2);
    os<< "," << pDepthMarketData->PreSettlementPrice;
    os<< "," << pDepthMarketData->SettlementPrice;
    os<< endl;
    string out=os.str();
    this->outlog<<out;
}
