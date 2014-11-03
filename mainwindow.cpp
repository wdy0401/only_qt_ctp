#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QString>
#include<string>

using namespace std;

extern QApplication * qa;
extern void start_ctp();
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

