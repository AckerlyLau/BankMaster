#ifndef LOGMASTER_H
#define LOGMASTER_H
#include <QMainWindow>
#include "Date.h"
#include <utility>
#include "LogInfo.h"
#include <map>
namespace Ui { class MainWindow; }
class LogMaster
{
public:
    Ui::MainWindow *ui;
public:
    LogMaster(Ui::MainWindow *ui);
    void AddLog(multimap<Date,LogInfo> &log,Date date,double amount,string detail,string accid);
};

#endif // LOGMASTER_H
