#include <iostream>
#include "Account.h"
#include "LogMaster.h"
#include <QMainWindow>
#include "Date.h"
#include "Account.h"
#include <utility>
#include "LogInfo.h"
#include <map>
#include "mainwindow.h"
#include "ui_mainwindow.h"
namespace Ui { class MainWindow; }
using namespace std;

LogMaster::LogMaster(Ui::MainWindow *ui)
{
    this -> ui = ui;
}
void LogMaster::AddLog(multimap<Date,LogInfo> &log,Date date,double amount,string detail,string accid)
{
    LogInfo lo(date,amount,detail);
    log.insert(make_pair(date,lo));
    string text ="账户：" +  accid +  " 时间：" + date.TransferToString() + " 变动：" +to_string(amount) + " 备注：" + detail;
    ui->LogTextBrowser->append(text.c_str());
}

