#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include<QApplication>
#include<QLabel>
#include<QMessageBox>

#include<string>
#include<map>
#include"../ctp/ThostFtdcMdApi.h"
class ctp_manager;

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
    void set_seperate_label();
    void set_symbols_display(const std::string &);

    void show_string_quote(const std::string &);
    void show_string_trade(const std::string &);
    void symbol_price_display(const std::string & , double);

    void set_ctp_manager(ctp_manager * p){cm=p;}
    void set_qa(QApplication * p){qa=p;}

signals:
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
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
    std::map<std::string,QLabel *> quote_labels;
    ctp_manager * cm;
    QApplication * qa;
};

#endif // MAINWINDOW_H
