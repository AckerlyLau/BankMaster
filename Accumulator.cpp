#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_
#include "Accumulator.h"
#include "Account.h"
//���캯����dateΪ��ʼ�ۼӵ����ڣ�valueΪ��ʼֵ
Accumulator::Accumulator(Date date, double value,int accountType,double sum) : lastDate(date), value(value), sum(sum) ,accountType(accountType){ }
//���캯����dateΪ��ʼ�ۼӵ����ڣ�valueΪ��ʼֵ
Accumulator::Accumulator(Date date, double value,int accountType) : lastDate(date), value(value), sum(0) ,accountType(accountType){ }

//Ĭ�Ϲ��캯��
Accumulator::Accumulator():lastDate(Date(2019,1,1)),value(0),sum(0)
{
}


//��õ�����date���ۼӽ��
double Accumulator::getSum(Date date) 
{
	if (accountType == 0 || ((accountType == 1) && value < 0))
		return sum + value * (date - lastDate);
	else
		return sum;
}

//��date����ֵ���Ϊvalue
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

//��ʼ���������ڱ�Ϊdate����ֵ��Ϊvalue���ۼ�������
void Accumulator::reset(Date date, double value)
{
	lastDate = date;
	this->value = value;
	sum = 0;
}
#endif