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
		SavingsAccount(Date date,string id,double rate,string OwnerUsername,double balance,double accumulation,multimap<Date,LogInfo> log);
		SavingsAccount(Date date,string id,double rate,string OnwerUsername);
		SavingsAccount();
		
		//累计利息
		void accumulate(Date date); 

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

