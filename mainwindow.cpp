#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QString>
#include<QLabel>
#include<Qfont>
#include<QPalette>

#include<map>
#include<iostream>
#include<string>
#include<list>
#include<iomanip>

#include"../gpp_qt/cfg/cfg.h"
#include"../gpp_qt/log_info/log_info.h"
#include"../gpp_qt/wtimer/wtimer.h"
#include"../gpp_qt/bar/bars_manage.h"
#include"../gpp_qt/wfunction/wfunction.h"

using namespace std;

extern QApplication * qa;
extern wtimer tm;
extern void start_ctp();
extern log_info simu_log;
extern bars_manage simu_bars_manage;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ctp_is_start=false;
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::set_symbols_display(const std::string & symbols)
{
    list<string> symbol_list=wfunction::splitstring(symbols);
    for(list<string>::iterator iter=symbol_list.begin();iter!=symbol_list.end();iter++)
    {
//if we want to use two color on symbol and price
//two qlabel is needed
//a new class is needed
        QLabel * ql=new QLabel();
        this->ui->horizontalLayout->addWidget(ql);
        ql->setText(QString::fromStdString(*iter));
        QPalette * pe=new QPalette;
        pe->setColor(QPalette::WindowText,Qt::red);
        ql->setPalette(*pe);
        ql->setFont(QFont("微软雅黑",14,-1,false));
        quote_labels[*iter]=ql;
    }
}
void MainWindow::show_quote_label(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
    symbol_price_display(pDepthMarketData->InstrumentID, pDepthMarketData->LastPrice);
}
void MainWindow::symbol_price_display(const string & symbol, double price)
{
    map<string,QLabel *>::iterator iter=quote_labels.find(symbol);
    if(iter!=quote_labels.end())
    {
     //   iter->second()->setText( QString("'f' format, precision 2, gives %1" ).arg(price));
        quote_labels[symbol]->setText(QString::fromStdString(symbol)+QString("\n%1" ).arg(price,0,'f',2));
        qa->processEvents();
    }
    else
    {
        cout<<"Error: function MainWindow::symbol_display"<<endl;
    }
}


void MainWindow::show_string(const string &text)
{
    this->ui->textBrowser->append(QString::fromStdString(text));
    qa->processEvents();
}
void MainWindow::show_quote_1(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
    cout<< pDepthMarketData->TradingDay;
    cout<< "," << pDepthMarketData->UpdateTime;
    cout<< ":" << pDepthMarketData->UpdateMillisec;
    cout<< "," << pDepthMarketData->InstrumentID;
    cout<< "," << pDepthMarketData->BidPrice1;
    cout<< "," << pDepthMarketData->AskPrice1;
    cout<< "," << pDepthMarketData->BidVolume1;
    cout<< "," << pDepthMarketData->AskVolume1;
    cout<< "," << pDepthMarketData->LastPrice;
    cout<< "," << pDepthMarketData->HighestPrice;
    cout<< "," << pDepthMarketData->LowestPrice;
    cout<< "," << pDepthMarketData->Volume;
    cout<< endl;

    ostringstream os;
    os<< pDepthMarketData->TradingDay;
    os<< "," << pDepthMarketData->UpdateTime;
    os<< ":" << pDepthMarketData->UpdateMillisec;
    os<< "," << pDepthMarketData->InstrumentID;
    os<< "," << pDepthMarketData->BidPrice1;
    os<< "," << pDepthMarketData->AskPrice1;
    os<< "," << pDepthMarketData->BidVolume1;
    os<< "," << pDepthMarketData->AskVolume1;
    os<< "," << pDepthMarketData->LastPrice;
    os<< "," << pDepthMarketData->HighestPrice;
    os<< "," << pDepthMarketData->LowestPrice;
    os<< "," << pDepthMarketData->Turnover;
    os.setf(ios::fixed);
    os<<setprecision(10);
    os<< "," << pDepthMarketData->AveragePrice;
    os.setf(ios::fixed);
    os<<setprecision(2);
    os<< "," << pDepthMarketData->PreSettlementPrice;
    os<< "," << pDepthMarketData->SettlementPrice;
    os<< endl;
    simu_log.writeinfo(os.str());

    //    tm.settic(atof(wfunction::ctp_time_char_convert(pDepthMarketData->UpdateTime,ctp_time_length)));
    tm.settic(atof(wfunction::ctp_time_char_convert(pDepthMarketData->UpdateTime,sizeof(TThostFtdcTimeType))));
    simu_bars_manage.updatebar(pDepthMarketData->InstrumentID,pDepthMarketData->LastPrice);

     string ctpinfo= pDepthMarketData->UpdateTime;
     ctpinfo+="\t";
     ctpinfo+=pDepthMarketData->InstrumentID;
     ctpinfo+="\t";
     ctpinfo+=wfunction::ftos(pDepthMarketData->LastPrice);
     this->ui->textBrowser->append(QString::fromStdString(wfunction::joinquote(ctpinfo)));
     qa->processEvents();
}

void MainWindow::on_pushButton_clicked()
{
    this->show_string("button pushed");
    if(!ctp_is_start)
    {
        start_ctp();
        this->show_string("Start quote");
        ctp_is_start=true;
    }
    else
    {
        this->show_string("Quote is running");
    }
}
