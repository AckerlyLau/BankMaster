#ifndef _LOGINFO_H_
#define _LOGINFO_H_
#include <string>
#include "Date.h"
#include <iostream>
class LogInfo
{
    private:
        Date date;
        double amount;
        string detail;
    public:
        LogInfo();
        LogInfo(Date date,double amount,string detail);
        string getDetail();
        double getAmount();
        Date getDate();
        
        //重载小于号，排序用
        bool operator<(LogInfo &log);

};
#endif