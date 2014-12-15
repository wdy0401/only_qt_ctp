#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QString>
#include<QLabel>
#include<Qfont>
#include<QPalette>
#include<QSize>
#include<QLineEdit>

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

#include"ctp_manage.h"

using namespace std;

extern QApplication * qa;
extern wtimer tm;
extern void start_ctp_quote();
extern ctp_manage * cm;
extern log_info simu_log;
extern cfg simu_cfg;
extern bars_manage simu_bars_manage;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
void MainWindow::init()
{
    set_symbols_display(simu_cfg.getparam("INSTRUMENT_ID"));
    set_order_send(simu_cfg.getparam("INSTRUMENT_ID"));
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_order_send(const std::string & symbols)
{
    this->ui->fontComboBox->clear();
    this->ui->fontComboBox->setFont(QFont("微软雅黑",9,-1,false));

    list<string> symbol_list=wfunction::splitstring(symbols);
    for(list<string>::iterator iter=symbol_list.begin();iter!=symbol_list.end();iter++)
    {
        this->ui->fontComboBox->addItem(QString::fromStdString(*iter));
    }

    this->ui->fontComboBox_2->clear();
    this->ui->fontComboBox_2->setFont(QFont("微软雅黑",9,-1,false));
    QRegExp rxp("^[1-9][0-9]{0,10}\\.?[1-9]{0,3}$");
    QValidator * validatorp = new QRegExpValidator(rxp,0);
    this->ui->fontComboBox_2->lineEdit()->setValidator(validatorp);
    this->ui->fontComboBox_2->setCurrentText("4000");

    this->ui->fontComboBox_3->clear();
    this->ui->fontComboBox_3->setFont(QFont("微软雅黑",9,-1,false));
    QRegExp rxs("^[1-9][0-9]{0,10}\\.?[1-9]{0,3}$");
    QValidator * validators = new QRegExpValidator(rxs,0);
    this->ui->fontComboBox_3->lineEdit()->setValidator(validators);
    this->ui->fontComboBox_3->setCurrentText("1");


    this->ui->comboBox ->clear();
    this->ui->comboBox->setFont(QFont("微软雅黑",9,-1,false));
    this->ui->comboBox->addItem("买入");
    this->ui->comboBox->addItem("卖出");

    this->ui->comboBox_2 ->clear();
    this->ui->comboBox_2->setFont(QFont("微软雅黑",9,-1,false));
    this->ui->comboBox_2->addItem("开新仓");
    this->ui->comboBox_2->addItem("平今");
    this->ui->comboBox_2->addItem("平昨");

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
        cerr<<"Error: function MainWindow::symbol_display"<<endl;
    }
}


void MainWindow::show_string_quote(const string &text)
{
    this->ui->textBrowser->append(QString::fromStdString(text));
    qa->processEvents();
}
void MainWindow::show_string_trade(const string &text)
{
    this->ui->textBrowser_2->append(QString::fromStdString(text));
    qa->processEvents();
}
void MainWindow::show_quote_1(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
    //输出信息太多 显得乱

//    cout<< pDepthMarketData->TradingDay;
//    cout<< "," << pDepthMarketData->UpdateTime;
//    cout<< ":" << pDepthMarketData->UpdateMillisec;
//    cout<< "," << pDepthMarketData->InstrumentID;
//    cout<< "," << pDepthMarketData->BidPrice1;
//    cout<< "," << pDepthMarketData->AskPrice1;
//    cout<< "," << pDepthMarketData->BidVolume1;
//    cout<< "," << pDepthMarketData->AskVolume1;
//    cout<< "," << pDepthMarketData->LastPrice;
//    cout<< "," << pDepthMarketData->HighestPrice;
//    cout<< "," << pDepthMarketData->LowestPrice;
//    cout<< "," << pDepthMarketData->Volume;
//    cout<< endl;

//    simu_bars_manage.updatebar(pDepthMarketData->InstrumentID,pDepthMarketData->LastPrice);

//     string ctpinfo= pDepthMarketData->UpdateTime;
//     ctpinfo+="\t";
//     ctpinfo+=pDepthMarketData->InstrumentID;
//     ctpinfo+="\t";
//     ctpinfo+=wfunction::ftos(pDepthMarketData->LastPrice);
//     this->ui->textBrowser->append(QString::fromStdString(wfunction::joinquote(ctpinfo)));
//     qa->processEvents();
}

void MainWindow::on_pushButton_clicked()
{
    this->show_string_quote("quote button pushed");
    cm->start_ctp_quote();
}

void MainWindow::on_pushButton_2_clicked()
{
    this->show_string_trade("trade button pushed");
    cm->start_ctp_trade();
}

void MainWindow::on_pushButton_3_clicked()
{
    if(cm->is_trade_running())
    {
    emit check_add_order(
        this->ui->fontComboBox->currentText().toStdString(),
        this->ui->comboBox->currentText().toStdString(),
        this->ui->comboBox_2->currentText().toStdString(),
        this->ui->fontComboBox_2->currentText().toStdString(),
        this->ui->fontComboBox_3->currentText().toStdString()
                );
    }
    else
    {
        QMessageBox::information(this,"ERROR","请先开启trade进程");
    }
}
/*
void MainWindow::on_pushButton_4_clicked()
{

}
*/
