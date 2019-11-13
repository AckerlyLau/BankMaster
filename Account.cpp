#include "Account.h" 
#include "Date.h"
#include <iostream>
#include <iomanip>
#include "AccountException.h"
#include <map>
#include <string>
#include <utility>
#include "LogInfo.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include <QMainWindow>
namespace Ui { class MainWindow; }

using namespace std;
const int TypeCredit = 1;
const int TypeSavings = 0;

//构造函数
Account::Account(Date date, string id, double rate, int accountType, string OwnerUsername, double balance, Date accumulationDate, double accumulationValue, double accumulationSum,  multimap <Date, LogInfo> log,LogMaster *logmgr) : accumulation(accumulationDate,accumulationValue,accumulationSum)
{
    //Ui::MainWindow *uii = logmgr->ui;
	lastRecordedDate = date;
	this -> id = id;
	this -> rate = rate;
	this -> balance = balance;
	this -> accountType = accountType;
	this -> OwnerUsername = OwnerUsername;
    this -> logmgr = logmgr;

	Log = log;

}
//构造函数 
Account::Account(Date date,string id,double rate,int accountType,string OwnerUsername,LogMaster *logmgr):accumulation(date,0,accountType)
{
	lastRecordedDate = date;
	this -> id = id;
	this -> rate = rate;
	balance = 0;
	this -> accountType = accountType;
    this -> logmgr = logmgr;

	this -> OwnerUsername = OwnerUsername;

}	

//默认构造函数 
Account::Account() : accumulation(Date(2019, 1, 1), 0,accountType)
{
	lastRecordedDate = Date(2019,1,1);
	this -> id = "0";
	this -> rate = 0;
	balance = 0;
	accountType = TypeSavings;
    OwnerUsername = "NULL";
    logmgr = nullptr;
}	

//亚默认构造函数
Account::Account(int accountType) : accumulation(Date(2019, 1, 1), 0,accountType)
{
	lastRecordedDate = Date(2019,1,1);
	this -> id = "0";
	this -> rate = 0;
	balance = 0;
	this -> accountType = accountType;
    logmgr = nullptr;
}	

//进行账户变动
void Account::record(Date date,double amount,string detail)
{
	//保留两位小数
	amount = floor(amount * 100 + 0.5) / 100;
	//cout <<"Debug:Account::record mid" <<endl;
	//余额累加 
	//cout << "Debug:" <<balance <<" " << amount << endl;
	balance += amount;
	//cout <<"Debug:Account::record 吼吼吼"<<endl;
	AddLog(date,amount,detail); 
}
//更新日期前判断是否结算
void Account::Process(Date date)
{
	if (date < getLastRecordedDate())
		throw AccountException("日期时间错误，无法时光倒流", this);
    //cout <<"Debug:DataUpdate "  << date << endl;
    //date.setDate((date + 1).getYear(),(date + 1).getMonth(),(date + 1).getDay());
    //cout <<"Debug:DataUpdate2 "  << date << endl;
   // Date dat;
    //dat.setDate(date.getYear(),date.getMonth(),date.getDay());
    //dat.setDate((date + 1).getYear(),(date + 1).getMonth(),(date + 1).getDay());
    date = date + 1;
    for (Date i = getLastRecordedDate()+1;i < date; i = i + 1)
	{
		settle(i);
		//cout << i << endl;
	}
}
//上次操作日期
Date Account::getLastRecordedDate()
{
	return lastRecordedDate;
}

//日期更新 ，即上次操作账户时的信息
void Account::DateUpdating(Date date)
{
	lastRecordedDate = date;
}

//获取账户类型
int Account::getAccountType()
{
	return accountType;
}


string Account::getId()
{
	return id; 
} 
double Account::getBalance()
{
	return balance;
}
double Account::getRate()
{
	return rate;
}

void Account::AddLog(Date date,double amount,string detail)
{
//	cout <<"Debug:Account::AddLog"<<endl;
    logmgr -> AddLog(Log,date,amount,detail,getId());
	//cout <<"Debug:Account::AddLog finished"<<endl;
}


//某个月按时间排序的账户信息
vector<string> Account::ShowLogTime(Date date)
{
    vector<string> res;
    //cout << date.getYear() << " 年 " << date.getMonth() << " 月 的账户日志如下(按time排序):" << endl;
	for(map<Date,LogInfo>::iterator it  = Log.lower_bound(date);it != Log.upper_bound(Date(date.getYear(),date.getMonth(),31));it ++)
	{
        //cout << "时间: " <<it -> second.getDate().TransferToString() <<" 变动: "<<it -> second.getAmount() <<" 备注:" << it->second.getDetail() <<endl;
        cout << "时间: " <<it -> second.getDate().TransferToString() <<" 变动: "<<it -> second.getAmount() <<" 备注:" << it->second.getDetail() <<endl;
        string str;
        string balance = to_string(it->second.getAmount());
        balance = balance.substr(0,balance.find('.')+3);
        str = "时间:"+it->second.getDate().TransferToString()+" 变动:" + balance + "备注: " + it->second.getDetail();
        res.push_back(str);
    }
    return res;
}	

bool cmp(LogInfo &L1,LogInfo &L2)
{
	return abs(L1.getAmount()) < (L2.getAmount());
}

//某个月按照交易金额从小到大排序的账户查询信息
vector<string> Account::ShowLogAmount(Date date)
{
    //cout << date.getYear() << " 年 " << date.getMonth() << " 月 的账户日志如下(按amount排序):" << endl;
    vector<string> res;

	vector<LogInfo> temp;
	for(multimap<Date,LogInfo>::iterator it  = Log.lower_bound(date);it != Log.upper_bound(Date(date.getYear(),date.getMonth(),31));it ++)
	{
		temp.push_back(it->second);
	}

	sort(temp.begin(),temp.end(),cmp);
	for(vector<LogInfo>::iterator it  = temp.begin();it != temp.end();it ++)
	{
        //cout << "时间: " <<it ->getDate().TransferToString() <<" 变动: "<<it -> getAmount() <<" 备注:" << it->getDetail() <<endl;
        string str;
        string balance = to_string(it->getAmount());
        balance = balance.substr(0,balance.find('.')+3);
        str = "时间:" + it->getDate().TransferToString() +"变动: " + balance + " 备注:" + it->getDetail() ;
        res.push_back(str);
    }
    return res;
}


 

