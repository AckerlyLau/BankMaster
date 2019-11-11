#include "SavingsAccount.h"
#include "Date.h"
#include "Account.h"
#include <iostream>
#include <iomanip>
#include <math.h>
#include "AccountException.h"
using namespace std; 
 

//构造函数
SavingsAccount::SavingsAccount(Date date, string id, double rate, string OwnerUsername, double balance, Date accumulationDate, double accumulationValue, double accumulationSum, multimap<Date, LogInfo> log):Account(date,id,rate,TypeSavings,OwnerUsername,balance,accumulationDate,accumulationValue,accumulationSum,log)
{

}
//构造函数 
SavingsAccount::SavingsAccount(Date date,string id,double rate,string OwnerUsername):Account(date,id,rate,TypeSavings,OwnerUsername)
{

}	

//默认构造函数 
SavingsAccount::SavingsAccount():Account(TypeSavings)
{
}	
 
 

//结算利息 
void SavingsAccount::settle(Date date)
{
	//cout << "Debug :: SavingsAccount :: settle" << endl;
	if(date.getMonth() == 1 && date.getDay() == 1)
	{
		DateUpdating(date);
		double amount = accumulation.getSum(date) * getRate() /365;
		record(date,amount,"储蓄利息结算");
		accumulation.reset(date, getBalance());
	}

}

//展示账户信息 
void SavingsAccount::show()
{
	//cout <<"#" <<setiosflags(ios::left) << setw(15)<<getId() <<"Balance: " <<getBalance();
	cout << "******Account Information*****************" <<endl;
	cout <<"** ID:" << getId() <<endl;
	cout <<"** 当前余额:"<< getBalance() <<endl;
	cout << "** 账户类型:储蓄账户" << endl;
	//cout <<"** 余额(利息):"<<settle(date) <<endl; 
	//cout <<"** 总金额:" << getBalance() << endl;
	cout <<"** 年利率:"<<getRate() <<endl;
	cout <<"** 上次操作日期:"<<getLastRecordedDate().TransferToString()<<endl;
	cout <<"***************** End *********************"<<endl;

}



//存款 
void SavingsAccount::deposit(Date date,double amount)
{
	if(amount < 0)
		throw AccountException("存款金额不能为负",this);
	if(date < getLastRecordedDate())
		throw AccountException("日期时间错误，无法时光倒流.",this);
	
	//处理变动
	record(date,amount,"存款");
	accumulation.change(date, getBalance());
}


//取款
void SavingsAccount::withdraw(Date date,double amount)
{
	
	if(amount < 0)
		throw AccountException("取款金额不能为负",this);
	if(date < getLastRecordedDate())
		throw AccountException("日期时间错误，无法时光倒流.",this);
	if(amount <= balance)
	{
		//处理变动
		record(date,-amount,"取款");
		accumulation.change(date, getBalance());
	}
	else
	{
		throw AccountException("取款额度超过账户余额,取款失败。",this);
	}
} 
