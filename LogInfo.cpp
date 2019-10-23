#include "Date.h"
#include <string>
#include "LogInfo.h"
#include <iostream>
#include <cmath> 
using namespace std;

LogInfo::LogInfo()
{
    date = Date(2019,1,1);
    amount = 0;
    detail = "";
}
LogInfo::LogInfo(Date date,double amount,string detail)
{
    this -> date = date;
    this -> amount = amount;
    this -> detail = detail;
}
string LogInfo::getDetail()
{
    return detail;
}
double LogInfo::getAmount()
{
    return amount;
}
Date LogInfo::getDate()
{
    return date;
}
bool LogInfo::operator<(LogInfo &log)
{
    return abs(this -> getAmount()) > abs(log.getAmount()); 
}

