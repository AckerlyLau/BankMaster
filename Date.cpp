#include "Date.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace std;

const int YYYY_MM_DD = 1;
const int YYYYMMDD = 2;
const int YYYYnMMyDDr = 3;
Date::Date()
{
    setDate(2019,1,1);
}
Date::Date(int year, int month, int day)
{
    setDate(year, month, day);
}
Date::Date(string str)
{
    int sum = 0;
    for(sum = 0;str.find("-")!= str.npos;sum++)
        str.replace(str.find("-"),1," ");
    stringstream ss;
    ss << str;
    int year ,month,day;
    ss >> year >> month >> day;
    string sss;
    ss >> sss;
    if(sss.size() != 0 || year == 0 || month == 0 || day == 0 || sum != 2)
        throw runtime_error("日期输入有误");
    setDate(year,month,day);
}
/*
Date::Date(Date &date)
{
    this->day = date.day;
    this->year = date.year;
    this->month = date.month;
}
*/
int Date::getYear() const
{
    return year;
}
int Date::getMonth()const
{
    return month;
}
int Date::getDay()const
{
    return day;
}
void Date::setDate(int year, int month, int day)
{
    setYear(year);
    setMonth(month);
    setDay(day);
}
void Date::setYear(int year)
{
    this->year = year;
}
void Date::setMonth(int month)
{
    this->month = month;
}
void Date::setDay(int day)
{
    this->day = day;
}


void Date::showDate(int style)
{
    switch (style)
    {
    case YYYY_MM_DD:
        cout << getYear() << "-" << getMonth() << "-" << getDay();
        break;
    case YYYYMMDD:
        cout << getYear();
        if (getMonth() < 10)
            cout << "0";
        cout << getMonth();
        if (getDay() < 10)
            cout << "0";
        cout << getDay();
        break;
    case YYYYnMMyDDr:
        cout << getYear() << "年" << getMonth() << "月" << getDay() << "日";
        break;
    default:
        cout << getYear() << "-" << getMonth() << "-" << getDay();
        break;
    }
}

string Date::TransferToString(int style)
{
    stringstream ss;
    switch (style)
    {
    case YYYY_MM_DD:
        ss << getYear() << "-" << getMonth() << "-" << getDay();
        break;
    case YYYYMMDD:
        ss << getYear();
        if (getMonth() < 10)
            cout << "0";
        ss << getMonth();
        if (getDay() < 10)
            cout << "0";
        ss << getDay();
        break;
    case YYYYnMMyDDr:
        ss << getYear() << "年" << getMonth() << "月" << getDay() << "日";
        break;
    default:
        ss << getYear() << "-" << getMonth() << "-" << getDay();
        break;
    }
    return ss.str();
}
//重载 < 运算符
/*
bool Date::operator<(Date &dat)
{
    if(getYear() < dat.getYear())
        return true;
    else if(getYear() > dat.getYear())
        return false;
    else if(getMonth() < dat.getMonth())
        return true;
    else if(getMonth() > dat.getMonth())
        return false;
    else if(getDay() < dat.getDay())
        return true;
    else 
        return false;
}*/
bool operator<(const Date &dat1,const Date &dat2)
{
    if(dat1.getYear() < dat2.getYear())
        return true;
    else if(dat1.getYear() > dat2.getYear())
        return false;
    else if(dat1.getMonth() < dat2.getMonth())
        return true;
    else if(dat1.getMonth() > dat2.getMonth())
        return false;
    else if(dat1.getDay() < dat2.getDay())
        return true;
    else 
        return false;
}

//返回dat - this年 的天数
int Date::operator-( Date &dat)
{
    /*
    //                        1  2  3  4  5  6  7  8  9 10 11 12
    int DaysInMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int days = 0;
    int EarlierMonth = getMonth() > dat.getMonth() ? dat.getMonth() : getMonth();
    int LaterMonth = getMonth() <= dat.getMonth() ? dat.getMonth() : getMonth();
    int EarlierDay = getMonth() > dat.getMonth() ? dat.getDay() : getDay();
    int LaterDay = getMonth() <= dat.getMonth() ? dat.getDay() : getDay();

    for (int i = EarlierMonth; i < LaterMonth; i++)
        days += DaysInMonth[i];
    days -= EarlierDay;
    days += LaterDay;

    days = getMonth() > dat.getMonth() ? days : -days;

   // cout << "1:" << days << endl;

    days += ( getYear() - dat.getYear()) * 365;

 //   cout << "2:" << days << endl;

    int EarlierYear = getYear() > dat.getYear() ? dat.getYear() : getYear();
    int LaterYear = getYear() <= dat.getYear() ? dat.getYear() : getYear();
    int CountOfLeap = 0;
    for (int i = EarlierYear + 1; i < LaterYear; i++)
        if (i % 4 == 0 && i % 100 != 0 || i % 400 == 0)
            CountOfLeap++;
    if (getYear() % 4 == 0 && getYear() || getYear() % 400 == 0)
    {
        if (getMonth() <= 2 && getYear() < dat.getYear())
            CountOfLeap++;
        if (getMonth() > 2 && getYear() > dat.getYear())
            CountOfLeap++;
    }
    if (dat.getYear() % 4 == 0 && dat.getYear() || dat.getYear() % 400 == 0)
    {
        if (dat.getMonth() > 2 && getYear() < dat.getYear())
            CountOfLeap++;
        if (dat.getMonth() <= 2 && getYear() > dat.getYear())
            CountOfLeap++;
    }
    if (getYear() < dat.getYear())
        days -= CountOfLeap;
    else
        days += CountOfLeap;
    
  //  cout <<"3:" << days << endl;
    return days;
    */


   //                        1  2  3  4  5  6  7  8  9 10 11 12
    int DaysInMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int days = 0;
    int mdays = 0;
    int leap = 0;
    int ydays = 0;
    Date* EarlierYear;
    Date* LaterYear;
    if(dat < *this)
    {
        EarlierYear = &dat;
        LaterYear = this;
    }
    else
    {
       EarlierYear = this;
       LaterYear = &dat;
    }

    ydays = (LaterYear -> getYear() - EarlierYear -> getYear())*365;
    int EarlierMonth,LaterMonth;
    int EarlierMonthDay,LaterMonthDay;
    if(LaterYear -> getMonth() >= EarlierYear -> getMonth())
    {
        EarlierMonth = EarlierYear -> getMonth();
        LaterMonth = LaterYear -> getMonth();
        EarlierMonthDay = EarlierYear -> getDay();
        LaterMonthDay = LaterYear -> getDay();
    }
    else 
    {
        EarlierMonth = LaterYear -> getMonth();
        LaterMonth = EarlierYear -> getMonth();
        EarlierMonthDay = LaterYear -> getDay();
        LaterMonthDay = EarlierYear -> getDay();
    }
    for(int i = EarlierMonth; i < LaterMonth;i++)
    {
        mdays += DaysInMonth[i];
    }

    //cout << EarlierMonth <<" " <<LaterMonth << endl;
    
    mdays += LaterMonthDay - EarlierMonthDay;
    if(LaterYear -> getMonth() < EarlierYear -> getMonth())
        mdays = -mdays;
    for(int i = EarlierYear -> getYear() + 1;i< LaterYear -> getYear();i++)
    {
        if(((i % 4 == 0 )&& (i % 100 != 0)) || (i%400==0))
            leap ++;
    }
    if( (EarlierYear -> getYear() % 4 == 0 ) && (EarlierYear -> getYear() % 100 != 0) || (EarlierYear -> getYear() % 400 == 0) )
        if(EarlierYear -> getMonth() <= 2)
            leap ++;
    if( (LaterYear -> getYear() % 4 == 0 ) && (LaterYear -> getYear() % 100 != 0) || (LaterYear -> getYear() % 400 == 0) )
        if(LaterYear -> getMonth() > 2)
            leap ++;     
    
    //showDate(YYYY_MM_DD);
    //cout <<" - ";
    //dat.showDate(YYYY_MM_DD) ;
    //cout <<endl;
    
    days = leap + mdays + ydays;
    
    //cout << days <<" " << mdays <<" " << ydays << " "<< leap<<endl;
    
    if(*this < dat)
        days = -days;
    
    return days;
}

//重载>>运算符
istream &operator>>(istream &in,Date &date)
{
    string str;
    in >> str;
    int sum = 0;
    for(sum = 0;str.find("-")!= str.npos;sum++)
        str.replace(str.find("-"),1," ");
    stringstream ss;
    ss << str;
    int year ,month,day;
    ss >> year >> month >> day;
    string sss;
    ss >> sss;
    if(sss.size() != 0 || year == 0 || month == 0 || day == 0 || sum != 2)
        throw runtime_error("日期输入有误");
    date.setDate(year,month,day);
    return in;
}

//重载<<运算符
ostream &operator<<(ostream &out,Date &date)
{
    out << date.getYear() <<"-" <<date.getMonth() <<"-" << date.getDay();
    return out;
}
//重载加号
Date Date::operator+( int a)
{
	//                1  2  3  4  5  6  7  8  9 10 11 12
	int mp[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	int mr[13] = { 0,31,29,31,30,31,30,31,31,30,31,30,31 };
    int *m;
    Date d = *this;
    //Date *d =new Date(this->getYear(),this->getMonth(),this->getMonth());
    //*d = *this;
	int b = a;
	while (b > 0)
	{
        if (d.year % 4 == 0 && d.year % 100 != 0 || d.year % 400 == 0)
			m = mr;
		else
			m = mp;
        if (d.day + b > m[d.month])
		{
            b = b - m[d.month] + d.day -1;
            d.day = 1;
            if (d.month >= 12)
			{
                d.year++;
                d.month = 1;
			}
			else
			{
                d.month++;
			}
		}
		else
		{
            d.day += b;
			b = 0;
		}
	}
    return d;
}

/*
void Date::operator=(const Date *&D )
{
    this->day = D->getDay();
    this->year = D->getYear();
    this->month = D->getMonth();
    delete D;
}
void Date::operator=(const Date &D )
{
    this->day = D.getDay();
    this->year = D.getYear();
    this->month = D.getMonth();
}
*/
/*
ofstream &operator<<(ofstream &out,Date &date)
{
    *os << date.getYear;
   //return ofs;
    //static_cast<ostream&>(out) << value;
     out << to_string(date.getYear()) <<"-" <<date.getMonth() <<"-" << date.getDay();
    return out;
}
*/
