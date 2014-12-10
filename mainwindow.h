#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QLabel>
#include<QMessageBox>

#include<string>
#include<map>
#include"../ctp/ThostFtdcMdApi.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void init();
    void set_order_send(const std::string &);
    void show_string(const std::string &);
    void show_string_trade(const std::string &);
    void set_symbols_display(const std::string &);
    void symbol_price_display(const std::string & , double);

signals:
    void on_pushButton_4_clicked();
    void check_add_order(const std::string &,const std::string &,const std::string &,const std::string &,const std::string &);

public slots:
    void show_quote_1(CThostFtdcDepthMarketDataField *pDepthMarketData);
    void show_quote_label(CThostFtdcDepthMarketDataField *pDepthMarketData);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
	Ui::MainWindow *ui;
	bool ctp_quote_running;
	bool ctp_trade_running;
    std::map<std::string,QLabel *> quote_labels;
};

#endif // MAINWINDOW_H
