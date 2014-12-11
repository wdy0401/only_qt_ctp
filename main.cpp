#include<stdio.h>
#include<stdlib.h> 
#include<iostream>
#include<string>
//#include<Windows.h>

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
#include"ctp_manage.h"
using namespace std;

wtimer tm;
cfg simu_cfg;
log_info simu_log;//ctp log
log_info loginfo;//gpp_qt log
ctp_log ctp_quote_log;//qoute log
bars_manage simu_bars_manage;

MainWindow * mw;
QApplication * qa;


ctp_manage * cm;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qa=&a;
    MainWindow w;
    mw=&w;

	//reg string
    qRegisterMetaType<string>("std::string");


    //load simu para
    simu_cfg.setcfgfile("c:/cfg/simu_trade.cfg");

    //set cm
    cm=new ctp_manage();

    //set para
    simu_bars_manage.addbarlist(simu_cfg.getparam("INSTRUMENT_ID"));
    simu_log.setfile("d:/record/"+wfunction::get_now_second()+".txt");
    ctp_quote_log.setfile("d:/record/quote_"+wfunction::get_now_second()+".csv");

    w.init();
    w.show();

    return a.exec();
}

/*
void start_ctp_quote()
{
	mw->setWindowTitle(QString::fromStdString(simu_cfg.getparam("FEED_SOURSE")));
	
    cqq = new ctp_quote_qthread;
	QObject::connect(cqq, &ctp_quote_qthread::broadcast_markerdata, mw, &MainWindow::show_quote_1);
	QObject::connect(cqq, &ctp_quote_qthread::broadcast_markerdata, mw, &MainWindow::show_quote_label);
	QObject::connect(cqq, &ctp_quote_qthread::broadcast_markerdata, &ctp_quote_log, &ctp_log::writeinfo);

	cqq->start();
}
void start_ctp_trade()
{
	mw->setWindowTitle(QString::fromStdString(simu_cfg.getparam("FEED_SOURSE")));
	
    ctq = new ctp_trade_qthread;
    QObject::connect(mw, &MainWindow::check_add_order, ctq, &ctp_trade_qthread::check_add_order);
    QObject::connect(mw, &MainWindow::on_pushButton_4_clicked, ctq, &ctp_trade_qthread::delete_all_pending_order);

    ctq->start();
}
*/
