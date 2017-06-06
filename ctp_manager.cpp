#include"ctp_manager.h"
#include"ctp_quote_qthread.h"
#include"ctp_trade_qthread.h"
#include"ctp_log.h"

#include"../gpp_qt/cfg/cfg.h"

#include "mainwindow.h"

extern cfg cfg_info;
extern ctp_log ctp_quote_log;

void ctp_manager::init()
{
    ctp_quote_running=false;
    ctp_trade_running=false;
    QObject::connect(mw, &MainWindow::on_pushButton_5_clicked, this, &ctp_manager::run_tactic);
    QObject::connect(mw, &MainWindow::on_pushButton_6_clicked, this, &ctp_manager::pause_tactic);
    QObject::connect(mw, &MainWindow::on_pushButton_16_clicked, this, &ctp_manager::resume_tactic);
}
bool ctp_manager::check_trade_init_para()
{
    if(cfg_info.get_para("TRADE_FRONT_ADDR")=="")
    {
        return false;
    }
    return true;
}
bool ctp_manager::check_quote_init_para()
{
    if(cfg_info.get_para("QUOTE_FRONT_ADDR")=="")
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
            mw->show_string_quote("Start quote");
            ctp_quote_running = true;
            cqq->set_ctp_order_manager(get_ctp_order_mamager());

            QObject::connect(cqq, &ctp_quote_qthread::broadcast_marketdata, mw, &MainWindow::show_quote_1);
            QObject::connect(cqq, &ctp_quote_qthread::broadcast_marketdata, mw, &MainWindow::show_quote_label);
            QObject::connect(cqq, &ctp_quote_qthread::broadcast_marketdata, &ctp_quote_log, &ctp_log::writeinfo);

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
            ctq->set_mainwindow(mw);

            QObject::connect(mw, &MainWindow::check_add_order, ctq, &ctp_trade_qthread::check_add_order);
            QObject::connect(mw, &MainWindow::check_position, ctq, &ctp_trade_qthread::check_position);

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
void ctp_manager::resume_tactic()
{
    mw->show_string_trade("Tactic resumed");
    tc->resume();
}
void ctp_manager::pause_tactic()
{
    mw->show_string_trade("Tactic paused");
    tc->pause();
}
void ctp_manager::run_tactic()
{
    if(ctp_quote_running)
    {
        om->set_tactic(tc);
        tc->init();
        tc->set_ctp_order_manager(om);
        mw->show_string_trade("Start tactic");
    }
    else
    {
        QMessageBox::information(mw, "INFO","Quote is NOT running. Please run quote first");
        mw->show_string_quote("Run quote before run tactic");
    }
}

void ctp_manager::check_pos()
{

}
