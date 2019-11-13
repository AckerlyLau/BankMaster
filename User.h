#ifndef _USER_H_
#define _USER_H_
#include <map>
#include "Account.h"
#include "CreditAccount.h"
#include "SavingsAccount.h"
#include <string>
#include <utility>
#include <vector>
#include "LogMaster.h"
using namespace std;
class User
{
    private:
        map<string,Account*> userAccount;//用户账户信息
        Account *CurrentAccount;//当前账户指针
        string username;//用户名
        string password;//密码
        LogMaster *logmgr;

    public:
		//友元
        friend class System;
        //构造函数
		User();
        User(string username,string password,LogMaster *logmgr);
        //获取username
		string getUsername();
        //获取password
		string getPassword();
        //登陆验证
		bool LoginCheck(string username,string password);
        //添加账户
		void AddAccount(string id,Account *acc);
        //创建账户
		void CreatAccount(Date date,string id,double rate,double credit,double annualFee);
        //查找账户，按照id查找
		bool FindAccount(string id,Account *& acc);
        //是否已经选择了账户
		bool isAccountSelected();
		//选择ID为id的账户
        void UseAccount(string id);
		//账户登出
        void AccountLogout();
		//显示所有的用户信息
        void ShowAllAccount();
		//显示警告信息，用于刚登录时显示
        void ShowWarningInfo();
        vector<string> GUIShowWarningInfo();

        //取款
        void Deposit(Date date,double amount);
        //存款
        void Withdraw(Date date,double amount);
        Account * getCurrentAccount();
		//所有账户的的全部存款信息
		double getTotal();
        //所有账户的ID
        vector<string> getAllAccountID();

};
#endif
