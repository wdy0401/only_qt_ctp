#include "tactic.h"
#include"ctp_order_manager.h"
#include<iostream>
using namespace std;

void tactic::init()
{
    _pause=false;
    ordersize=0;
    ordersize_1=0;
    lasttradeprice=0;
    lasttradeprice_1=0;
}
void tactic::set_ctp_order_manager(ctp_order_manager * p)
{
    om=p;
}
void tactic::book(const CThostFtdcDepthMarketDataField *pDepthMarketData)
{
//    cerr <<endl << "Tactic Book" << endl;
}
void tactic::quote(const std::string & symbol, const std::string & ba, long level, double price, long quotesize)
{
    if(_pause==true)
    {
        return;
    }
    //    cerr <<"now ordersize\t"<<ordersize<< "\tnow price\t " <<price << "\tlast trade price\t" << lasttradeprice <<endl;
    if(symbol=="IF1501")
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
    if(symbol=="IF1503")
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
                ordersize_1--;
            }
            if(price-lasttradeprice_1<-1*LIMITSTEP)
            {
                om->new_order(symbol,"SELL","OPEN",price-PRICESTEP,ORDERSZ);
                lasttradeprice_1=price;
                ordersize_1++;
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
    cerr<<endl<<"--->>> ack from tactic"<<endl;
    cerr << "ordername " << ordername <<"\ttype\t"<<type<<"\tinfo\t"<<info<<endl;
}
void tactic::done(const std::string & ordername,const std::string & type,const std::string & info)
{
    cerr<<endl<<"--->>> done from tactic"<<endl;
    cerr << "ordername " << ordername <<"\ttype\t"<<type<<"\tinfo\t"<<info<<endl;
}
void tactic::rej(const std::string & ordername,const std::string & type,const std::string & info)
{
    cerr<<endl<<"--->>> rej from tactic"<<endl;
    cerr << "ordername " << ordername <<"\ttype\t"<<type<<"\tinfo\t"<<info<<endl;
}
void tactic::fill(const std::string & ordername,const std::string & symbol,double price, long size)
{
    cerr<<endl<<"--->>> fill from tactic"<<endl;
    cerr << "ordername " << ordername <<"\tsymbol\t"<<symbol <<"\tprice\t"<<price<<"\tsize\t"<<size<<endl;
}
