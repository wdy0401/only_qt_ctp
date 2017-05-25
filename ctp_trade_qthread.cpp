#include "ctp_trade_qthread.h"
#include "ctp_trade.h"
#include<QMessageBox>
#include "mainwindow.h"
#include<string>
#include"../gpp_qt/cfg/cfg.h"
#include"ctp_order_manager.h"

using namespace std;


extern cfg cfg_info;

void ctp_trade_qthread::run()
{
    trade->init(this);
}
void ctp_trade_qthread::init()
{
    trade = new ctp_trade;
    order_manager->set_trade(trade);

    QObject::connect(mw, &MainWindow::check_add_order, this, &ctp_trade_qthread::check_add_order);
    QObject::connect(mw, &MainWindow::check_position, this, &ctp_trade_qthread::check_position);
    QObject::connect(trade,&ctp_trade::show_warning,mw,&MainWindow::show_string_quote);

    QObject::connect(trade,&ctp_trade::show_warning,order_manager,&ctp_order_manager::show_warning);
    QObject::connect(trade,&ctp_trade::send_rtn_order,order_manager,&ctp_order_manager::OnRtnOrder);
    QObject::connect(trade,&ctp_trade::send_rtn_trade,order_manager,&ctp_order_manager::OnRtnTrade);
    QObject::connect(trade,&ctp_trade::OnLogin,order_manager,&ctp_order_manager::OnLogin);

    //mainwindow到check_position
}
bool ctp_trade_qthread::check_init_para()
{
    if(cfg_info.get_para("TRADE_FRONT_ADDR")=="")
    {
        QMessageBox::information(mw, "ERROR", "TRADE_FRONT_ADDR not exist !");
        this->exit();
        return false;
    }
    return true;
}
void ctp_trade_qthread::check_add_order(const std::string & ID,const std::string & side ,const std::string & openclose ,const std::string & price ,const std::string & size)
{
	if (ID.empty())
	{
        QMessageBox::information(mw, "ERROR", "合约为空");
	}
	else if (side.empty())
	{
        QMessageBox::information(mw, "ERROR", "缺少方向");
	}
	else if (openclose.empty())
	{
        QMessageBox::information(mw, "ERROR", "缺少开平仓");
	}
	else if (price.empty())
	{
        QMessageBox::information(mw, "ERROR", "缺少价格");
	}
	else if (size.empty())
	{
        QMessageBox::information(mw, "ERROR", "缺少手数");
	}
	else
    {
        string sd=side=="买入"?"BUY":"SELL";
        string oc=openclose=="开新仓"?"OPEN":openclose=="平今"?"CLOSET":"CLOSE";
        order_manager->new_order(ID, sd, oc, QString::fromStdString(price).toDouble(), QString::fromStdString(size).toInt());
	}
}

//void ctp_trade_qthread::check_position(const std::string & ctr)
void ctp_trade_qthread::check_position()
{
    //trade->ReqQryInvestorPosition(ctr);
    trade->ReqQryInvestorPosition("IF1707");
}
