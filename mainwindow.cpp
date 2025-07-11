#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    RunningProcesses(ui->tableWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
