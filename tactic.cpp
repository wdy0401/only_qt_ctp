#include "tactic.h"
#ifndef SIMU
#include"ctp_order_manager.h"
#endif
#include<iostream>
#include<QDebug>
using namespace std;

void tactic::init()
{
    _pause=false;
    ordersize=0;
    ordersize_1=0;
    lasttradeprice=0;
    lasttradeprice_1=0;
}
void tactic::book(const CThostFtdcDepthMarketDataField *p){if(p!=nullptr){;}}
//{
////    qDebug() <<endl << "Tactic Book" << endl;
//}
void tactic::quote(const std::string & symbol, const std::string & ba, long level, double price, long quotesize)
{
    if(_pause==true)
    {
        return;
    }
    if(ba.size()>0 && level>0 && price>0 && quotesize>0){}
#ifdef SIMU
    if(1)
#else
    if(symbol=="IF1503")
#endif
    {
        if(lasttradeprice==0)
        {
            lasttradeprice=price;
        }
        if(ordersize==0)
        {
            if(price-lasttradeprice>1*LIMITSTEP)
            {
                om->new_order(symbol,"SELL","OPEN",price-PRICESTEP,ORDERSZ);
                lasttradeprice=price;
                ordersize--;
            }
            if(price-lasttradeprice<-1*LIMITSTEP)
            {
                om->new_order(symbol,"BUY","OPEN",price+PRICESTEP,ORDERSZ);
                lasttradeprice=price;
                ordersize++;
            }
        }
        else if(ordersize>0)
        {
            if(price-lasttradeprice>1*LIMITSTEP)
            {
                om->new_order(symbol,"SELL","CLOSE",price-PRICESTEP,ORDERSZ);
                lasttradeprice=price;
                ordersize--;
            }
            if(price-lasttradeprice<-1*LIMITSTEP)
            {
                om->new_order(symbol,"BUY","OPEN",price+PRICESTEP,ORDERSZ);
                lasttradeprice=price;
                ordersize++;
            }
        }
        else if(ordersize<0)
        {
            if(price-lasttradeprice>1*LIMITSTEP)
            {
                om->new_order(symbol,"SELL","OPEN",price-PRICESTEP,ORDERSZ);
                lasttradeprice=price;
                ordersize--;
            }
            if(price-lasttradeprice<-1*LIMITSTEP)
            {
                om->new_order(symbol,"BUY","CLOSE",price+PRICESTEP,ORDERSZ);
                lasttradeprice=price;
                ordersize++;
            }
        }
    }
    if(symbol=="IF1502")
    {
        if(lasttradeprice_1==0)
        {
            lasttradeprice_1=price;
        }
        if(ordersize_1==0)
        {
            if(price-lasttradeprice_1>1*LIMITSTEP)
            {
                om->new_order(symbol,"BUY","OPEN",price+PRICESTEP,ORDERSZ);
                lasttradeprice_1=price;
                ordersize_1++;
            }
            if(price-lasttradeprice_1<-1*LIMITSTEP)
            {
                om->new_order(symbol,"SELL","OPEN",price-PRICESTEP,ORDERSZ);
                lasttradeprice_1=price;
                ordersize_1--;
            }
        }
        else if(ordersize_1>0)
        {
            if(price-lasttradeprice_1>1*LIMITSTEP)
            {
                om->new_order(symbol,"BUY","OPEN",price+PRICESTEP,ORDERSZ);
                lasttradeprice_1=price;
                ordersize_1++;
            }
            if(price-lasttradeprice_1<-1*LIMITSTEP)
            {
                om->new_order(symbol,"SELL","CLOSE",price-PRICESTEP,ORDERSZ);
                lasttradeprice_1=price;
                ordersize_1--;
            }
        }
        else if(ordersize_1<0)
        {
            if(price-lasttradeprice_1>1*LIMITSTEP)
            {
                om->new_order(symbol,"BUY","CLOSE",price+PRICESTEP,ORDERSZ);
                lasttradeprice_1=price;
                ordersize_1++;
            }
            if(price-lasttradeprice_1<-1*LIMITSTEP)
            {
                om->new_order(symbol,"SELL","OPEN",price-PRICESTEP,ORDERSZ);
                lasttradeprice_1=price;
                ordersize_1--;
            }
        }
    }
}

void tactic::ack(const std::string & ordername,const std::string & type,const std::string & info)
{
    qDebug()<<endl<<"--->>> ack from tactic"<<endl;
    qDebug() << "ordername " << ordername.c_str() <<"\ttype\t"<<type.c_str()<<"\tinfo\t"<<info.c_str()<<endl;
}
void tactic::done(const std::string & ordername,const std::string & type,const std::string & info)
{
    qDebug()<<endl<<"--->>> done from tactic"<<endl;
    qDebug() << "ordername " << ordername.c_str() <<"\ttype\t"<<type.c_str()<<"\tinfo\t"<<info.c_str()<<endl;
}
void tactic::rej(const std::string & ordername,const std::string & type,const std::string & info)
{
    qDebug()<<endl<<"--->>> rej from tactic"<<endl;
    qDebug() << "ordername " << ordername.c_str() <<"\ttype\t"<<type.c_str()<<"\tinfo\t"<<info.c_str()<<endl;
}
void tactic::fill(const std::string & ordername,const std::string & symbol,const std::string & buysell,double price, long size)
{
    qDebug()<<endl<<"--->>> fill from tactic"<<endl;
    qDebug() << "ordername " << ordername.c_str() <<"\tsymbol\t"<<symbol.c_str() << "\tbuysell\t"<< buysell.c_str() <<"\tprice\t"<<price<<"\tsize\t"<<size<<endl;
}
