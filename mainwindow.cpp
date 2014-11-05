#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QString>
#include<string>

#include"../gpp_qt/wfunction/wfunction.h"

using namespace std;

extern QApplication * qa;
extern void start_ctp();

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
