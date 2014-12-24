#include "ctp_order_manager.h"

#include"mainwindow.h"
#include<QMessageBox>

#include<map>
#include<string>
#include<iostream>

#include"../gpp_qt/wfunction/wfunction.h"
#include"../gpp_qt/cfg/cfg.h"

#include"../../libs/ctp/ThostFtdcTraderApi.h"
#include"tactic.h"
extern cfg simu_cfg;

using namespace std;

void ctp_order_manager::init()
{
    _ordercount=0;
    _order_ref_sz=sizeof(TThostFtdcOrderRefType);

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
    ordername=InstrumentID+"#"+side+"#"+openclose+"#"+wfunction::ftos(price)+"#"+wfunction::itos(size)+"#"+wfunction::itos(porder->RequestID);
    cerr << "Order name\t" << ordername << endl;

    if(_ordername_iRequestID.find(ordername)!=_ordername_iRequestID.end())
    {
        _ordername_iRequestID[ordername].push_back(porder->RequestID);
    }
    else
    {
        list<long> tmplist;
        tmplist.push_back(porder->RequestID);
        _ordername_iRequestID[ordername]=tmplist;
    }
    ctp_order * ctporder=new ctp_order(porder,this);
    _ordername_order[ordername]=ctporder;
    _iRequestID_ordername[porder->RequestID]=ordername;

    trade->ReqOrderInsert(porder);
    return ordername;
}
void ctp_order_manager::OnLogin(CThostFtdcRspUserLoginField *pRspUserLogin)
{
    FRONT_ID = pRspUserLogin->FrontID;
    SESSION_ID = pRspUserLogin->SessionID;
    strcpy(this->MaxOrderRef,pRspUserLogin->MaxOrderRef);
    this->nowref=atoi(this->MaxOrderRef);
}
void ctp_order_manager::OnRtnOrder(CThostFtdcOrderField *p)
{
    static string fillstr;
    cerr << endl << "--->>> OnRtnOrder" <<endl;
    if(p->FrontID!=this->FRONT_ID || p->SessionID!=this->SESSION_ID)
    {
        cerr << "Rtn from other ctp"<<endl;
        cerr << "Rtn FrontID " << p->FrontID<<"\tSessionID\t"<<p->SessionID<<endl;
        cerr << "This FrontID " << this->FRONT_ID<<"\tSessionID\t"<<this->SESSION_ID<<endl;
        return;
    }
    std::map <long, std::string>::iterator iter=_iRequestID_ordername.find(p->RequestID);
    if(iter==_iRequestID_ordername.end())
    {
        cerr << "ERROR: order not in list"
             << "\tBrokerID\t"<<p->BrokerID
             << "\tBrokerOrderSeq\t"<<p->BrokerOrderSeq
             << "\tExchangeID\t"<<p->ExchangeID
             << "\tOrderSysID\t"<<p->OrderSysID
             << "\tTraderID\t"<<p->TraderID
             << "\tInstrumentID\t"<<p->InstrumentID
             <<endl;
        return;
    }
//    /////////////////////////////////////////////////////////////////////////
//    ///TFtdcOrderStatusType是一个报单状态类型
//    /////////////////////////////////////////////////////////////////////////
//    ///
//    ///全部成交
//    #define THOST_FTDC_OST_AllTraded '0'

//    ///部分成交还在队列中
//    #define THOST_FTDC_OST_PartTradedQueueing '1'

//    ///部分成交不在队列中
//    #define THOST_FTDC_OST_PartTradedNotQueueing '2'

//    ///未成交还在队列中
//    #define THOST_FTDC_OST_NoTradeQueueing '3'

//    ///未成交不在队列中
//    #define THOST_FTDC_OST_NoTradeNotQueueing '4'

//    ///撤单
//    #define THOST_FTDC_OST_Canceled '5'

//    ///未知
//    #define THOST_FTDC_OST_Unknown 'a'

//    ///尚未触发
//    #define THOST_FTDC_OST_NotTouched 'b'

//    ///已触发
//    #define THOST_FTDC_OST_Touched 'c'

//    typedef char TThostFtdcOrderStatusType;

    ///全部成交
    if(p->OrderStatus == THOST_FTDC_OST_AllTraded)
    {
        fillstr= p->ExchangeID;
        fillstr+=p->OrderSysID;
        _fill_ordername[fillstr]=iter->second;
        emit done(iter->second,"FILL","ALL");
    }
    ///部分成交还在队列中
    else if(p->OrderStatus == THOST_FTDC_OST_PartTradedQueueing)
    {
        fillstr= p->ExchangeID;
        fillstr+=p->OrderSysID;
        _fill_ordername[fillstr]=iter->second;
        emit done(iter->second,"FILL","PART");
    }
    ///部分成交不在队列中
    else if(p->OrderStatus == THOST_FTDC_OST_PartTradedNotQueueing)
    {
        emit done(iter->second,"CANCEL","PART_NOTQUEUE");
    }
    ///未成交还在队列中
    else if(p->OrderStatus == THOST_FTDC_OST_NoTradeQueueing)
    {
        fillstr= p->ExchangeID;
        fillstr+=p->OrderSysID;
        _fill_ordername[fillstr]=iter->second;
        emit ack(iter->second,"SEND","EXG_ACK");
    }
    ///未成交不在队列中
    else if(p->OrderStatus == THOST_FTDC_OST_NoTradeNotQueueing)
    {
        emit rej(iter->second,"SEND","EXG_ACK");
    }
    ///撤单
    else if(p->OrderStatus == THOST_FTDC_OST_Canceled)
    {
        if(_ordername_order[iter->second]->of->OrderStatus==THOST_FTDC_OST_Unknown)
        {
            emit rej(iter->second,"SEND","EXG_ACK");
        }
        else
        {
            emit done(iter->second,"CANCEL","DONE");
        }
    }
    ///未知 ctp已接受 还未发到交易所
    else if(p->OrderStatus == THOST_FTDC_OST_Unknown)
    {
        emit ack(iter->second,"SEND","CTP_ACK");
    }
    ///尚未触发
    else if(p->OrderStatus == THOST_FTDC_OST_NotTouched)
    {
        emit ack(iter->second,"SEND","CTP_ACK_NOTTOUCH");
    }
    ///已触发
    else if(p->OrderStatus == THOST_FTDC_OST_Touched)
    {
        emit ack(iter->second,"SEND","CTP_ACK_TOUCHED");
    }
    else
    {
        cerr << "Unknow OrderStatus"<< p->OrderStatus <<endl;
    }
    _ordername_order[iter->second]->of->OrderStatus=p->OrderStatus;

    cerr << "FrontID\t" << p->FrontID << endl;
    cerr << "SessionID\t" << p->SessionID << endl;
    cerr << "OrderRef\t" << p->OrderRef << endl;
    cerr << "OrderStatus\t" << p->OrderStatus << endl;
    cerr << "iRequestID\t" << p->RequestID << endl;
    cerr << "ExchangeID\t"<< p->ExchangeID <<endl;
    cerr << "OrderSysID\t"<< p->OrderSysID <<endl;
}
void ctp_order_manager::OnRtnTrade(CThostFtdcTradeField *p)
{
    cerr << endl << "--->>> OnRtnTrade" <<endl;
    static string fillstr;
    fillstr= p->ExchangeID;
    fillstr+=p->OrderSysID;

    std::map <std::string, std::string>::iterator iter=_fill_ordername.find(fillstr);
    if(iter==_fill_ordername.end())
    {
        cerr << "ERROR: order not in list"
             << "\tBrokerID\t"<<p->BrokerID
             << "\tBrokerOrderSeq\t"<<p->BrokerOrderSeq
             << "\tExchangeID\t"<<p->ExchangeID
             << "\tOrderSysID\t"<<p->OrderSysID
             << "\tTraderID\t"<<p->TraderID
             << "\tInstrumentID\t"<<p->InstrumentID
             <<endl;
        return;
    }
    emit fill(iter->second,p->InstrumentID,p->Price,p->Volume);
    cerr << "OrderRef\t" << p->OrderRef << endl;
    cerr << "Fill size\t" << p->Volume<<endl;
    cerr << "Fill price\t" << p->Price<<endl;
    show_warning("Warning from OnRtnTrade");
}
CThostFtdcInputOrderField * ctp_order_manager::initorder(const string & InstrumentID, const string & side, const string & openclose, double price, long size)
{
    cerr << endl << "--->>> Init order" << endl;
    cerr << "Local Init order\t" << InstrumentID << "\t" << side << "\t" << openclose << "\t" << price << "\t" << size << endl;
    CThostFtdcInputOrderField * oireq = new CThostFtdcInputOrderField;
    memset(oireq, 0, sizeof(CThostFtdcInputOrderField));

    ///经纪公司代码
    strncpy(oireq->BrokerID, const_cast<char*>(simu_cfg.getparam("BROKER_ID").c_str()), sizeof(oireq->BrokerID));
    ///投资者代码
    strncpy(oireq->InvestorID, const_cast<char*>(simu_cfg.getparam("INVESTOR_ID").c_str()), sizeof(oireq->InvestorID));
    ///合约代码
    strncpy(oireq->InstrumentID, const_cast<char*>(InstrumentID.c_str()), sizeof(oireq->InstrumentID));
    ///报单引用
    add_OrderRef();
    strncpy(oireq->OrderRef,this->NowOrderRef, sizeof(TThostFtdcOrderRefType));
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

    ///请求编号
    oireq->RequestID=trade->add_iRequestID();

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
    std::map <std::string, ctp_order *>::iterator iter = _ordername_order.find(ordername);
    if (iter == _ordername_order.end())
    {
        return nullptr;
    }
    else
    {
        CThostFtdcOrderField * pOrder = iter->second->of;
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

        ///请求编号
        cgreq->RequestID=trade->add_iRequestID();;
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
        cgorder->RequestID = trade->add_iRequestID();
        cgorder->LimitPrice = price;
        cgorder->VolumeChange = size;
        cgorder->ActionFlag = THOST_FTDC_AF_Modify;
        trade->ReqOrderAction(cgorder);
    }
}
void ctp_order_manager::cancel_all_order()
{
    for(std::map <std::string, ctp_order *>::iterator iter =_ordername_order.begin();iter!=_ordername_order.end();iter++)
    {
        if(iter->second->of->OrderStatus==THOST_FTDC_OST_NoTradeQueueing
                || iter->second->of->OrderStatus==THOST_FTDC_OST_PartTradedQueueing
                || iter->second->of->OrderStatus==THOST_FTDC_OST_Unknown
                || iter->second->of->OrderStatus==THOST_FTDC_OST_NotTouched
                || iter->second->of->OrderStatus==THOST_FTDC_OST_Touched
                )
        {
            cancel_order(iter->first);
        }
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
        rej(ordername,"CANCEL","NOTFOUND");
        return;
    }
    else
    {
        cerr << "order name " << ordername << " order deleting" <<endl;
        dlorder->RequestID = trade->add_iRequestID();
        dlorder->ActionFlag = THOST_FTDC_AF_Delete;
        ack(ordername,"CANCEL","LOCAL_ACK");
        trade->ReqOrderAction(dlorder);
    }
}
void ctp_order_manager::add_OrderRef()
{
    this->nowref++;
    int tmpint=this->nowref;
    this->NowOrderRef[_order_ref_sz-1]='\0';
    for(string::size_type i=2 ;i<= _order_ref_sz;i++)
    {
        this->NowOrderRef[_order_ref_sz-i]=48+tmpint%10;
        tmpint=tmpint/10;
    }
}
