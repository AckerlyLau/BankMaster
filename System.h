#ifndef _SYSTEM_H_
#define _SYSTEM_H_
#include <map>
#include <utility>
#include "SavingsAccount.h"
#include "CreditAccount.h"
#include "Account.h"
#include <iostream>
#include <string>
#include "User.h"
using namespace std;
class System
{ 
    private:
       map<string,User *> userData;//user数据
       string DataBaseFile;//存放数据的文件路径
       User * CurrentUser;//当前已登录账户
       Date Today;//今天的日期
    public:
        System();
		~System();
		//查找用户 按照username查找用户
        bool FindUser(string username,User *&usr);
        //登录
        void Login(string username,string password);
        //登陆的UI界面
		void CMDLogin();
		//登出
        void Logout();
        //添加账户
        bool AddUser(string username,User *user);
		//创建帐户
        void CreateAccount(Date date,string id,double rate,double credit,double annualFee);
		//创建账户的UI
        void CMDCreateAccount(); 
        //查找账户 按照id查找账户，赋给acc指针的引用
        bool FindAccount(string id,Account *&acc);
		//添加账户 将acc指向账户对象添加到map中
		void AddAccount(string id, Account* acc);
		//创建账户
		void CreatAccount(Date date, string id, double rate, double credit, double annualFee);
		//选择并使用账户
		void UseAccount(string id);
		//注册 创建帐户
        void Register(string username,string password);
		//注册界面UI
        void CMDRegister();
		//输入密码时替换为*
        string InputPasswd();
		//选择账户界面的UI
        void CMDUseAccount();
        //保存数据，在析构函数中调用
        void SaveData();
        //初始化读取数据，在构造函数中调用
		bool ReadFile();
        //输出欢迎界面，循环调用MainLoop
        void Start();
        //UI界面和Mainloop
        void UIStart(int argc,char *argv[]);
		//分级展示菜单
        void ShowMenu(bool showDetail);
		//MainLoop，处理用户交互，循环执行
		bool MainLoop();
		//帮助菜单
        void HelpMe(string cmd);
};
#endif
