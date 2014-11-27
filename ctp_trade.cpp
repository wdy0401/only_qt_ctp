#include "ctp_trade.h"
#include<Windows.h>
#include<string>

#include<QApplication>

#include"../gpp_qt/wfunction/wfunction.h"
#include"../gpp_qt/cfg/cfg.h"

extern cfg simu_cfg;
using namespace std;

ctp_trade::ctp_trade()
{
    cout<<"init trade"<<endl;
    iRequestID=0;
    req=new CThostFtdcReqUserLoginField;
}
void ctp_trade::init()
{
    pUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi(this->mk_trade_con_dir());
    pUserApi->RegisterSpi((CThostFtdcTraderSpi*)this);
    pUserApi->SubscribePublicTopic(THOST_TERT_QUICK);
    pUserApi->SubscribePrivateTopic(THOST_TERT_QUICK);
    pUserApi->RegisterFront(const_cast<char*>(simu_cfg.getparam("TRADE_FRONT_ADDR").c_str()));// connect
    pUserApi->Init();
    pUserApi->Join();
}
void ctp_trade::ReqUserLogin()
{
    memset(req, 0, sizeof(*req));
    strncpy(req->BrokerID,const_cast<char*>(simu_cfg.getparam("BROKER_ID").c_str()),sizeof(req->BrokerID));
    strncpy(req->UserID,const_cast<char*>(simu_cfg.getparam("INVESTOR_ID").c_str()),sizeof(req->UserID));
    strncpy(req->Password,const_cast<char*>(simu_cfg.getparam("PASSWORD").c_str()),sizeof(req->Password));
    int iResult = pUserApi->ReqUserLogin(req, ++iRequestID);
    cerr << "--->>> Sending login request: " << iResult << ((iResult == 0) ? ",Successed" : ",Fail") << endl;
}

void ctp_trade::ReqSettlementInfoConfirm()
{
    CThostFtdcSettlementInfoConfirmField screq;
    memset(&screq, 0, sizeof(screq));
    strncpy(screq.BrokerID,const_cast<char*>(simu_cfg.getparam("BROKER_ID").c_str()),sizeof(screq.BrokerID));
    strncpy(screq.InvestorID,const_cast<char*>(simu_cfg.getparam("INVESTOR_ID").c_str()),sizeof(screq.InvestorID));
    int iResult = pUserApi->ReqSettlementInfoConfirm(&screq, ++iRequestID);
    cerr << "--->>> Confirm settlement: " << iResult << ((iResult == 0) ? ",Successed" : ",Fail") << endl;
}

void ctp_trade::ReqQryOrder()
{

}
void ctp_trade::QryOrder()
{

}
bool ctp_trade::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
    return true;
}
bool ctp_trade::IsMyOrder(CThostFtdcOrderField *pOrder)
{
    return true;
}
bool ctp_trade::IsTradingOrder(CThostFtdcOrderField *pOrder)
{
    return true;
}
void ctp_trade::ReqQryInstrument(char * instrument_id)
{
    ReqQryInstrument(false,instrument_id);//defaule mode is "wait untill get result"

}
void ctp_trade::ReqQryInstrument(bool fast,const string & instrument_id)
{
    CThostFtdcQryInstrumentField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.InstrumentID, ,const_cast<char*>(instrument_id.c_str()));
    int maxdelaytime=atoi(simu_cfg.getparam("MAX_QUERY_DELAY"));
    int delaytime=0;
    while (true)
    {
        //对任何Qry请求，程序有死锁在这的可能
        //目前解决方式是在cfg最大查询时间里设置 并在大于最长时间时输出警告并返回
        if(delaytime>maxdelaytime)
        {
            cerr<<"--->>> 请求查询合约时间超过最大限时\t"<<"请求合约:\t"<<instrument_id<<"\t最大限时:\t"<<maxdelaytime<<endl;
            break;
        }
        int iResult = pUserApi->ReqQryInstrument(&req, ++iRequestID);
        if (!IsFlowControl(iResult))
        {
            cerr << "--->>> 请求查询合约: "  << iResult << ((iResult == 0) ? ", 成功" : ", 失败") << endl;
            break;
        }
        else
        {
            if(fast)
            {
                cerr << "--->>> 请求查询合约: "  << iResult << ", 受到流控\t fast 模式，结束查询" << endl;
                break;
            }
            else
            {
                cerr << "--->>> 请求查询合约: "  << iResult << ", 受到流控\t 普通模式，等待一秒后继续查询" << endl;
                Sleep(1000);
                delaytime++;
            }
        }
    }
}
void ctp_trade::ReqQryTradingAccount()
{
    CThostFtdcQryTradingAccountField tareq;
    memset(&tareq, 0, sizeof(tareq));
    strncpy(tareq.BrokerID,const_cast<char*>(simu_cfg.getparam("BROKER_ID").c_str()),sizeof(tareq.BrokerID));
    strncpy(tareq.InvestorID,const_cast<char*>(simu_cfg.getparam("INVESTOR_ID").c_str()),sizeof(tareq.InvestorID));
    int maxdelaytime=atoi(simu_cfg.getparam("MAX_QUERY_DELAY"));
    int delaytime=0;
    while (true)//资金账户查询对响应时间较不敏感  故只设置死锁返回，未设置快速退出
    {
        int iResult = pUserApi->tareqQryTradingAccount(&tareq, ++iRequestID);
        if(delaytime>maxdelaytime)
        {
            cerr<<"--->>> 请求查询资金账户时间超过最大限时\t"<<"经纪商:\t"<<tareq.BrokerID<<"\t请求资金账户:\t"<<tareq.InvestorID<<"\t最大限时:\t"<<maxdelaytime<<endl;
            break;
        }
        if (!IsFlowControl(iResult))
        {
            cerr << "--->>> 请求查询资金账户: "  << iResult << ((iResult == 0) ? ", 成功" : ", 失败") << endl;
            break;
        }
        else
        {
            cerr << "--->>> 请求查询资金账户: "  << iResult << ", 受到流控\t 普通模式，等待一秒后继续查询" << endl;
            Sleep(1000);
            delaytime++;
        }
    }
}
void ctp_trade::ReqQryInvestorPosition()
{

}
void ctp_trade::ReqOrderInsert()
{

}
void ctp_trade::ReqOrderAction(CThostFtdcOrderField *pOrder)
{

}
char *ctp_trade::mk_trade_con_dir()
{
        string exedir=simu_cfg.getparam("TRADE_CON_PATH");
        if(exedir.size()>0)
        {
            wfunction::wmkdir(exedir);
            return const_cast<char*>((exedir+"/").c_str());
        }
        else
        {
            exedir=QCoreApplication::applicationFilePath().toStdString();
            cout<<exedir<<endl;
            exedir=exedir.erase(exedir.find_last_of("/"),exedir.size());
//            exedir=exedir.erase(exedir.find_last_of("\\"),exedir.size());
            exedir=exedir+"/trade_con";
            wfunction::wmkdir(exedir);
        }
        return const_cast<char*>((exedir+"/").c_str());
}
//////////////////////////////////////////////////////////////////////////////////////////////
//
//Functions below are called from exchange.
//
//////////////////////////////////////////////////////////////////////////////////////////////
void ctp_trade::OnFrontConnected()
{
    cerr << "--->>> " << "OnFrontConnected" << endl;
    ReqUserLogin();
}
void ctp_trade::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    cerr << "--->>> " << "OnRspUserLogin" << endl;
    if (bIsLast && !IsErrorRspInfo(pRspInfo))
    {
        //save para
        this->FRONT_ID = pRspUserLogin->FrontID;
        this->SESSION_ID = pRspUserLogin->SessionID;
        cout<<pRspUserLogin->MaxOrderRef<<endl;
        //get exchange trading day
        cerr << "--->>> get exchange trading day = " << pUserApi->GetTradingDay() << endl;
        ///confirm settlement result
        ReqSettlementInfoConfirm();
    }
}
void ctp_trade::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    cout<<"BrokerID:\t"<<pSettlementInfoConfirm->BrokerID<<"\t"<<"nRequestID:\t"<<nRequestID<<endl;
    cerr << "--->>> " << "OnRspSettlementInfoConfirm" << endl;
    if (bIsLast)
    {
        IsErrorRspInfo(pRspInfo);
    }
}
void ctp_trade::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}
void ctp_trade::OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}
void ctp_trade::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}
void ctp_trade::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}
void ctp_trade::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}
void ctp_trade::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}
void ctp_trade::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}
void ctp_trade::OnFrontDisconnected(int nReason)
{

}
void ctp_trade::OnHeartBeatWarning(int nTimeLapse)
{

}
void ctp_trade::OnRtnOrder(CThostFtdcOrderField *pOrder)
{

}
void ctp_trade::OnRtnTrade(CThostFtdcTradeField *pTrade)
{

}
