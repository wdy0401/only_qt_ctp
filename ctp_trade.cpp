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
    maxdelaytime=atoi(simu_cfg.getparam("MAX_QUERY_DELAY").c_str());
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
void ctp_trade::ReqQryOrder(const string &  instrument_id)
{
    ReqQryOrder(instrument_id,false);
}
void ctp_trade::ReqQryOrder(const string & instrument_id,bool fast)
{
    CThostFtdcQryOrderField ofreq;
    memset(&ofreq, 0, sizeof(ofreq));
    strncpy(ofreq.BrokerID,const_cast<char*>(simu_cfg.getparam("BROKER_ID").c_str()),sizeof(ofreq.BrokerID));
    strncpy(ofreq.InvestorID,const_cast<char*>(simu_cfg.getparam("INVESTOR_ID").c_str()),sizeof(ofreq.InvestorID));
    strncpy(ofreq.InstrumentID,const_cast<char*>(instrument_id.c_str()),sizeof(ofreq.InstrumentID));
    int delaytime=0;
    while (true)
    {
        if(delaytime>maxdelaytime)
        {
            cerr<<"--->>> 请求查询报单时间超过最大限时\t"<<"请求合约:\t"<<instrument_id<<"\t最大限时(second):\t"<<maxdelaytime<<endl;
            break;
        }
        int iResult = pUserApi->ReqQryOrder(&ofreq, ++iRequestID);
        if (!IsFlowControl(iResult))
        {
            cerr << "--->>> 请求查询报单: "  << iResult << ((iResult == 0) ? ", 成功" : ", 失败") << endl;
            break;
        }
        else
        {
            if(fast)
            {
                cerr << "--->>> 请求查询报单: "  << iResult << ", 受到流控\t fast 模式,结束查询" << endl;
                break;
            }
            else
            {
                cerr << "--->>> 请求查询报单: "  << iResult << ", 受到流控\t 普通模式，等待一秒后继续查询" << endl;
                Sleep(1000);
                delaytime++;
            }
        }
    }
}
void ctp_trade::ReqQryInstrument(const string & instrument_id)
{
    ReqQryInstrument(instrument_id,false);//defaule mode is "wait untill get result"
}
void ctp_trade::ReqQryInstrument(const string & instrument_id,bool fast)
{
    CThostFtdcQryInstrumentField qireq;
    memset(&qireq, 0, sizeof(qireq));
    strcpy(qireq.InstrumentID,const_cast<char*>(instrument_id.c_str()));
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
        int iResult = pUserApi->ReqQryInstrument(&qireq, ++iRequestID);
        if (!IsFlowControl(iResult))
        {
            cerr << "--->>> 请求查询合约: "  << iResult << ((iResult == 0) ? ", 成功" : ", 失败") << endl;
            break;
        }
        else
        {
            if(fast)
            {
                cerr << "--->>> 请求查询合约: "  << iResult << ", 受到流控\t fast 模式,结束查询" << endl;
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
    ReqQryTradingAccount(false);
}
void ctp_trade::ReqQryTradingAccount(bool fast)
{
    CThostFtdcQryTradingAccountField tareq;
    memset(&tareq, 0, sizeof(tareq));
    strncpy(tareq.BrokerID,const_cast<char*>(simu_cfg.getparam("BROKER_ID").c_str()),sizeof(tareq.BrokerID));
    strncpy(tareq.InvestorID,const_cast<char*>(simu_cfg.getparam("INVESTOR_ID").c_str()),sizeof(tareq.InvestorID));
    int delaytime=0;
    while (true)
    {
        int iResult = pUserApi->ReqQryTradingAccount(&tareq, ++iRequestID);
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
            if(fast)
            {
                cerr << "--->>> 请求查询资金账户: "  << iResult << ", 受到流控\t fast 模式,结束查询" << endl;
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
}
void ctp_trade::ReqQryInvestorPosition(const string & instrument_id)
{
    ctp_trade::ReqQryInvestorPosition(instrument_id,false);
}
void ctp_trade::ReqQryInvestorPosition(const string & instrument_id,bool fast)
{
    CThostFtdcQryInvestorPositionField ipreq;
    memset(&ipreq, 0, sizeof(ipreq));

    strncpy(ipreq.InstrumentID,const_cast<char*>(instrument_id.c_str()),sizeof(ipreq.InstrumentID));
    strncpy(ipreq.BrokerID,const_cast<char*>(simu_cfg.getparam("BROKER_ID").c_str()),sizeof(ipreq.BrokerID));
    strncpy(ipreq.InvestorID,const_cast<char*>(simu_cfg.getparam("INVESTOR_ID").c_str()),sizeof(ipreq.InvestorID));
    int delaytime=0;
    while (true)
    {
        int iResult = pUserApi->ReqQryInvestorPosition(&ipreq, ++iRequestID);
        if(delaytime>maxdelaytime)
        {
            cerr<<"--->>> 请求查询持仓时间超过最大限时\t"<<"合约:\t"<<ipreq.InvestorID<<"\t最大限时:\t"<<maxdelaytime<<endl;
            break;
        }
        if (!IsFlowControl(iResult))
        {
            cerr << "--->>> 请求合约持仓: "  << iResult << ((iResult == 0) ? ", 成功" : ", 失败") << endl;
            break;
        }
        else
        {
            if(fast)
            {
                cerr << "--->>> 请求合约持仓: "  << iResult << ", 受到流控\t fast 模式,结束查询" << endl;
                break;
            }
            else
            {
                cerr << "--->>> 请求查询合约持仓: "  << iResult << ", 受到流控\t 普通模式，等待一秒后继续查询" << endl;
                Sleep(1000);
                delaytime++;
            }
        }
    }
}
//未完成
void ctp_trade::ReqOrderInsert(const string & InstrumentID)
{
    /*
    CThostFtdcInputOrderField oireq;
    memset(&oireq, 0, sizeof(oireq));
    strncpy(oireq.InstrumentID,const_cast<char*>(instrument_id.c_str()),sizeof(oireq.InstrumentID));
    strncpy(oireq.BrokerID,const_cast<char*>(simu_cfg.getparam("BROKER_ID").c_str()),sizeof(oireq.BrokerID));
    strncpy(oireq.InvestorID,const_cast<char*>(simu_cfg.getparam("INVESTOR_ID").c_str()),sizeof(oireq.InvestorID));
    ///报单引用
    strcpy(req.OrderRef, ORDER_REF);
    ///用户代码
//	TThostFtdcUserIDType	UserID;
    ///报单价格条件: 限价
    req.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
    ///买卖方向:
    req.Direction = DIRECTION;
    ///组合开平标志: 开仓
    req.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
    ///组合投机套保标志
    req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
    ///价格
    req.LimitPrice = LIMIT_PRICE;
    ///数量: 1
    req.VolumeTotalOriginal = 1;
    ///有效期类型: 当日有效
    req.TimeCondition = THOST_FTDC_TC_GFD;
    ///GTD日期
//	TThostFtdcDateType	GTDDate;
    ///成交量类型: 任何数量
    req.VolumeCondition = THOST_FTDC_VC_AV;
    ///最小成交量: 1
    req.MinVolume = 1;
    ///触发条件: 立即
    req.ContingentCondition = THOST_FTDC_CC_Immediately;
    ///止损价
//	TThostFtdcPriceType	StopPrice;
    ///强平原因: 非强平
    req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
    ///自动挂起标志: 否
    req.IsAutoSuspend = 0;
    ///业务单元
//	TThostFtdcBusinessUnitType	BusinessUnit;
    ///请求编号
//	TThostFtdcRequestIDType	RequestID;
    ///用户强评标志: 否
    req.UserForceClose = 0;
    judge=2;
    int iResult = pUserApi->ReqOrderInsert(&req, ++iRequestID);
    cerr << "--->>> 报单录入请求: " << iResult << ((iResult == 0) ? ", 成功" : ", 失败") << endl;
    */
}
//未完成
void ctp_trade::ReqOrderAction(CThostFtdcOrderField *pOrder)
{
    /*
    if (pOrder->OrderStatus != THOST_FTDC_OST_Canceled)
        {
            CThostFtdcInputOrderActionField req;
            memset(&req, 0, sizeof(req));
            ///经纪公司代码
            cout<<pOrder->BrokerID<<pOrder->InvestorID<<pOrder->ExchangeID<<pOrder->BrokerID<<pOrder->OrderSysID<<endl;
            strcpy(req.BrokerID, pOrder->BrokerID);
            ///投资者代码
            strcpy(req.InvestorID, pOrder->InvestorID);
            ///报单操作引用
            TThostFtdcOrderActionRefType	OrderActionRef;
            ///报单引用
            strcpy(req.OrderRef, pOrder->OrderRef);
            ///请求编号

            TThostFtdcRequestIDType	RequestID;
            ///前置编号

            printf("%d",SESSION_ID);
            req.FrontID = FRONT_ID;
            ///会话编号
            req.SessionID = SESSION_ID;
            ///交易所代码
            strcpy(req.ExchangeID,pOrder->ExchangeID);
            ///报单编号
             strcpy(req.OrderSysID, pOrder->OrderSysID);
            ///操作标志
            req.ActionFlag = THOST_FTDC_AF_Delete;
            ///价格
            //req.LimitPrice=LIMIT_PRICE;
            ///数量变化
            //TThostFtdcVolumeType	VolumeChange;
            ///用户代码
            //TThostFtdcUserIDType	UserID;
            ///合约代码
            //strcpy(req.InstrumentID, pOrder->InstrumentID);
            judge=3;

            int iResult = pUserApi->ReqOrderAction(&req, ++iRequestID);cerr << "--->>> 报单操作请求: "  << iResult << ((iResult == 0) ? ", 成功" : ", 失败") << endl;
        }
        else
        {
            cout<<"单子已经撤销过了"<<endl;
            cmd();
        }
    */
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
//Functions called from exchange.
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
        //this->MaxOrderRef=pRspUserLogin->MaxOrderRef;
//        this->OrderRef=pRspUserLogin->;
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
//未完成
void ctp_trade::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    cerr << "--->>> " << "OnRspQryInstrument" << endl;
    if (bIsLast && !IsErrorRspInfo(pRspInfo))
    {
        //在此设置合约参数
    }
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

//////////////////////////////////////////////////////////////////////////////////////////////
//
//Bool Functions
//
//////////////////////////////////////////////////////////////////////////////////////////////
bool ctp_trade::IsFlowControl(int iResult)
{
    return ((iResult == -2) || (iResult == -3));
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
