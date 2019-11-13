#ifndef _SAVINGSACCOUNT_H_
#define _SAVINGSACCOUNT_H_
#include "Date.h" 
#include "Account.h"
#include <string>
/***********************************
SavingsAccount.h
SavingAccount类的声明 
***********************************/ 
using namespace std;
//SavingAccount类 
class SavingsAccount : public Account
{
	public:
		//构造函数 
        SavingsAccount(Date date,string id,double rate,string OwnerUsername,double balance,Date accumulationDate,double accumulationValue,double accumulationSum,multimap<Date,LogInfo> log,LogMaster *logmgr);
        SavingsAccount(Date date,string id,double rate,string OnwerUsername,LogMaster *logmgr);
		SavingsAccount();
		

		//取款，重载
		void withdraw(Date date,double amount);
		//结算利息
		void settle(Date date);

		//展示账户信息 
		void show();

		//存款
        void deposit(Date date,double amount);	


};
#endif

