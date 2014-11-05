#include<stdio.h>
#include<stdlib.h> 
#include<iostream>
#include<string>
#include<Windows.h>

#include "mainwindow.h"
#include "sender.h"
#include <QApplication>
#include<QObject>
#include<QThread>



#include"ctp_quote.h"
#include"ctp_quote_qthread.h"

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

MainWindow * mw;
QApplication * qa;
Sender * sd;

void start_ctp();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qa=&a;
    Sender sender;
    sd=&sender;
    MainWindow w;
    mw=&w;

    w.show();
//    sender.show();

    qRegisterMetaType<string>("std::string");
    QObject::connect(sd, &Sender::broadcastSignal, mw,&MainWindow::show_quote);

    start_ctp();

	return a.exec();
}


void start_ctp()
{
    simu_cfg.setcfgfile("c:/cfg/simu_trade.cfg");
    simu_bars_manage.addbarlist(simu_cfg.getparam("INSTRUMENT_ID"));


    ctp_quote_qthread * cqq=new ctp_quote_qthread;
    cqq->start();
    //    ctp_quote simu_quote;
}
