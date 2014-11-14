#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<string>
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

public slots:
    void show_quote_1(CThostFtdcDepthMarketDataField *pDepthMarketData);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    bool ctp_is_start;
};

#endif // MAINWINDOW_H
