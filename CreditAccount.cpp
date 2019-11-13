#include "Account.h" 
#include "CreditAccount.h"
#include "Date.h"
#include <iostream>
#include <iomanip>
#include <math.h>
#include "AccountException.h"
#include <stdio.h>
using namespace std; 

//构造函数
CreditAccount::CreditAccount(Date date,string id,double rate,double credits,double annualFee,string OwnerUsername ,double balance, Date accumulationDate, double accumulationValue, double accumulationSum,multimap<Date,LogInfo> log,LogMaster *logmgr):Account(date,id,rate,TypeCredit,OwnerUsername,balance, accumulationDate, accumulationValue, accumulationSum,log,logmgr)
{
    this -> credits = credits;
    this -> annualFee = annualFee;
}
CreditAccount::CreditAccount(Date date,string id,double rate,double credits,double annualFee,string OwnerUsername,LogMaster *logmgr):Account(date,id,rate,TypeCredit,OwnerUsername,logmgr)
{
    this -> credits = credits;
    this -> annualFee = annualFee;
}
CreditAccount::CreditAccount():Account(TypeCredit)
{
	annualFee = 0;
	credits = 0;
}

//信用额度
double CreditAccount::getCredits()
{
	return credits;
}
//年费
double CreditAccount::getAnnualFee()
{
	return annualFee;
}



//结算利息 
void CreditAccount::settle(Date date)
{
	//cout << "Debug::settle被调用" << endl;
	if(date.getMonth() == 1 && date.getDay() == 1 && getLastRecordedDate().getYear() != date.getYear())
    {
        //扣除年费,每年1月1日
		DateUpdating(date);
		record(date,-annualFee,"扣除年费");
    }
	if(date.getDay() == 1)
	{
		double amount = accumulation.getSum(date) * getRate();
		DateUpdating(date);
		record(date,amount,"欠款利息结算");
		accumulation.reset(date, getBalance());
	}
}


//取款，重载 
 void CreditAccount::withdraw(Date date,double amount)
{
	if(amount < 0)
		throw AccountException("取款金额不能为负",this);
	if(date < getLastRecordedDate())
		throw AccountException("日期时间错误，无法时光倒流.",this);
	if(amount <= balance + credits)
	{
		//cout <<"heiheihei"<<endl;
		//处理余额变动
		record(date,-amount,"取款");
		accumulation.change(date, getBalance());
	}
	else
		throw AccountException("取款超出信用额度限制,取款失败。",this);
	
} 

//存款 
void CreditAccount::deposit(Date date,double amount)
{
	//cout <<"Debug::CreditAccount::deposit"<<endl;
	if(amount < 0)
		throw AccountException("存款金额不能为负",this);
	if(date < getLastRecordedDate())
		throw AccountException("日期时间错误，无法时光倒流.",this);
	//处理余额变动
	record(date,amount,"存款");
	accumulation.change(date, getBalance());

}


//展示账户信息 
void CreditAccount::show()
{
	//cout <<"#" <<setiosflags(ios::left) << setw(15)<<getId() <<"Balance: " <<getBalance() << endl;
	cout << "******Account Information*****************" <<endl;
	cout <<"** ID:" << getId() <<endl;
	cout <<"** 当前余额:"<< getBalance() <<endl;
	cout <<"** 账户类型：信用账户"<<endl;
	//cout <<"** 余额(利息):"<<settle(date) <<endl; 
	//cout <<"** 总金额:" << getBalance() << endl;
	cout <<"** 日利率:"<<getRate() <<endl;
	cout <<"** 上次操作日期: "<<getLastRecordedDate().TransferToString() <<endl;
	cout <<"***************** End *********************"<<endl;

}

