#include"ctp_manager.h"
#include"ctp_quote_qthread.h"
#include"ctp_trade_qthread.h"
#include"ctp_log.h"

#include"../gpp_qt/cfg/cfg.h"

#include "mainwindow.h"

extern cfg simu_cfg;
extern ctp_log ctp_quote_log;
extern MainWindow *mw;

ctp_manager::ctp_manager()
{
    ctp_quote_running=false;
    ctp_trade_running=false;
    QObject::connect(mw, &MainWindow::on_pushButton_4_clicked, this, &ctp_manager::run_tactic);
}
bool ctp_manager::check_trade_init_para()
{
    if(simu_cfg.getparam("TRADE_FRONT_ADDR")=="")
    {
        return false;
    }
    return true;
}
bool ctp_manager::check_quote_init_para()
{
    if(simu_cfg.getparam("QUOTE_FRONT_ADDR")=="")
    {
        return false;
    }
    return true;
}
void ctp_manager::start_ctp_quote()
{
    if(!ctp_quote_running)
    {
        if(this->check_quote_init_para())
        {
            ctp_quote_qthread  * cqq;
            cqq = new ctp_quote_qthread;
            QObject::connect(cqq, &ctp_quote_qthread::broadcast_marketdata, mw, &MainWindow::show_quote_1);
            QObject::connect(cqq, &ctp_quote_qthread::broadcast_marketdata, mw, &MainWindow::show_quote_label);
            QObject::connect(cqq, &ctp_quote_qthread::broadcast_marketdata, &ctp_quote_log, &ctp_log::writeinfo);
            mw->show_string_quote("Start quote");
            ctp_quote_running = true;
            cqq->set_ctp_order_manager(get_ctp_order_mamager());
            cqq->init();
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
void ctp_manager::start_ctp_trade()
{
    if(!ctp_trade_running)
    {
        if(this->check_trade_init_para())
        {
            ctp_trade_qthread  * ctq;
            ctq = new ctp_trade_qthread;
            mw->show_string_trade("Start trade");
            ctp_trade_running = true;
            ctq->set_ctp_order_manager(get_ctp_order_mamager());
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
void ctp_manager::run_tactic()
{
    if(ctp_quote_running)
    {
        om->set_tactic(tc);
        tc->init();
        tc->set_ctp_order_manager(om);
    }
    else
    {
        QMessageBox::information(mw, "INFO","Quote is NOT running. Please run quote first");
        mw->show_string_quote("Run quote before run tactic");
    }
}

