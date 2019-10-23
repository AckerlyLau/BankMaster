#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_
#include "Date.h"
#include <string>
#include <map>
#include "LogInfo.h"
#include <utility>
/***********************************
Account.h
Account类的声明 
***********************************/ 
using namespace std; 
extern const int TypeCredit;
extern const int TypeSavings;
//Account类 
class Account
{
	protected:
		string id;
		double balance;
		double rate;
		Date lastDate;
		double accumulation;
		int accountType;
		multimap<Date,LogInfo> Log;
		string OwnerUsername;
	public:
		friend class System;
		friend class User;
		//构造函数
		Account(Date date,string id,double rate,int accountType,string OwnerUsername,double balance ,double accumulation,multimap<Date,LogInfo> log); 
		Account(Date date,string id,double rate,int accountType,string OwnerUsername);
		Account();
		Account(int accountType);
		
		//进行账户变动
		void record(Date date,double amount,string detail);
		
		//帐户类型
		int getAccountType();
		
		//利息累计 
		virtual void accumulate(Date date)  = 0 ;

		//上次操作日期
		Date getLastDate();
		
		//获取利息累计信息
		double getAccumulation();

		//获取账户id 
		string getId();
		
		//更新日期，并且决定结算
		void DateUpdate(Date date);

		//获取余额 
		double getBalance();

		//获取利率 
		double getRate();
		
		//展示账户信息
		virtual void show()=0;
		
		//存款 
		virtual void deposit(Date date,double amount) = 0;
		
		//取款 
		virtual void withdraw(Date date,double amount) = 0;
		
		//结算利息 
		virtual void settle(Date date) = 0;
		
		//添加日志
		void AddLog(Date date,double amount,string detail);
		
		//某个月按时间排序的账户信息
		void ShowLogTime(Date date);

		//某个月按照交易金额从小到大排序的账户查询信息
		void ShowLogAmount(Date date);	
};
#endif