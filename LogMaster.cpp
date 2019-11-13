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
#include "QWidget"
#include "QMessageBox"
namespace Ui { class MainWindow; }
using namespace std;

LogMaster::LogMaster(Ui::MainWindow *ui)
{
    this -> ui = ui;
}
void LogMaster::PrintLog(string text,Qt::GlobalColor color)
{
    ui->LogTextBrowser->append(text.c_str());
    QTextCursor cursor = ui->LogTextBrowser->textCursor();
    cursor.select(QTextCursor::LineUnderCursor);   //选中要着色的内容
    QTextCharFormat fmt;
    fmt.setForeground(color);
    cursor.mergeCharFormat(fmt);    //设置文本格式
    cursor.clearSelection(); //撤销选中
    cursor.movePosition(QTextCursor::EndOfLine);  //cursor和anchor均移至末尾


}
void LogMaster::AddLog(multimap<Date,LogInfo> &log,Date date,double amount,string detail,string accid)
{
    LogInfo lo(date,amount,detail);
    log.insert(make_pair(date,lo));
    string balance = to_string(amount);
    balance = balance.substr(0,balance.find('.')+3);
    string text ="账户：" +  accid +  " 时间：" + date.TransferToString() + " 变动：" +balance + " 备注：" + detail;
    PrintLog(text,Qt::black);

}
void LogMaster::AddLog(QWidget *parent,const QString &title,const QString &text,string type,bool ShowWindow,bool AddLogInfo)
{
    string s;
    Qt::GlobalColor color = Qt::green;
    if(ShowWindow == true)
    {
        if(type =="warning")
        {
            s = "错误";
            color = Qt::red;
            QMessageBox::warning(parent,title,text);
        }
        else
        {
            s = "消息";
            QMessageBox::information(parent,title,text);
        }
    }
    if(AddLogInfo == true)
    {
        string txt = title.toStdString()  +s + " : " + text.toStdString();
        PrintLog(txt,color);
    }
}

void LogMaster::AddLog(string str,bool Warning)
{
    if(Warning == true)
    {
        PrintLog(str.c_str(),Qt::red);
    }
    else
    {
        PrintLog(str.c_str());
    }
}
void LogMaster::AddLog(string str,Qt::GlobalColor color)
{
    PrintLog(str.c_str(),color);
}


