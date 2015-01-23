#include<stdio.h>
#include<stdlib.h> 
#include<iostream>
#include<string>

#include"mainwindow.h"
#include"sender.h"
#include<QApplication>
#include<QObject>
#include<QThread>
#include <QTextCodec>

#include"../libs/ctp/ThostFtdcMdApi.h"
#include"../libs/ctp/ThostFtdcTraderApi.h"

#include"../gpp_qt/cfg/cfg.h"
#include"../gpp_qt/bar/bar.h"
#include"../gpp_qt/bar/bars.h"
#include"../gpp_qt/wtimer/wtimer.h"
#include"../gpp_qt/bar/bars_manage.h"
#include"../gpp_qt/wfunction/wfunction.h"
#include"../gpp_qt/log_info/log_info.h"

#include"ctp_quote.h"
#include"ctp_quote_qthread.h"
#include"ctp_trade.h"
#include"ctp_trade_qthread.h"
#include"ctp_log.h"
#include"ctp_manager.h"
#include"ctp_order_manager.h"
using namespace std;

wtimer tm;
cfg simu_cfg;
log_info simu_log;//ctp log
log_info loginfo;//gpp_qt log
ctp_log ctp_quote_log;//qoute log
bars_manage simu_bars_manage;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication * qa=&a;
    MainWindow w;
    MainWindow * mw=&w;
    mw->set_qa(qa);

	//reg string
    qRegisterMetaType<string>("std::string");


    //load simu para
    simu_cfg.setcfgfile("c:/cfg/simu_trade.cfg");

    //set para
    simu_bars_manage.addbarlist(simu_cfg.getparam("INSTRUMENT_ID"));
    simu_log.set_file("d:/record/"+wfunction::get_now_second()+".txt");
    ctp_quote_log.set_file("d:/record/quote_"+wfunction::get_now_second()+".csv");

    //set cm ordermanager and tactic

    ctp_manager * cm=new ctp_manager();
    cm->set_mainwindow(mw);
    cm->init();
    mw->set_ctp_manager(cm);

    ctp_order_manager * order_manager=new ctp_order_manager;
    tactic * tc=new tactic;
    order_manager->init();
    order_manager->set_mw(mw);
    cm->set_ctp_order_mamager(order_manager);
    cm->set_tactic(tc);

    w.init();
    w.show();

    return a.exec();
}

