#include<stdio.h>
#include<stdlib.h> 
#include<iostream>
#include<Windows.h>

#include "mainwindow.h"
#include "sender.h"
#include <QApplication>


#include"ctp_quote.h"

#include"ctp/ThostFtdcMdApi.h"
#include"ctp/ThostFtdcTraderApi.h"

#include"gpp_qt/cfg/cfg.h"
#include"gpp_qt/bar/bar.h"
#include"gpp_qt/bar/bars.h"
#include"gpp_qt/wtimer/wtimer.h"
#include"gpp_qt/bar/bars_manage.h"
#include"gpp_qt/wfunction/wfunction.h"
#include<QTextBlock>
#include<QTextCursor>
using namespace std;

cfg simu_cfg;
bars_manage simu_bars_manage;
wtimer tm;
CThostFtdcMdApi * pUserApi;


Sender * sd;
void start_ctp();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Sender sender;
    sd=&sender;
//  MainWindow w;
//   w.show();
//   sender.show();
    start_ctp();

	return a.exec();
}


void start_ctp()
{
    simu_cfg.setcfgfile("c:/cfg/simu_trade.cfg");
    simu_bars_manage.addbarlist(simu_cfg.getparam("INSTRUMENT_ID"));
    pUserApi=CThostFtdcMdApi::CreateFtdcMdApi();
    ctp_quote simu_quote;
    simu_quote.init();
    simu_quote.login(pUserApi);
}
