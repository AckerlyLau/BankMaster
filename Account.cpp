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
using namespace std;
const int TypeCredit = 1;
const int TypeSavings = 0;

//构造函数
Account::Account(Date date,string id,double rate,int accountType,string OwnerUsername,double balance ,double accumulation,multimap <Date,LogInfo> log)
{
	lastDate = date;
	this -> id = id;
	this -> rate = rate;
	this -> balance = balance;
	this -> accumulation = accumulation;
	this -> accountType = accountType;
	this -> OwnerUsername = OwnerUsername;
	Log = log;
}
//构造函数 
Account::Account(Date date,string id,double rate,int accountType,string OwnerUsername)
{
	lastDate = date;
	this -> id = id;
	this -> rate = rate;
	balance = 0;
	accumulation = 0;
	this -> accountType = accountType;
	this -> OwnerUsername = OwnerUsername;
}	

//默认构造函数 
Account::Account()
{
	lastDate = Date(2019,1,1);
	this -> id = "0";
	this -> rate = 0;
	balance = 0;
	accumulation = 0;
	accountType = TypeSavings;
	OwnerUsername = "NULL";
}	

//亚默认构造函数
Account::Account(int accountType)
{
	lastDate = Date(2019,1,1);
	this -> id = "0";
	this -> rate = 0;
	balance = 0;
	accumulation = 0;
	this -> accountType = accountType;
}	

//进行账户变动
void Account::record(Date date,double amount,string detail)
{
	//cout <<"Debug:Account::record" <<endl;
	//累计已有存款的利息 
	accumulate(date);
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
void Account::DateUpdate(Date date)
{
	if (date < getLastDate())
		throw AccountException("日期时间错误，无法时光倒流", this);
	//cout <<"Debug:DataUpdate " <<lastDate << date << endl;
	for (Date i = lastDate;i < date + 1; i = i + 1)
	{
		settle(i);
		//cout << i << endl;
	}
}
//上次操作日期
Date Account::getLastDate()
{
	return lastDate;
}

//获取账户类型
int Account::getAccountType()
{
	return accountType;
}
double Account::getAccumulation()
{
	return accumulation;
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
	LogInfo log(date,amount,detail);
	Log.insert(make_pair(date,log));
	//cout <<"Debug:Account::AddLog finished"<<endl;
}


//某个月按时间排序的账户信息
void Account::ShowLogTime(Date date)
{
	cout << date.getYear() << " 年 " << date.getMonth() << " 月 的账户日志如下:" << endl;
	for(map<Date,LogInfo>::iterator it  = Log.lower_bound(date);it != Log.upper_bound(Date(date.getYear(),date.getMonth(),31));it ++)
	{
		cout << "时间: " <<it -> second.getDate().TransferToString() <<" 变动: "<<it -> second.getAmount() <<" 备注:" << it->second.getDetail() <<endl;
	}
}	

bool cmp(LogInfo &L1,LogInfo &L2)
{
	return L1.getAmount() > L2.getAmount();
}

//某个月按照交易金额从小到大排序的账户查询信息
void Account::ShowLogAmount(Date date)
{
	cout << date.getYear() << " 年 " << date.getMonth() << " 月 的账户日志如下:" << endl;
	
	vector<LogInfo> temp;
	for(multimap<Date,LogInfo>::iterator it  = Log.lower_bound(date);it != Log.upper_bound(Date(date.getYear(),date.getMonth(),31));it ++)
	{
		temp.push_back(it->second);
	}

	sort(temp.begin(),temp.end(),cmp);
	for(vector<LogInfo>::iterator it  = temp.begin();it != temp.end();it ++)
	{
		cout << "时间: " <<it ->getDate().TransferToString() <<" 变动: "<<it -> getAmount() <<" 备注:" << it->getDetail() <<endl;
	}
}


 

