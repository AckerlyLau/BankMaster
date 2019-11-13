#ifndef LOGMASTER_H
#define LOGMASTER_H
#include <QMainWindow>
#include "Date.h"
#include <utility>
#include "LogInfo.h"
#include <map>
#include "QWidget"
namespace Ui { class MainWindow; }
class LogMaster
{
public:
    Ui::MainWindow *ui;
public:
    LogMaster(Ui::MainWindow *ui);
    void AddLog(multimap<Date,LogInfo> &log,Date date,double amount,string detail,string accid);
    void AddLog(QWidget *parent,const QString &title,const QString &text,string type,bool ShowWindow = 1,bool AddLogInfo = 1);
    void PrintLog(string text,Qt::GlobalColor color = Qt::black);
    void AddLog(string str,bool Warning = false);
    void AddLog(string str,Qt::GlobalColor color );
};

#endif // LOGMASTER_H
