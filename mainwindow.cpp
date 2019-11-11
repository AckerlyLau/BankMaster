#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "System.h"
#include "CreateAccountDialog.h"
#include "RegisterDialog.h"
MainWindow::MainWindow(System *oss ,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,os(oss)
{
    ui->setupUi(this);

    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setColumnCount(3);
    QStringList header;
    ui->tableWidget->horizontalHeader()->setSectionsClickable(false);
    header<<tr("ID")<<tr("账户类型")<<tr("余额");
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setSelectionBehavior ( QAbstractItemView::SelectRows ); //设置选择行为，以行为单位
    ui->tableWidget->setSelectionMode ( QAbstractItemView::SingleSelection ); //设置选择模式，选择单行
    ui->tableWidget->setItem(0,0,new QTableWidgetItem("1"));
    ui->tableWidget->setItem(1,0,new QTableWidgetItem("2"));
    //ui->tableWidget->tableHeader<<"ID"<<"账户类型"<<"";
    //ui->tableWidget->
}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::on_actionNewAccount_triggered()
{
    CreateAccountDialog newAcc(os);
    newAcc.exec();
}

void MainWindow::on_actionRegister_R_triggered()
{
    RegisterDialog rsg(os);
    rsg.exec();
}
