#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "System.h"
#include "CreateAccountDialog.h"
#include "RegisterDialog.h"
#include "QListWidget"

MainWindow::MainWindow(System *oss ,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,os(oss)
{
    ui->setupUi(this);
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


