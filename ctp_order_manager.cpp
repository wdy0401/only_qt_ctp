#include "ctp_order_manager.h"
#include"mainwindow.h"
#include<QMessageBox>

#include<iostream>

#include"../gpp_qt/wfunction/wfunction.h"
#include"../gpp_qt/cfg/cfg.h"

#include"../../libs/ctp/ThostFtdcTraderApi.h"
#include"tactic.h"
extern MainWindow * mw;
extern ctp_order_manager * order_manager;
extern cfg simu_cfg;

using namespace std;

void ctp_order_manager::init()
{
    _ordercount=0;
//    order_manager=this;
}
void ctp_order_manager::set_tactic(tactic * p)
{
    tc=p;
    QObject::connect(this,&ctp_order_manager::ack,tc,&tactic::ack);
    QObject::connect(this,&ctp_order_manager::done,tc,&tactic::done);
    QObject::connect(this,&ctp_order_manager::rej,tc,&tactic::rej);
    QObject::connect(this,&ctp_order_manager::fill,tc,&tactic::fill);
    QObject::connect(this,&ctp_order_manager::send_quote,tc,&tactic::quote);
}

void ctp_order_manager::set_trade(ctp_trade * p)
{
    trade=p;
}
void ctp_order_manager::rec_quote(const string &symbol, const string &ba, long level, double price, long size)
{
    emit send_quote(symbol,ba,level,price,size);
}
void ctp_order_manager::show_warning(const string & warninfo)
{
    cerr << "Warning from ctp_order_manager" << endl;
    cerr << warninfo <<endl;
}
std::string ctp_order_manager::new_order(const std::string InstrumentID,const std::string side, const std::string & openclose ,double price,long size)
{
    string ordername="";
    cerr << endl << "--->>>ctp_trade sendorder init" << endl;
    CThostFtdcInputOrderField * porder=initorder(InstrumentID, side, openclose, price, size);
    cerr << "BrokerID "<< porder->BrokerID<<endl;
    trade->ReqOrderInsert(porder);
    return ordername;
}
void ctp_order_manager::OnLogin(CThostFtdcRspUserLoginField *pRspUserLogin)
{
    FRONT_ID = pRspUserLogin->FrontID;
    SESSION_ID = pRspUserLogin->SessionID;
}
void ctp_order_manager::OnRtnOrder(CThostFtdcOrderField *p)
{
    cerr << endl << "--->>> OnRtnOrder" <<endl;
    string mapid=wfunction::itos(p->FrontID)+"_"+wfunction::itos(p->SessionID)+"_"+p->OrderRef;
/*
    switch (p->OrderStatus)
    {
    ///全部成交
    case THOST_FTDC_OST_AllTraded: orderid_op.erase(mapid); break;
    ///部分成交还在队列中
    case THOST_FTDC_OST_PartTradedQueueing:break;
    ///部分成交不在队列中
    case THOST_FTDC_OST_PartTradedNotQueueing: orderid_op.erase(mapid); break;
    ///未成交还在队列中
    case THOST_FTDC_OST_NoTradeQueueing: break;
    ///未成交不在队列中
    case THOST_FTDC_OST_NoTradeNotQueueing: orderid_op.erase(mapid); break;
    ///撤单
    case THOST_FTDC_OST_Canceled: orderid_op.erase(mapid); break;
    ///未知， 表示 Thost已经接受用户 的委托指令，还没有 转发到交易所
    case THOST_FTDC_OST_Unknown: orderid_op[mapid] = p; break;
    ///尚未触发
    case THOST_FTDC_OST_NotTouched: break;

    }
  */
    cerr << "map id\t" << mapid << endl;
    cerr << "FrontID\t" << p->FrontID << endl;
    cerr << "SessionID\t" << p->SessionID << endl;
    cerr << "OrderRef\t" << p->OrderRef << endl;
//    cerr << "OrderStatus\t" << p->OrderStatus << endl;
    cerr << "iRequestID\t" << p->RequestID << endl;
    show_warning("Warning from OnRtnOrder");

//    cerr << "OrderRef" << p->OrderRef << endl;


    //
    //继续添加功能
    //
}
void ctp_order_manager::OnRtnTrade(CThostFtdcTradeField *pTrade)
{

}
CThostFtdcInputOrderField * ctp_order_manager::initorder(const string & InstrumentID, const string & side, const string & openclose, double price, long size)
{
    cerr << endl << "--->>> Init order" << endl;
    cerr << "Local Init order\t" << InstrumentID << "\t" << side << "\t" << openclose << "\t" << price << "\t" << size << endl;
    cerr << "Local Init order\t" << InstrumentID << "\t" << side << "\t" << openclose << "\t" << price << "\t" << size << endl;
    //cerr << InstrumentID;// << "\t" << side << "\t" << openclose << "\t" << price << "\t" << size << endl;
    CThostFtdcInputOrderField * oireq = new CThostFtdcInputOrderField;
    memset(oireq, 0, sizeof(CThostFtdcInputOrderField));

    ///经纪公司代码
    strncpy(oireq->BrokerID, const_cast<char*>(simu_cfg.getparam("BROKER_ID").c_str()), sizeof(oireq->BrokerID));
    ///投资者代码
    strncpy(oireq->InvestorID, const_cast<char*>(simu_cfg.getparam("INVESTOR_ID").c_str()), sizeof(oireq->InvestorID));
    ///合约代码
    strncpy(oireq->InstrumentID, const_cast<char*>(InstrumentID.c_str()), sizeof(oireq->InstrumentID));
    ///报单引用
    ///TThostFtdcOrderRefType OrderRef //ctp自动维护
    ///用户代码
    strncpy(oireq->UserID, const_cast<char*>(simu_cfg.getparam("INVESTOR_ID").c_str()), sizeof(oireq->UserID));
    ///报单价格条件
    oireq->OrderPriceType = THOST_FTDC_OPT_LimitPrice;
    ///买卖方向
    if (side == "BUY" || side == "SELL")
    {
        oireq->Direction = side == "BUY" ? THOST_FTDC_D_Buy : THOST_FTDC_D_Sell;
    }
    else
    {
        cerr << "--->>> order买卖方向错误: 请使用BUY SELL 指示买卖order方向" << endl;
    }
    ///组合开平标志
    if (openclose == "OPEN" || openclose == "CLOSE" || openclose == "CLOSET")
    {
        if (openclose == "OPEN")
        {
            oireq->CombOffsetFlag[0] = THOST_FTDC_OF_Open;
        }
        if (openclose == "CLOSE")
        {
            oireq->CombOffsetFlag[0] = THOST_FTDC_OF_Close;
        }
        if (openclose == "CLOSET")
        {
            oireq->CombOffsetFlag[0] = THOST_FTDC_OF_CloseToday;
        }
    }
    else
    {
        cerr << "--->>> order开平方向错误: 请使用OPEN CLOSE CLOSET 指示开平order方向" << endl;
    }
    ///组合投机套保标志
    oireq->CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;

    ///价格
    oireq->LimitPrice = price;
    ///数量
    oireq->VolumeTotalOriginal = size;
    ///有效期类型
    oireq->TimeCondition = THOST_FTDC_TC_GFD;
    ///GTD日期
    strcpy(oireq->GTDDate, "");
    ///成交量类型
    oireq->VolumeCondition = THOST_FTDC_VC_AV;
    ///最小成交量
    oireq->MinVolume = 1;
    ///触发条件: 立即
    oireq->ContingentCondition = THOST_FTDC_CC_Immediately;
    ///止损价
    oireq->StopPrice=0;
    ///强平原因: 非强平
    oireq->ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
    ///自动挂起标志: 否
    oireq->IsAutoSuspend = 0;


    //以下两处均未在文档中写明作用
    ///下面是神马
    ///业务单元
    //TThostFtdcBusinessUnitType	BusinessUnit;

    ///请求编号 发单时设置
    //TThostFtdcRequestIDType	RequestID;

    ///用户强评标志: 否
    oireq->UserForceClose = 0;

    ///下面是神马
    ///互换单标志
    //TThostFtdcBoolType	IsSwapOrder;
    cerr<<"init order is done"<<endl;

    return oireq;
}

CThostFtdcInputOrderActionField * ctp_order_manager::initorderchange(const string & ordername)
{
    map<string, CThostFtdcOrderField*>::iterator iter = orderid_op.find(ordername);
    if (iter == orderid_op.end())
    {
        return nullptr;
    }
    else
    {
        CThostFtdcOrderField *pOrder = iter->second;
        CThostFtdcInputOrderActionField * cgreq = new CThostFtdcInputOrderActionField;
        memset(cgreq, 0, sizeof(*cgreq));
        //cout << pOrder->BrokerID << pOrder->InvestorID << pOrder->ExchangeID << pOrder->BrokerID << pOrder->OrderSysID << endl;
        ///经纪公司代码
        strcpy(cgreq->BrokerID, pOrder->BrokerID);
        ///投资者代码
        strcpy(cgreq->InvestorID, pOrder->InvestorID);

        ///报单操作引用
        ///TThostFtdcOrderActionRefType	 OrderActionRef;
        ///报单引用
        strcpy(cgreq->OrderRef, pOrder->OrderRef);

        ///非初始化内容
        ///请求编号
        ///TThostFtdcRequestIDType	RequestID;

        ///前置编号
        cgreq->FrontID = FRONT_ID;
        ///会话编号
        cgreq->SessionID = SESSION_ID;
        ///交易所代码
        strcpy(cgreq->ExchangeID, pOrder->ExchangeID);
        ///报单编号
        strcpy(cgreq->OrderSysID, pOrder->OrderSysID);

        ///非初始化内容
        ///操作标志
        ///cgreq->ActionFlag = THOST_FTDC_AF_Delete;
        ///价格
        //cgreq->LimitPrice=LIMIT_PRICE;
        ///数量变化
        //TThostFtdcVolumeType	VolumeChange;

        ///用户代码
        strcpy(cgreq->UserID, pOrder->UserID);
        ///合约代码
        strcpy(cgreq->InstrumentID, pOrder->InstrumentID);

        return cgreq;
    }
}


void ctp_order_manager::change_order(const string & ordername,double price,long size)
{
    CThostFtdcInputOrderActionField * cgorder = initorderchange(ordername);
    if (cgorder == nullptr)
    {
        cerr << "--->>> 报单操作请求: 待改单不存在 请确认   ordername="<< ordername <<endl;
        return;
    }
    else
    {
        //此处存疑  这个volumechange是何意思 相对变化 绝对变化？
        cgorder->RequestID = ++iRequestID;
        cgorder->LimitPrice = price;
        cgorder->VolumeChange = size;
        cgorder->ActionFlag = THOST_FTDC_AF_Modify;
        trade->ReqOrderAction(cgorder);
    }
}
void ctp_order_manager::cancel_order(const string & ordername)
{
    cerr << endl << "--->>>delete_order init" << endl;
    cerr << "order name " << ordername <<endl;
    CThostFtdcInputOrderActionField * dlorder = initorderchange(ordername);
    if (dlorder == nullptr)
    {
        cerr << "--->>> Order not exist: Please confirm   ordername=" << ordername << endl;
        return;
    }
    else
    {
        cerr << "order name " << ordername << " order deleting" <<endl;
        dlorder->RequestID = ++iRequestID;
        dlorder->ActionFlag = THOST_FTDC_AF_Delete;
        trade->ReqOrderAction(dlorder);
    }
}
