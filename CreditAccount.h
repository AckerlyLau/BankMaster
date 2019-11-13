#ifndef _CREDITACCOUNT_H_
#define _CREDITACCOUNT_H_
#include "Account.h"
#include "Date.h"
#include "LogMaster.h"
class CreditAccount : public Account
{
    private:
        double credits;
        double annualFee;
    public:
        //构造函数
        CreditAccount(Date date,string id,double rate,double credits,double annualFee,string OwnerUsername,double balance, Date accumulationDate, double accumulationValue, double accumulationSum,multimap<Date,LogInfo> log,LogMaster *logmgr);
        CreditAccount(Date date,string id,double rate,double credits,double annualFee,string OwnerUsername,LogMaster *logmgr);
        CreditAccount(); 
    	 
        //取款，重载
        void withdraw(Date,double);

        //信用额度
        double getCredits();

        //年费
        double getAnnualFee();

		//结算利息
		void settle(Date date);

		//展示账户信息 
        void show();	

        //存款
        void deposit(Date date,double amount);


  
};
#endif
