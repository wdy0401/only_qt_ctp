#include "ctp_trade.h"
#include<Windows.h>
#include<string>

#include"../gpp_qt/wfunction/wfunction.h"
#include"../gpp_qt/cfg/cfg.h"

extern cfg simu_cfg;
using namespace std;

ctp_trade::ctp_trade()
{
    cout<<"init trade"<<endl;
}
void ctp_trade::init()
{
    pUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi(this->mk_trade_con_dir());
    pUserApi->RegisterSpi((CThostFtdcTraderSpi*)this);			// 注册事件类
    pUserApi->SubscribePublicTopic(THOST_TERT_QUICK);				// 注册公有流
    pUserApi->SubscribePrivateTopic(THOST_TERT_QUICK);				// 注册私有流
    pUserApi->RegisterFront(const_cast<char*>(simucfg->getparam("FRONT_ADDR").c_str()));// connect
    pUserApi->Init();
    pUserApi->Join();
}
void ctp_trade::OnFrontConnected()
{
    cerr << "--->>> " << "OnFrontConnected" << endl;
    ///用户登录请求
    ReqUserLogin();
}
void ctp_trade::ReqUserLogin()
{
    CThostFtdcReqUserLoginField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.BrokerID, BROKER_ID);
    strcpy(req.UserID, INVESTOR_ID);
    strcpy(req.Password, PASSWORD);
    int iResult = pUserApi->ReqUserLogin(&req, ++iRequestID);
    cerr << "--->>> 发送用户登录请求: " << iResult << ((iResult == 0) ? ", 成功" : ", 失败") << endl;
}
void ctp_trade::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    cerr << "--->>> " << "OnRspUserLogin" << endl;
    if (bIsLast && !IsErrorRspInfo(pRspInfo))
    {
        // 保存会话参数
        FRONT_ID = pRspUserLogin->FrontID;
        SESSION_ID = pRspUserLogin->SessionID;
        cout<<pRspUserLogin->MaxOrderRef<<endl;


        ///获取当前交易日
        cerr << "--->>> 获取当前交易日 = " << pUserApi->GetTradingDay() << endl;
        ///投资者结算结果确认
        ReqSettlementInfoConfirm();
    }
}
void ctp_trade::ReqSettlementInfoConfirm()
{
    CThostFtdcSettlementInfoConfirmField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.BrokerID, BROKER_ID);
    strcpy(req.InvestorID, INVESTOR_ID);
    int iResult = pUserApi->ReqSettlementInfoConfirm(&req, ++iRequestID);
    cerr << "--->>> 投资者结算结果确认: " << iResult << ((iResult == 0) ? ", 成功" : ", 失败") << endl;
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
