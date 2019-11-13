#include <map>
#include "User.h"
#include "Account.h"
#include "CreditAccount.h"
#include "SavingsAccount.h"
#include <string>
#include <utility>
#include <iostream>
#include "UserException.h"
#include <map>
#include <utility>
#include "Date.h"
#include "LogInfo.h"
#include <vector>
using namespace std;

User::User()
{
    CurrentAccount = nullptr;
    logmgr = nullptr;
}

User::User(string username,string password,LogMaster *logmgr)
{
    this -> username = username;
    this -> password = password;
    CurrentAccount = nullptr;
    this -> logmgr = logmgr;
}
string User::getUsername()
{
   return username;
}

string User::getPassword()
{
    return password;
}

bool User::LoginCheck(string username,string password)
{
    if(username == this -> username && password == this -> password)
        return true;
    else 
        return false;  
}

void User::AddAccount(string id,Account *acc)
{
	if(userAccount.count(id) == 0)
	{
		userAccount.insert(make_pair(id,acc));
	}
    else
        throw UserException("账户ID已被使用，添加账户失败。",this);
}

void User::CreatAccount(Date date,string id,double rate,double credit,double annualFee)
{
    Account *acc;
    if(credit < 0)
    {
        acc = new SavingsAccount(date,id,rate,this->getUsername(),logmgr);
    } 
    else
    {
        acc = new CreditAccount(date,id,rate,credit,annualFee,this->getUsername(),logmgr);
    }
    //userData.insert(make_pair(id,user));
    AddAccount(id,acc);
}

bool User::FindAccount(string id,Account *& acc)
{
    if(userAccount.count(id)>0)
    {
        acc = userAccount.find(id) -> second;
        return true;
    }
    else 
        return false;
}
bool User::isAccountSelected()
{
    if(CurrentAccount == nullptr)
        return false;
    else
        return true;
    
}

void User::UseAccount(string id)
{
    Account * acc;
    if(FindAccount(id,acc))
    {
        CurrentAccount = acc;
    }
    else
    {
        throw UserException("账户不存在或不属于该用户.",this);
    }
}

void User::AccountLogout()
{
    if(CurrentAccount != nullptr)
        CurrentAccount = nullptr;
    cout << "** 账户登出成功"<<endl;
}

void User::ShowAllAccount()
{
    for(map<string,Account*>::iterator it = userAccount.begin();it != userAccount.end();it++)
    {
        it ->second -> show();
        cout <<"------------------------------------------"<<endl;
    }
}

void User::ShowWarningInfo()
{
    double payoff = 0;
    bool NeedPayOff = false;
    for(map<string,Account*>::iterator it  =  userAccount.begin();it != userAccount.end();it++)
    {

        if(it ->second ->getBalance() < 0)
        {
            if(NeedPayOff == false)
            {
                cout << "---------------------------------------------------------" << endl;
                cout << "****名下全部余额: " << getTotal() << endl;
                cout <<"****待还款："<<endl;
            }
            cout <<"** 账户:" << it -> second ->getId() <<" 待还款额度:" << -it -> second -> getBalance() << endl;
            NeedPayOff = true;
            payoff += it ->second ->getBalance();
        }
    }
    if(NeedPayOff)
    {
        cout <<"****共需还款额度:" << -payoff << endl;
        cout <<"---------------------------------------------------------"<<endl;
    }

    double TotalAmount = 0;
    cout <<"****您的最近收入/支出统计如下："<<endl;
    for(map<string,Account*>::iterator it  =  userAccount.begin();it != userAccount.end();it++)
    {
        double amount = 0;
        for(multimap<Date,LogInfo>::iterator ite = it -> second ->Log.lower_bound(Date(it -> second ->getLastRecordedDate().getYear(),it -> second ->getLastRecordedDate().getMonth(),1));ite != it -> second -> Log.end();ite++)
        {
            amount += ite -> second.getAmount();
        }
        TotalAmount += amount;
        cout << "** 账户: " <<it ->second ->getId() <<" 收支:" << amount << endl;
    }
    cout <<"****近期总收/支:" << TotalAmount << endl;
    cout <<"---------------------------------------------------------"<<endl;

}
vector<string> User::GUIShowWarningInfo()
{
    vector<string> res;
    double payoff = 0;
    bool NeedPayOff = false;
    res.push_back("--------------账户状态提醒----------------------");
    for(map<string,Account*>::iterator it  =  userAccount.begin();it != userAccount.end();it++)
    {

        if(it ->second ->getBalance() < 0)
        {
            if(NeedPayOff == false)
            {
                res.push_back(getUsername() +" 您的信用卡累计待还款账目如下,请记得及时还款");
            }
            string balance = to_string(-it -> second -> getBalance());
            balance = balance.substr(0,balance.find('.')+3);
            res.push_back("** 账户:" + it -> second ->getId() +" 待还款额度:" + balance);
            NeedPayOff = true;
            payoff += it ->second ->getBalance();
        }
    }
    if(NeedPayOff)
    {
        string balance = to_string( -payoff);
        balance = balance.substr(0,balance.find('.')+3);
        res.push_back("****共需还款额度:" + balance );
    }
    res.push_back("----------------------------------------------");
    double TotalAmount = 0;
    res.push_back("****您的最近收入/支出统计如下：");
    for(map<string,Account*>::iterator it  =  userAccount.begin();it != userAccount.end();it++)
    {
        double amount = 0;
        for(multimap<Date,LogInfo>::iterator ite = it -> second ->Log.lower_bound(Date(it -> second ->getLastRecordedDate().getYear(),it -> second ->getLastRecordedDate().getMonth(),1));ite != it -> second -> Log.end();ite++)
        {
            amount += ite -> second.getAmount();
        }
        TotalAmount += amount;
        string balance = to_string( amount);
        balance = balance.substr(0,balance.find('.')+3);
        res.push_back( "** 账户: " +it ->second ->getId() +" 收支:" + balance );
    }
    string balance = to_string(TotalAmount);
    balance = balance.substr(0,balance.find('.')+3);
    res.push_back("****近期总收/支:" + balance );
    res.push_back( "--------------提醒结束--------------------------");
    return res;
}

//取款
void User::Deposit(Date date,double amount)
{
    if(CurrentAccount != nullptr)
    {
        //cout <<"Debug:" <<"User::Deposit" <<endl;
        CurrentAccount -> deposit(date,amount);
        cout << "** 存款操作成功,当前余额 " << CurrentAccount -> getBalance() <<endl;
    }
    else
    {
        throw runtime_error("未选择账户，存款失败");
    }
}
//存款
void User::Withdraw(Date date,double amount)
{
    if(CurrentAccount != nullptr)
    {
        CurrentAccount -> withdraw(date,amount);
        cout << "** 取款操作成功,当前余额 " << CurrentAccount -> getBalance() <<endl;
    }
    else
    {
        throw runtime_error("未选择账户，取款失败");
    }
}
double User::getTotal()
{
	double total = 0;
	for (map<string, Account*> ::iterator it = userAccount.begin(); it != userAccount.end(); it++)
	{
		total += it->second->getBalance();
	}
	return total;
}
Account * User::getCurrentAccount()
{
    return CurrentAccount;
}

vector<string>  User::getAllAccountID()
{
    vector<string> vec;
    for(map<string,Account*>::iterator it = userAccount.begin();it != userAccount.end();it ++)
    {
        vec.push_back(it->second->getId());
    }
    return vec;
}
