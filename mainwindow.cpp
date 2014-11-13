#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QString>
#include<iostream>
#include<string>
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
void MainWindow::show_quote(const string &text)
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
    this->show_quote("button pushed");
    if(!ctp_is_start)
    {
        start_ctp();
        this->show_quote("Start quote");
        ctp_is_start=true;
    }
    else
    {
        this->show_quote("Quote is running");
    }
}
