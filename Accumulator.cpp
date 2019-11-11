#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_
#include "Accumulator.h"
#include "Account.h"
//构造函数，date为开始累加的日期，value为初始值
Accumulator::Accumulator(Date date, double value,int accountType,double sum) : lastDate(date), value(value), sum(sum) ,accountType(accountType){ }
//构造函数，date为开始累加的日期，value为初始值
Accumulator::Accumulator(Date date, double value,int accountType) : lastDate(date), value(value), sum(0) ,accountType(accountType){ }

//默认构造函数
Accumulator::Accumulator():lastDate(Date(2019,1,1)),value(0),sum(0)
{
}


//获得到日期date的累加结果
double Accumulator::getSum(Date date) 
{
	if (accountType == 0 || ((accountType == 1) && value < 0))
		return sum + value * (date - lastDate);
	else
		return sum;
}

//在date将数值变更为value
void Accumulator::change( Date date, double value)
{
	if (accountType == 0 ||((accountType == 1) && value < 0))//0 TypeSavings 1 TypeCredits
	{
		//cout << accountType << endl;
		sum = getSum(date);
	}
	lastDate = date;
	this->value = value;
}

//初始化，将日期变为date，数值变为value，累加器清零
void Accumulator::reset(Date date, double value)
{
	lastDate = date;
	this->value = value;
	sum = 0;
}
#endif