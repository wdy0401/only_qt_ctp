#include "tactic.h"
#include"ctp_order_manager.h"
#include<iostream>
using namespace std;

void tactic::init()
{
    ordersize=0;
    lastprice=0;
    lasttradeprice=0;
}
void tactic::set_ctp_order_manager(ctp_order_manager * p)
{
    om=p;
}
void tactic::quote(const std::string & symbol, const std::string & ba, long level, double price, long quotesize)
{
//    cerr <<"now ordersize\t"<<ordersize<< "\tnow price\t " <<price << "\tlast trade price\t" << lasttradeprice <<endl;
    if(symbol=="IF1412")
    {
        if(lastprice==0)
        {
            lastprice=price;
        }
        if(lasttradeprice==0)
        {
            lasttradeprice=price;
        }

        if(ordersize==0)
        {
            if(price-lastprice>1*LIMITSTEP)
            {
                om->new_order(symbol,"SELL","OPEN",price-PRICESTEP,ORDERSZ);
                lasttradeprice=price;
                ordersize--;
            }
            if(price-lastprice<-1*LIMITSTEP)
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
}
