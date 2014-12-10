#include "ctp_trade_qthread.h"
#include "ctp_trade.h"
#include<QMessageBox>
#include "mainwindow.h"

extern MainWindow * mw;

void ctp_trade_qthread::run()
{
    trade = new ctp_trade;
    trade->init(this);
}
void ctp_trade_qthread::delete_all_order()
{
    trade->delete_all_order();
}
void ctp_trade_qthread::check_add_order(const std::string & ID,const std::string & side ,const std::string & openclose ,const std::string & price ,const std::string & size)
{
    if(ID.size()>0 && side.size()>0 && openclose.size()>0 && price.size()>0 && size.size()>0)
    {
        trade->addorder(ID, side, openclose, QString::fromStdString(price).toDouble(), QString::fromStdString(size).toInt());
    }
    else
    {
        QMessageBox::information(mw,"ERROR","请填写合约名");
    }
}
