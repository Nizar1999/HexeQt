#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bytes.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionImport_New_File, SIGNAL(triggered(bool)), this, SLOT(importNewFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::importNewFile() {
    Bytes bytesRead;
    if(bytesRead.model != nullptr) {
        ui->tableView->setModel(bytesRead.model); // This is necessary to display the data on table view
        ui->tableView->setShowGrid(false);
        ui->tableView->verticalHeader()->setDefaultAlignment(Qt::AlignHCenter);
        ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);
        //ui->tableView->resizeColumnsToContents();
        //ui->tableView->resizeRowsToContents();
    }
}
