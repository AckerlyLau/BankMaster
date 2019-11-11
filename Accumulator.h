#ifndef _ACCUMULATOR_H_
#define _ACCUMULATOR_H_
#include "Date.h"

class Accumulator {	//��ĳ����ֵ�����ۼ�
private:
	Date lastDate;	//�ϴα����ֵ��ʱ��
	double value;	//��ֵ�ĵ�ǰֵ
	double sum;		//��ֵ�����ۼ�֮��
	int accountType;
public:
	friend class System;
	//���캯����dateΪ��ʼ�ۼӵ����ڣ�valueΪ��ʼֵ
	Accumulator(Date date, double value,int accountType);
	//���캯����dateΪ�ϴ��ۼ����ڣ�valueΪ��ʼֵ,sumΪ�ۼ�ֵ
	Accumulator(Date date, double value,int accountType,double sum);

	//Ĭ�Ϲ��캯��
	Accumulator();

	//��õ�����date���ۼӽ��
	double getSum(Date date);


	//��date����ֵ���Ϊvalue
	void change(Date date, double value);

	//��ʼ���������ڱ�Ϊdate����ֵ��Ϊvalue���ۼ�������
	void reset(Date date, double value);
};

#endif //__ACCUMULATOR_H__