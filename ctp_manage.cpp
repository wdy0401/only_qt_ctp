#include"ctp_manage.h"
#include"ctp_quote_qthread.h"
#include"ctp_trade_qthread.h"
#include"ctp_log.h"

#include"../gpp_qt/cfg/cfg.h"

#include "mainwindow.h"

extern cfg simu_cfg;
extern ctp_log ctp_quote_log;
extern MainWindow *mw;

ctp_manage::ctp_manage()
{
    ctp_quote_running=false;
    ctp_trade_running=false;
}
bool ctp_manage::check_trade_init_para()
{
    if(simu_cfg.getparam("TRADE_FRONT_ADDR")=="")
    {
        return false;
    }
    return true;
}
bool ctp_manage::check_quote_init_para()
{
    if(simu_cfg.getparam("QUOTE_FRONT_ADDR")=="")
    {
        return false;
    }
    return true;
}
void ctp_manage::start_ctp_quote()
{
    if(!ctp_quote_running)
    {
        if(this->check_quote_init_para())
        {
            ctp_quote_qthread  * cqq;
            cqq = new ctp_quote_qthread;
            QObject::connect(cqq, &ctp_quote_qthread::broadcast_markerdata, mw, &MainWindow::show_quote_1);
            QObject::connect(cqq, &ctp_quote_qthread::broadcast_markerdata, mw, &MainWindow::show_quote_label);
            QObject::connect(cqq, &ctp_quote_qthread::broadcast_markerdata, &ctp_quote_log, &ctp_log::writeinfo);
            mw->show_string_quote("Start quote");
            ctp_quote_running = true;
            cqq->start();
        }
        else
        {
            QMessageBox::information(mw, "ERROR", "QUOTE_FRONT_ADDR not exist !");
            mw->show_string_quote("ERROR:\tQUOTE_FRONT_ADDR not exist !");
        }
    }
    else
    {
        QMessageBox::information(mw, "INFO","Quote is running");
        mw->show_string_quote("Quote is running");
    }
}
void ctp_manage::start_ctp_trade()
{
    if(!ctp_trade_running)
    {
        if(this->check_trade_init_para())
        {
            ctp_trade_qthread  * ctq;
            ctq = new ctp_trade_qthread;
            QObject::connect(mw, &MainWindow::check_add_order, ctq, &ctp_trade_qthread::check_add_order);
            QObject::connect(mw, &MainWindow::on_pushButton_4_clicked, ctq, &ctp_trade_qthread::delete_all_pending_order);
            mw->show_string_trade("Start trade");
            ctp_trade_running = true;
            ctq->init();
            ctq->start();
        }
        else
        {
            QMessageBox::information(mw, "ERROR", "TRADE_FRONT_ADDR not exist !");
            mw->show_string_trade("ERROR:\tTRADE_FRONT_ADDR not exist !");
        }
    }
    else
    {
        QMessageBox::information(mw, "INFO","Trade is running");
        mw->show_string_trade("Trade is running");
    }
}
