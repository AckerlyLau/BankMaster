#ifndef _DATE_H_
#define _DATE_H_
#include <iostream>

using namespace std;
extern const int YYYY_MM_DD; //日期格式YYYY-MM-DD
extern const int YYYYMMDD;   //日期格式YYYY-MM-DD
extern const int YYYYnMMyDDr;//日期格式YYYY年MM月DD日
class Date 
{
    private:
        int year;                 //年
        int month;                //月
        int day;                  //日
    public:
        Date();//默认构造函数
        Date(int year,int month,int day);//构造函数年月日
       // Date(Date &date);
        int getYear()const;//返回year
        int getMonth()const;//返回month
        int getDay()const;//返回day

        void setDate(int year,int month,int day);//给year,month,day赋值
        void setYear(int year);//给year赋值
        void setMonth(int month );//给month赋值
        void setDay(int day); //给day赋值
        void showDate(int style = YYYY_MM_DD);//显示日期，默认为YYYY-MM-DD格式输出
        string TransferToString(int style = YYYY_MM_DD);//将日期转换为string字符串返回
        int operator-( Date &dat) ;//两日期相减，返回两个日期相距天数
        Date operator+(int a);
        //void operator=(const Date *&D );
        //void operator=(const Date &D );
};

bool operator<(const Date &dat1,const Date &dat2);//重载<运算符，比较大小
istream &operator>>(istream &in,Date &date);//重载>>运算符，允许直接以YY YY-MM-DD方式输入日期
ostream &operator<<(ostream &out,Date &date);//可以直接输出日期，格式为YYYY-MM-DD


#endif
