#ifndef _ACCUMULATOR_H_
#define _ACCUMULATOR_H_
#include "Date.h"

class Accumulator {	//将某个数值按日累加
private:
	Date lastDate;	//上次变更数值的时期
	double value;	//数值的当前值
	double sum;		//数值按日累加之和
	int accountType;
public:
	friend class System;
	//构造函数，date为开始累加的日期，value为初始值
	Accumulator(Date date, double value,int accountType);
	//构造函数，date为上次累加日期，value为初始值,sum为累加值
	Accumulator(Date date, double value,int accountType,double sum);

	//默认构造函数
	Accumulator();

	//获得到日期date的累加结果
	double getSum(Date date);


	//在date将数值变更为value
	void change(Date date, double value);

	//初始化，将日期变为date，数值变为value，累加器清零
	void reset(Date date, double value);
};

#endif //__ACCUMULATOR_H__