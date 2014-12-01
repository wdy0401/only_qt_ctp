#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QLabel>

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

    void show_string(const std::string &);
    void set_symbols_display(const std::string &);
    void symbol_price_display(const std::string & , double);

public slots:
    void show_quote_1(CThostFtdcDepthMarketDataField *pDepthMarketData);
    void show_quote_label(CThostFtdcDepthMarketDataField *pDepthMarketData);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    bool ctp_is_start;
    std::map<std::string,QLabel *> quote_labels;
};

#endif // MAINWINDOW_H
