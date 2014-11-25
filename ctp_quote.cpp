#include"ctp_quote.h"

#include<iostream>
#include<iomanip>
#include<string>
#include<sstream>
#include<list>
#include<windows.h>

#include "mainwindow.h"
#include<QApplication>

#include"../gpp_qt/cfg/cfg.h"
#include"../gpp_qt/log_info/log_info.h"
#include"../gpp_qt/wtimer/wtimer.h"
#include"../gpp_qt/bar/bars_manage.h"
#include"../gpp_qt/wfunction/wfunction.h"

#include"ctp/ThostFtdcMdApi.h"

#include"ctp_quote_qthread.h"
extern cfg simu_cfg;
extern bars_manage simu_bars_manage;
extern wtimer tm;
extern log_info simu_log;


using namespace std;

ctp_quote::ctp_quote(ctp_quote_qthread * father)
{
    pfather=father;
    ctp_quote();
}
ctp_quote::ctp_quote()
{
    pUserApi=CThostFtdcMdApi::CreateFtdcMdApi(mk_quote_con_dir());
    this->init();
    this->login();
}
void ctp_quote::init()
{
	nRequestID=0;
	nppInstrumentID=0;
	ctp_time_length=sizeof(TThostFtdcTimeType);
	
	req=new CThostFtdcReqUserLoginField;
	memset(req, 0, sizeof(*req));
	strncpy(req->BrokerID,const_cast<char*>(simu_cfg.getparam("BROKER_ID").c_str()),sizeof(req->BrokerID));
	strncpy(req->UserID,const_cast<char*>(simu_cfg.getparam("INVESTOR_ID").c_str()),sizeof(req->UserID));
	strncpy(req->Password,const_cast<char*>(simu_cfg.getparam("PASSWORD").c_str()),sizeof(req->Password));


	ppInstrumentID=new char * [MAX_CONTRACT_NUMBER];
	list<string> contracts=wfunction::splitstring(simu_cfg.getparam("INSTRUMENT_ID"));
	for(list<string>::iterator iter=contracts.begin();iter!=contracts.end();iter++)
	{
		ppInstrumentID[nppInstrumentID]=new char [MAX_CONTRACT_NAME];
		memset(ppInstrumentID[nppInstrumentID],'\0',MAX_CONTRACT_NAME);
		strncpy(ppInstrumentID[nppInstrumentID],iter->c_str(),iter->size());
		nppInstrumentID++;
        cout<<"INFO: quote contract   "<<iter->c_str()<<endl;
    }
    cout << "INFO: BrokerID: "<<req->BrokerID<<endl;
    cout << "INFO: UserID: "<<req->UserID<<endl;
}

void ctp_quote::login()
{
    pUserApi->RegisterSpi(this);
    pUserApi->RegisterFront(const_cast<char*>(simu_cfg.getparam("QUOTE_FRONT_ADDR").c_str()));
	pUserApi->Init();
	pUserApi->Join();
}
void ctp_quote::ReqUserLogin()
{
	int iResult = pUserApi->ReqUserLogin(req, ++nRequestID);
	cout << "--->>> 发送用户登录请求: " << ((iResult == 0) ? "成功" : "失败") << endl;
}

void ctp_quote::OnRspError(CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast)
{
	//尚不清楚在具体哪种情况下会触发此回调
	cout<< "--->>> "<< "OnRspError\t RequeseID="<<nRequestID<< endl;
	IsErrorRspInfo(pRspInfo);
}
void ctp_quote::OnFrontDisconnected(int nReason)
{
	cout << "--->>> " << "OnFrontDisconnected" << endl;
	cout << "Reasons\n\t0x1001 网络读失败\n\t0x1002 网络写失败\n\t0x2001 接收心跳超时\n\t0x2002 发送心跳失败\n\t0x2003 收到错误报文"<<endl;
	cout << "\tReason = " << nReason << endl;
}

///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
void ctp_quote::OnFrontConnected()
{
	cout << "--->>> " << "OnFrontConnected" << endl;
	ReqUserLogin();
}
	
///登录请求响应
void ctp_quote::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "--->>> " << "OnRspUserLogin" << endl;
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		///获取当前交易日
		cout << "--->>> 获取当前交易日 = " << pUserApi->GetTradingDay()<< endl;
		// 请求订阅行情
		SubscribeMarketData();
	}
}
void ctp_quote::SubscribeMarketData()
{
	int iResult = pUserApi->SubscribeMarketData(ppInstrumentID, nppInstrumentID);
	cout << "--->>> 发送行情订阅请求: " << ((iResult == 0) ? "成功" : "失败") << endl;
}

///订阅行情应答
void ctp_quote::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "OnRspSubMarketData" << endl;
}

///取消订阅行情应答
void ctp_quote::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "OnRspUnSubMarketData" << endl;
}

///深度行情通知
void ctp_quote::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
    //tm must be set before any slots.
    tm.settic(atof(wfunction::ctp_time_char_convert(pDepthMarketData->UpdateTime,sizeof(TThostFtdcTimeType))));
    pfather->broadcast_markerdata(pDepthMarketData);
}
bool ctp_quote::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
	bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (bResult)
		cout << "--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << endl;
	return bResult;
}
char *ctp_quote::mk_quote_con_dir()
{
        string exedir=simu_cfg.getparam("QUOTE_CON_PATH");
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
            exedir=exedir+"/quote_con";
            wfunction::wmkdir(exedir);
        }
        return const_cast<char*>((exedir+"/").c_str());
}
