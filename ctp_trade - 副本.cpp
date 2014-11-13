#include"ctp_trade.h"
#include"gpp_qt/wfunction/wfunction.h"
#include"gpp_qt/cfg/cfg.h"

extern cfg simu_cfg;

static bool offer=false;
static bool cancel = false;
static bool dele=false;
static int tempinner=0;
static int i=0;
static bool ex=false;
static int sysid[20];
static int reqid[20];
char orderref[20][13];
char idref[20][13];

// USER_API参数
extern CThostFtdcTraderApi* pUserApi;


static int judge=0;

// 配置参数
extern char BROKER_ID[];		// 经纪公司代码
extern char INVESTOR_ID[];		// 投资者代码
extern char PASSWORD[];			// 用户密码
extern char INSTRUMENT_ID[];	// 合约代码
extern TThostFtdcPriceType	LIMIT_PRICE;	// 价格
extern TThostFtdcDirectionType	DIRECTION;	// 买卖方向

CThostFtdcOrderField  *p[20];
CThostFtdcOrderField  *t;

struct CThostFtdcOrderField  q;
char message[20][13];

// 请求编号
extern int iRequestID;

// 会话参数
TThostFtdcFrontIDType	FRONT_ID;	//前置编号
TThostFtdcSessionIDType	SESSION_ID;	//会话编号
TThostFtdcOrderRefType	ORDER_REF;	//报单引用

// 流控判断
bool IsFlowControl(int iResult)
{
    return ((iResult == -2) || (iResult == -3));
}
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//登录部分
void CTraderSpi::OnFrontConnected()
{
    cerr << "--->>> " << "OnFrontConnected" << endl;
    ///用户登录请求
    ReqUserLogin();
}
void CTraderSpi::ReqUserLogin()
{
    CThostFtdcReqUserLoginField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.BrokerID, BROKER_ID);
    strcpy(req.UserID, INVESTOR_ID);
    strcpy(req.Password, PASSWORD);
    int iResult = pUserApi->ReqUserLogin(&req, ++iRequestID);
    cerr << "--->>> 发送用户登录请求: " << iResult << ((iResult == 0) ? ", 成功" : ", 失败") << endl;
}
void CTraderSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
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
void CTraderSpi::ReqSettlementInfoConfirm()
{
    CThostFtdcSettlementInfoConfirmField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.BrokerID, BROKER_ID);
    strcpy(req.InvestorID, INVESTOR_ID);
    int iResult = pUserApi->ReqSettlementInfoConfirm(&req, ++iRequestID);
    cerr << "--->>> 投资者结算结果确认: " << iResult << ((iResult == 0) ? ", 成功" : ", 失败") << endl;
}
void CTraderSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    cout<<pSettlementInfoConfirm->BrokerID<<endl;
    cerr << "--->>> " << "OnRspSettlementInfoConfirm" << endl;

    if (bIsLast && !IsErrorRspInfo(pRspInfo))
    {
        cmd();
    }
}
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//唯一order的下单处理
void CTraderSpi::cmd()
{
    cout<<"请输入命令代码：\n1查询持仓\n2报单\n3撤单\n4查询委托"<<endl;

    int temp=0;
    static int j=0;

    scanf("%d",&temp);

    if(temp==1)
    {
        ReqQryInvestorPosition();
    }
    else if(temp==2)
    {
        ReqOrderInsert();
    }
    else if (temp==3)
    {
        strcpy(p[1]->OrderSysID,idref[2]);
        strcpy(p[1]->OrderRef,orderref[2]);
        cout<<p[2]->OrderSysID<<endl;
        cout<<p[1]->OrderRef<<endl;
        ReqOrderAction(p[1]);
    }
    else if(temp==4)
    {
        ReqQryOrder();
    }
    else if(temp==5)
    {
        int temp1;
        for(temp1=1;temp<i+1;temp1++)
        cout<<p[temp1]->OrderRef<<p[temp1]->OrderLocalID<<p[temp1]->OrderSysID<<endl;
    }
    else
    {
        cout<<"不知道你命令是什么"<<endl;
        cmd();
    }
}
///*****************************在某一个价位对某个合约进行  卖  报单的操作******************************************************
void CTraderSpi::ReqOrderInsert()
{
    CThostFtdcInputOrderField req;
    memset(&req, 0, sizeof(req));
    ///经纪公司代码
    strcpy(req.BrokerID, BROKER_ID);
    ///投资者代码
    strcpy(req.InvestorID, INVESTOR_ID);
    ///合约代码
    strcpy(req.InstrumentID, INSTRUMENT_ID);
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
}
void CTraderSpi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    cerr << "--->>> " << "OnRspOrderInsert" << endl;
    IsErrorRspInfo(pRspInfo);
    cmd();
}
///*****************************撤单操作******************************************************
//需要程序主动调用
void CTraderSpi::ReqOrderAction(CThostFtdcOrderField *pOrder)
{	if (pOrder->OrderStatus != THOST_FTDC_OST_Canceled)
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
}
//报单响应
void CTraderSpi::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    cerr << "--->>> " << "OnRspOrderAction" << endl;
    IsErrorRspInfo(pRspInfo);
    cmd();
}
//报单通知
///*****************************创建报单或者撤单操作后系统的反馈******************************************************
void CTraderSpi::OnRtnOrder(CThostFtdcOrderField *pOrder)
    {
    int temp=0;
    cerr << "--->>> " << "OnRtnOrder"  << endl;
    //挂单后自动回到cmd()
    if(judge==2)
    {
        cerr << "--->>> " << "OnRtnOrder"  << endl;
        if(offer)
        {
            offer=false;
            cout<<ORDER_REF<<endl;
            temp=atoi(pOrder->OrderRef);
            printf("%d",temp);
            i++;
            strcpy(orderref[i],pOrder->OrderRef);
            strcpy(idref[i],pOrder->OrderSysID);
            reqid[temp]=pOrder->RequestID;
            cout<<pOrder->BrokerID<<pOrder->InvestorID<<pOrder->ExchangeID<<pOrder->BrokerID<<pOrder->OrderSysID<<idref<<orderref<<endl;
            p[temp]=pOrder;
            cmd();
        }
        else
        {
            offer=true;
        }
    }

    if(judge==3)
    {
        cout<<"撤单成功"<<endl;
        if(cancel)
        {
            cout<<"撤单成功22"<<endl;
            cancel=false;
            cmd();
        }
        else
        {
            cancel=true;
        }
    }
}
///*****************************查询已有的挂单 从返回结果上看 称其为网络状态查询更为恰当******************************************************
void CTraderSpi::ReqQryOrder()
{
    CThostFtdcQryOrderField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.BrokerID, BROKER_ID);
    strcpy(req.InvestorID, INVESTOR_ID);
    strcpy(req.InstrumentID,INSTRUMENT_ID);
    tempinner=0;
    int iResult = pUserApi->ReqQryOrder(&req, ++iRequestID);
    if (!IsFlowControl(iResult))
    {
        cerr << "--->>> 报单查询请求: " << iResult << ((iResult == 0) ? (", 成功") : ", 失败") << endl;
    }
    else
    {
        cerr << "--->>> 请求查询投资者持仓: "  << iResult << ", 受到流控" << endl;
        Sleep(1000);
    }
};
//这里返回查询报单的结果
void  CTraderSpi::OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if(pOrder->OrderStatus!= THOST_FTDC_OST_Canceled)
    {
        cout<<pOrder->OrderStatus<<pOrder->OrderRef<<pOrder->OrderSysID<<endl;
    }
    if (bIsLast && !IsErrorRspInfo(pRspInfo))
    {
        cmd();
    }
}
///成交通知
void CTraderSpi::OnRtnTrade(CThostFtdcTradeField *pTrade)
{
    cerr << "--->>> " << "OnRtnTrade"  << endl;
}

void CTraderSpi:: OnFrontDisconnected(int nReason)
{
    cerr << "--->>> " << "OnFrontDisconnected" << endl;
    cerr << "--->>> Reason = " << nReason << endl;
}

void CTraderSpi::OnHeartBeatWarning(int nTimeLapse)
{
    cerr << "--->>> " << "OnHeartBeatWarning" << endl;
    cerr << "--->>> nTimerLapse = " << nTimeLapse << endl;
}

void CTraderSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    cerr << "--->>> " << "OnRspError" << endl;
    IsErrorRspInfo(pRspInfo);
}

bool CTraderSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
    // 如果ErrorID != 0, 说明收到了错误的响应
    bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
    if (bResult)
    {
        cerr << "--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << endl;
    }
    return bResult;
}

bool CTraderSpi::IsMyOrder(CThostFtdcOrderField *pOrder)
{
    return
        (
            (pOrder->FrontID == FRONT_ID) &&
            (pOrder->SessionID == SESSION_ID) &&
            (strcmp(pOrder->OrderRef, ORDER_REF) == 0)
        );
}

bool CTraderSpi::IsTradingOrder(CThostFtdcOrderField *pOrder)
{
    return
        (
            (pOrder->OrderStatus != THOST_FTDC_OST_PartTradedNotQueueing) &&
            (pOrder->OrderStatus != THOST_FTDC_OST_Canceled) &&
            (pOrder->OrderStatus != THOST_FTDC_OST_AllTraded)
        );
}
void CTraderSpi::ReqQryInstrument()
{
    CThostFtdcQryInstrumentField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.InstrumentID, INSTRUMENT_ID);
    while (true)
    {
        int iResult = pUserApi->ReqQryInstrument(&req, ++iRequestID);
        if (!IsFlowControl(iResult))
        {
            cerr << "--->>> 请求查询合约: "  << iResult << ((iResult == 0) ? ", 成功" : ", 失败") << endl;
            break;
        }
        else
        {
            cerr << "--->>> 请求查询合约: "  << iResult << ", 受到流控" << endl;
            Sleep(1000);
        }
    } // while
}

void CTraderSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    cerr << "--->>> " << "OnRspQryInstrument" << endl;

    if (bIsLast && !IsErrorRspInfo(pRspInfo))
    {
        cmd();
    }
}

void CTraderSpi::ReqQryTradingAccount()
{
    CThostFtdcQryTradingAccountField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.BrokerID, BROKER_ID);
    strcpy(req.InvestorID, INVESTOR_ID);
    while (true)
    {
        int iResult = pUserApi->ReqQryTradingAccount(&req, ++iRequestID);
        if (!IsFlowControl(iResult))
        {
            cerr << "--->>> 请求查询资金账户: "  << iResult << ((iResult == 0) ? ", 成功" : ", 失败") << endl;
            break;
        }
        else
        {
            cerr << "--->>> 请求查询资金账户: "  << iResult << ", 受到流控" << endl;
            Sleep(1000);
        }
    } // while
}

void CTraderSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    cerr << "--->>> " << "OnRspQryTradingAccount" << endl;
    if (bIsLast && !IsErrorRspInfo(pRspInfo))
    {
        cmd();
    }
}
//发送查询投资者持仓
void CTraderSpi::ReqQryInvestorPosition()
{
    CThostFtdcQryInvestorPositionField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.BrokerID, BROKER_ID);
    strcpy(req.InvestorID, INVESTOR_ID);
    strcpy(req.InstrumentID, INSTRUMENT_ID);
    while (true)
    {
        int iResult = pUserApi->ReqQryInvestorPosition(&req, ++iRequestID);
        printf("%d",iResult);
        if (!IsFlowControl(iResult))
        {
            cerr << "--->>> 请求查询投资者持仓: "  << iResult << ((iResult == 0) ? ", 成功" : ", 失败") << endl;
            break;
        }
        else
        {
            cerr << "--->>> 请求查询投资者持仓: "  << iResult << ", 受到流控" << endl;
            Sleep(1000);
            cmd();
        }
    } // while
}
//投资者持仓回报
void CTraderSpi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    cerr << "--->>> " << "OnRspQryInvestorPosition" << endl;
//	qryorder=false;
    cout<<pInvestorPosition->Position<<endl;
    if (bIsLast && !IsErrorRspInfo(pRspInfo))
    {
        cmd();
    }
}

