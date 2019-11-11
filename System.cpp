#include "System.h"
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "Account.h"
#include "SavingsAccount.h"
#include "CreditAccount.h"
#include "Date.h"
#include <stdexcept>
#include <conio.h>
#include "User.h"
#include <utility>
using namespace std;

System::System()
{
	cout << "System initing......" << endl;
	DataBaseFile = "DataBase.txt";
	CurrentUser = NULL;
	Today = Date(2019,1,1);
	ReadFile();
}
System::~System()
{
	CurrentUser = NULL;
	SaveData();
}

bool System::FindUser(string username, User *&usr)
{
	for (map<string, User *>::iterator it = userData.begin(); it != userData.end(); it++)
	{
		if (it->second->getUsername() == username)
		{
			usr = it->second;
			return true;
		}
	}
	return false;
}
string System::InputPasswd()
{
	char c;
	string str;
	for (int i = 0; (c = _getch()) != 13; )
	{
		if (c != 8)
		{
			cout << "*";
			str += c;
			i++;
		}
		else
		{
			if(i != 0)
			{
				str.erase(i - 1);
				i--;
				cout << "\b \b";
			}
		}
	}
	cout << endl;
	return str;
}
//登录
void System::Login(string username, string password)
{
	User *usr;
	if (FindUser(username, usr))
	{
		if (usr->LoginCheck(username, password))
		{
			CurrentUser = usr;
		}
		else
			throw runtime_error("用户名或密码错误");
	}
	else
		throw runtime_error("用户名不存在");
}

void System::CMDLogin()
{
	string username, password;
	cout <<"******************************"<<endl;
	cout << "**  用户名:";
	cin >> username;
	cout << "**  密码:";
	password = InputPasswd();
	try
	{
		Login(username, password);
		if(CurrentUser != NULL)
		{
			cout << "**  " << CurrentUser->getUsername() << " 已登录." << endl;
			cout <<"******************************"<<endl;
			CurrentUser -> ShowWarningInfo();
		}
	}
	catch (const std::exception &e)
	{
		std::cerr <<"【登陆错误】: "<< e.what() << '\n';
		CMDLogin();
	}
}

//注册
void System::Register(string username, string password)
{
	User *user = new User(username, password);
	if(!AddUser(username, user))
		throw runtime_error("用户名已被使用，注册失败");
}

//注册账户 格式: date(2019 1 1) type(Credit/Saving) id
void System::CMDRegister()
{
	string username;
	string password1;
	string password2;
	cout <<"******************************"<<endl;
	cout << "**  用户名:";
	cin >> username;
	int t = 0;
	do
	{
		if (t > 0)
			cout << "两次密码不匹配，请重新输入" << endl;
		cout << "**  密码:";
		password1 = InputPasswd();
		cout << "**  确认密码:";
		password2 = InputPasswd();
		t++;
	} while (password1 != password2);
	try
	{
		Register(username, password1);
		cout <<"**  "<< username <<" 注册成功"<<endl;
		cout <<"******************************"<<endl;
	}
	catch (const std::exception &e)
	{
		std::cerr <<"【注册错误】: "<< e.what() << '\n';
		CMDRegister();
	}
}

//添加账户
bool System::AddUser(string username, User *user)
{
	if (userData.count(username) == 0)
	{
		userData.insert(make_pair(username, user));
		return true;
	}
	return false;
}

//创建帐户
void System::CreateAccount(Date date, string id, double rate, double credit, double annualFee)
{
	Account *acc;
	if(CurrentUser == NULL)
		throw runtime_error("用户未登录，无法创建帐户");
	if (!FindAccount(id, acc))
		CurrentUser->CreatAccount(date, id, rate, credit, annualFee);
	else
		throw runtime_error("用户名已被占用，添加用户失败。");
}

void System::CMDCreateAccount()
{
	Date date;
	string type;
	string id;
	double rate;
	double credits;
	double annualFee;
	cin >> date >> type >> id >> rate;
	if (type == "Credit")
		cin >> credits >> annualFee;
	else
	{
		credits = -1;
		annualFee = -1;
	}
	try
	{
		CreateAccount(date, id, rate, credits, annualFee);
		cout << "** 账户创建完成" << endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << "【账户创建错误】:"<< e.what() << '\n';
	}
}
//全用户查找Account
bool System::FindAccount(string id, Account *&acc)
{
	for (map<string, User *>::iterator it = userData.begin(); it != userData.end(); it++)
	{
		if (it->second->FindAccount(id, acc))
			return true;
		else
			return false;
	}
	return false;
}

void System::Logout()
{
	if (CurrentUser != NULL)
	{
		CurrentUser->AccountLogout();
		CurrentUser = NULL;
	}
	cout << "** 用户登出成功" << endl;
}

//保存数据
void System::SaveData()
{
	ofstream fout;
	fout.open(DataBaseFile, ios::out);
	if (!fout)
		throw runtime_error("文件打开失败");

	for (map<string, User *>::iterator itu = userData.begin(); itu != userData.end(); itu++)
	{
		fout << "UserStart" << endl;
		fout << "UserInfoStart" << endl;
		fout << "Username= " << itu->second->getUsername() << endl;
		fout << "Password= " << itu->second->getPassword() << endl;
		fout << "UserInfoEnd" << endl;
		fout << "AccountStart" << endl;//账户信息起始标志
		for (map<string, Account *>::iterator it = itu->second->userAccount.begin(); it != itu->second->userAccount.end(); it++)
		{
			if (it->second->getAccountType() == TypeSavings)
			{
				fout << "SavingsAccountStart" << endl; //储蓄账户数据起始标志
				fout << "ID= " << it->second->getId() << endl;
				fout << "Balance= " << it->second->getBalance() << endl;
				fout << "Rate= " << it->second->getRate() << endl;
				fout << "LastRecordedDate= " << it->second->getLastRecordedDate().TransferToString() << endl;
				fout << "AccumulationLastDate= " << it->second->accumulation.lastDate.TransferToString() << endl;
				fout << "AccumulationValue= " << it->second->accumulation.value << endl;
				fout << "AccumulationSum= " << it->second->accumulation.sum << endl;
				fout << "LogInfoStart" << endl;
				int year = Today.getYear();
				int month = Today.getMonth();
				if(month <= 3)
				{
					year-=1;
					month = 12-3+month;
				}
				int sum = 0;
				bool LowerBoundArrived = false;
				for(multimap<Date,LogInfo> ::reverse_iterator ite = it -> second -> Log.rbegin(); (!LowerBoundArrived || sum < 5)&&(ite != it -> second ->Log.rend());ite ++)
				{
					if(ite.base() == it -> second -> Log.lower_bound(Date(year,month,1)))
					{
						LowerBoundArrived = true;
					}
					sum ++;
					fout <<"Log= "<< ite -> second.getDate().TransferToString()  <<" " << ite -> second.getAmount() <<" " <<ite -> second.getDetail() << endl;
				}
				fout << "LogInfoEnd" << endl;
				fout << "SavingsAccountEnd" << endl; //储蓄账户数据结束标志
			}
			if (it->second->getAccountType() == TypeCredit)
			{
				fout << "CreditAccountStart" << endl; //信用账户数据起始标志
				fout << "ID= " << it->second->getId() << endl;
				fout << "Balance= " << it->second->getBalance() << endl;
				fout << "Rate= " << it->second->getRate() << endl;
				fout << "LastRecordedDate= " << it->second->getLastRecordedDate().TransferToString() << endl;
				fout << "AccumulationLastDate= " << it->second->accumulation.lastDate.TransferToString() << endl;
				fout << "AccumulationValue= " << it->second->accumulation.value << endl;
				fout << "AccumulationSum= " << it->second->accumulation.sum << endl;
				CreditAccount *tmp = dynamic_cast<CreditAccount *>(it->second);
				fout << "Credits= " << tmp->getCredits() << endl;
				fout << "AnnualFee= " << tmp->getAnnualFee() << endl;
				fout << "LogInfoStart" << endl;
				int year = Today.getYear();
				int month = Today.getMonth();
				if(month <= 3)
				{
					year-=1;
					month = 12-3+month;
				}
				int sum = 0;
				bool LowerBoundArrived = false;
				for(multimap<Date,LogInfo> ::reverse_iterator ite = it -> second -> Log.rbegin(); (!LowerBoundArrived || sum < 5)&&(ite != it -> second ->Log.rend());ite ++)
				{
					if(ite.base() == it -> second -> Log.lower_bound(Date(year,month,1)))
					{
						LowerBoundArrived = true;
					}
					sum ++;
					fout <<"Log= "<< ite -> second.getDate().TransferToString()  <<" " << ite -> second.getAmount() <<" " <<ite -> second.getDetail() << endl;
				}
				fout << "LogInfoEnd" << endl;
				fout << "CreditAccountEnd" << endl; //信用账户数据结束标志
			}
		}
			fout << "AccountEnd" << endl;//帐户信息结束标志
		fout << "UserEnd" << endl;
	}
	fout << "EndFile" << endl; //文件结束标识
	cout << "** 数据保存完成" << endl;
	fout.close();
	//return true;
}

//从文件中读取数据
bool System::ReadFile()
{
	cout << "正在从文件中读取数据..." << endl;
	fstream fin;
	fin.open(DataBaseFile);
	if (!fin)
	{
		cout << "文件打开错误。如果这是第一次运行程序，请按回车跳过,若不是，请检查文件目录下的DataBase.txt是否正常" << endl;
		cin.ignore();
		fin.close();
		return false;
	}
	string index;
	int SumOfAccount = 0;
	int SumOfUser = 0;
	while (!fin.eof())
	{

		fin >> index;

		//cout << "1: " << index << endl;

		if (index == "UserStart")
		{
			SumOfUser++;
			User *usr;
			string username;
			string password;

			while (index != "UserInfoEnd")
			{
				fin >> index;
				//cout << "6:" << index << endl;
				if (index == "Username=")
				{
					fin >> username;
				}
				else if (index == "Password=")
				{
					fin >> password;
				}
			}
			usr = new User(username, password);
			Account *tmp;
			fin >> index;
			//cout << "5: " << index << endl;
			if (index == "AccountStart")
			{
				while (index != "AccountEnd")
				{
					fin >> index;

					//cout <<"4:" <<endl;

					while (index == "SavingsAccountStart")
					{
						SumOfAccount++;

						//读入学生基本信息
						string id = "";
						double balance = 0;
						double rate = 0;
						Date LastRecordedDate(2019, 1, 1);
						Date AccumulationLastDate(2019, 1, 1);
						double AccumulationValue = 0;
						double AccumulationSum = 0;
						multimap<Date,LogInfo> log;
						while (index != "SavingsAccountEnd")
						{
							fin >> index;

							//cout << "2:" << index << endl;

							if (index == "ID=")
							{
								fin >> id;
							}
							else if (index == "Balance=")
							{
								fin >> balance;
							}
							else if (index == "Rate=")
							{
								fin >> rate;
							}
							else if (index == "LastRecordedDate=")
							{
								fin >> LastRecordedDate;
							}
							else if (index == "AccumulationLastDate=")
							{
								fin >> AccumulationLastDate;
							}
							else if (index == "AccumulationValue=")
							{
								fin >> AccumulationValue;
							}
							else if (index == "AccumulationSum=")
							{
								fin >> AccumulationSum;
							}
							else if(index == "LogInfoStart")
							{
								fin >> index;
								while(index != "LogInfoEnd")
								{
									Date date;
									double amount;
									string detail;
									fin >> date >> amount >> detail;
									log.insert(make_pair(date,LogInfo(date,amount,detail)));
									fin >> index;
								}
							}
						}

						tmp = new SavingsAccount(LastRecordedDate, id, rate, usr->getUsername(), balance, AccumulationLastDate,AccumulationValue,AccumulationSum,log);
						usr->AddAccount(id, tmp);
					}
					while (index == "CreditAccountStart")
					{
						SumOfAccount++;

						//读入学生基本信息
						string id = "";
						double balance = 0;
						double rate = 0;
						Date LastRecordedDate(2019, 1, 1);
						Date AccumulationLastDate(2019, 1, 1);
						double AccumulationValue = 0;
						double AccumulationSum = 0;
						double credits = 0;
						double annualFee = 0;
						multimap<Date,LogInfo> log;

						while (index != "CreditAccountEnd")
						{
							fin >> index;

							//cout << "3: " << index << endl;

							if (index == "ID=")
							{
								fin >> id;
							}
							else if (index == "Balance=")
							{
								fin >> balance;
							}
							else if (index == "Rate=")
							{
								fin >> rate;
							}
							else if (index == "LastRecordedDate=")
							{
								fin >> LastRecordedDate;
							}
							else if (index == "AccumulationLastDate=")
							{
								fin >> AccumulationLastDate;
							}
							else if (index == "AccumulationValue=")
							{
								fin >> AccumulationValue;
							}
							else if (index == "AccumulationSum=")
							{
								fin >> AccumulationSum;
							}
							else if (index == "Credits=")
							{
								fin >> credits;
							}
							else if (index == "AnnualFee=")
							{
								fin >> annualFee;
							}
							else if(index == "LogInfoStart")
							{
								fin >> index;
								while(index != "LogInfoEnd")
								{
									Date date;
									double amount;
									string detail;
									fin >> date >> amount >> detail;
									log.insert(make_pair(date,LogInfo(date,amount,detail)));
									fin >> index;
								}
							}
						}

						tmp = new CreditAccount(LastRecordedDate, id, rate, credits, annualFee, usr->getUsername(), balance, AccumulationLastDate, AccumulationValue, AccumulationSum,log);
						usr->AddAccount(id, tmp);
					}
				}
			}
			AddUser(username, usr);
		}
	}
	cout << SumOfUser << " 个用户信息 " << SumOfAccount << " 个账户信息读取完成。" << endl;
	fin.close();
	return true;
}

void System::CMDUseAccount()
{
	string id;
	cin >> id;
	if (CurrentUser != NULL)
	{
		CurrentUser->UseAccount(id);
		cout <<"** 欢迎您 " <<id<<" ,请告诉我今天的日期:";
		cin >> Today;
		CurrentUser->CurrentAccount->Process(Today);

	}
	else
	{
		throw runtime_error("未登录，无法选择账户");
	}
}

void System::HelpMe(string cmd)
{

	if (cmd == "all" || cmd == "help")
	{
		cout << "help:查看帮助信息" << endl;
		cout << "格式:" << endl;
		cout << "help [命令名]" << endl;
		cout << "说明:" << endl;
		cout << "使用help all 可以查看全部命令帮助信息" << endl;
		cout << "样例：" << endl;
		cout << "1.help register" << endl;
		cout << "2.help all" << endl;
	}
	if (cmd == "all" || cmd == "new-acc")
	{
		cout << "new-acc:注册账号。" << endl;
		cout << "格式:" << endl;
		cout << "信用账户：new-acc [日期] Credit [ID] [利率] [信用额度] [年费]" << endl;
		cout << "储蓄账户：new-acc [日期] Savings [ID] [利率]" << endl;
		cout << "说明:" << endl;
		cout << "[日期]格式：YYYY-MM-DD，例：2019-1-1" << endl;
		cout << "[利率]使用浮点形式，不能使用百分数。" << endl;
		cout << "样例：" << endl;
		cout << "1.new-acc 2019-1-1 Credit 001 0.015 10000 1000" << endl;
		cout << "2.new-acc 2019-12-30 Savings LIUYANG 0.015" << endl;
		cout << "------------------------------------------------------------" << endl;
	}
	if (cmd == "all" || cmd == "use-acc")
	{
		cout << "use-acc:登陆后选择账户。" << endl;
		cout << "格式:" << endl;
		cout << "login [ID]" << endl;
		cout << "样例：" << endl;
		cout << "1.use-acc 001" << endl;
		cout << "2.use-acc LIUYANG" << endl;
		cout << "------------------------------------------------------------" << endl;
	}
	if (cmd == "all" || cmd == "logout")
	{
		cout << "logout:登出账号." << endl;
		cout << "格式:" << endl;
		cout << "logout" << endl;
		cout << "样例：" << endl;
		cout << "1.logout" << endl;
		cout << "------------------------------------------------------------" << endl;
	}
	if (cmd == "all" || cmd == "deposit")
	{
		cout << "deposit:实现存款操作。" << endl;
		cout << "格式:" << endl;
		cout << "deposit [金额]" << endl;
		cout << "样例：" << endl;
		cout << "1.deposit 5000" << endl;
		cout << "2.deposit 10000" << endl;
		cout << "------------------------------------------------------------" << endl;
	}
	if (cmd == "all" || cmd == "withdraw")
	{
		cout << "withdraw:实现取款操作。" << endl;
		cout << "格式:" << endl;
		cout << "withdraw [日期] [金额]" << endl;
		cout << "样例：" << endl;
		cout << "1.withdraw 5000" << endl;
		cout << "2.withdraw 10000" << endl;
		cout << "------------------------------------------------------------" << endl;
	}
	if (cmd == "all" || cmd == "show")
	{
		cout << "show:查看账户信息。" << endl;
		cout << "格式:" << endl;
		cout << "show" << endl;
		cout << "样例：" << endl;
		cout << "show" << endl;
		cout << "------------------------------------------------------------" << endl;
	}
	if (cmd == "all" || cmd == "exit")
	{
		cout << "exit:保存全部操作并退出系统。" << endl;
		cout << "格式:" << endl;
		cout << "exit" << endl;
		cout << "样例：" << endl;
		cout << "exit" << endl;
		cout << "------------------------------------------------------------" << endl;
	}
	if (cmd == "all" || cmd == "register")
	{
		cout << "register:注册账号。" << endl;
		cout << "格式:" << endl;
		cout << "register" << endl;
		cout << "样例：" << endl;
		cout << "register" << endl;
		cout << "------------------------------------------------------------" << endl;
	}
	if (cmd == "all" || cmd == "login")
	{
		cout << "login:注册账号。" << endl;
		cout << "格式:" << endl;
		cout << "login" << endl;
		cout << "样例：" << endl;
		cout << "login" << endl;
		cout << "------------------------------------------------------------" << endl;
	}
	if (cmd == "all"|| cmd == "show-log" )
	{
		cout << "show-log:查询日志。" << endl;
		cout << "格式:" << endl;
		cout << "show-log [日期] [排序方式]" << endl;
		cout << "说明:"<<endl;
		cout << "[日期]：输入完整日期，精确到月，如2019-1-1 和2019-1-30都表示2019年1月，不允许输入2019-1"<<endl;
		cout << "[排序方式]:2种，time 按时间排序 value按金额从大到小排序"<<endl;
		cout << "样例：" << endl;
		cout << "show-log 2019-1-1 time 查看2019年1月的日志，按照时间排序" << endl;
		cout << "------------------------------------------------------------" << endl;
	
	}
	else
	{
		cout << "command " << cmd << " not fount" << endl;
	}
}
void System::Start()
{

	cout << "---------------Welcome!-------------------" << endl;
	cout << endl;
	cout << "          ====       ====" << endl;
	cout << "            \\\\       //" << endl;
	cout << "             \\\\     //" << endl;
	cout << "              \\\\   //" << endl;
	cout << "               \\\\ //" << endl;
	cout << "             =========        " << endl;
	cout << "                |||" << endl;
	cout << "                |||" << endl;
	cout << "                |||" << endl;
	cout << "               =====" << endl << endl;

	while (MainLoop());
}

void System::ShowMenu(bool showDetail)
{
	if (CurrentUser == NULL)
	{
		if (showDetail)
		{
			cout << "-----------------菜单:----------------------" << endl;
			cout << "_________________________________________________________" << endl;
			cout << "|    命令    |                说明                       " << endl;
			cout << "| register   |注册账号                                   " << endl;
			cout << "| login      |登陆                                       " << endl;
			cout << "| help       |查看命令帮助信息。格式:help [命令名]          " << endl;
			cout << "| exit       |保存操作并退出系统。                         " << endl;
			cout << "————————————————————————————" << endl;
		}
		cout << "** 您还未登录，请登陆或注册." << endl;
		cout << "   None@None$";
	}
	else if (!CurrentUser->isAccountSelected())
	{
		if (showDetail)
		{
			cout << "-----------------菜单:----------------------" << endl;
			cout << "_________________________________________________________" << endl;
			cout << "|    命令    |                说明                       " << endl;
			cout << "| new-acc    |创建账户,格式：new-acc [日期] [账户类型] [id]" << endl;
			cout << "|            [利率] [信用额度] [年费] Saving账户省略后两项 " << endl;
			cout << "| use-acc    |选择账户，格式 use-acc [id]                 " << endl;
			cout << "| show-acc   |查看所有账户信息                            " << endl;
			cout << "| logout     |登出账号,格式 logout                        " << endl;
			cout << "| help       |查看命令帮助信息。格式:help [命令名]          " << endl;
			cout << "| exit       |保存操作并退出系统。                         " << endl;
			cout << "—————————————————————————————" << endl;
		}
		cout << "** 你还没有选择账户." << endl;
		cout << "None"
			 << "@" << CurrentUser->getUsername() << "$";
	}
	else
	{
		if (showDetail)
		{
			cout << "-----------------菜单:----------------------" << endl;
			cout << "_________________________________________________________" << endl;
			cout << "|    命令    |                说明                       " << endl;
			cout << "| new-acc    |创建账户,格式：new-acc [日期] [账户类型] [id]" << endl;
			cout << "|            [利率] [信用额度] [年费] Saving账户省略后两项 " << endl;
			cout << "| use-acc    |选择账户，格式 use-acc [id]                 " << endl;
			cout << "| show-acc   |查看所有账户信息                             " << endl;
			cout << "| logout     |登出账号,格式 logout                        " << endl;
			cout << "| logout-acc |登出账户，格式 logout-acc                   " << endl;
			cout << "| deposit    |实现存款操作。用法:deposit [金额]     " << endl;
			cout << "| withdraw   |实现取款操作。用法:withdraw [金额]    " << endl;
			cout << "| show-log   |查询某个月的日志。用法:show-log [日期] [排序方式]" <<endl;
			cout << "| show       |展示账户信息。用法:show [日期]               " << endl;
			cout << "| help       |查看命令帮助信息。格式:help [命令名]          " << endl;
			cout << "| exit       |保存操作并退出系统。                         " << endl;
			cout << "————————————————————————————" << endl;
		}
		//cout << "$请输入命令，使用 \"help all\"查看全部命令。" << endl;
		cout << CurrentUser->CurrentAccount->getId() << "@" << CurrentUser->getUsername() << "$";
	}
}

bool System::MainLoop()
{
	static bool ShowDetail = true;
	try
	{
		ShowMenu(ShowDetail);
		ShowDetail = false;
		string cho;
		cin >> cho;
		if (cho == "help")
		{
			string cmd;
			cin >> cmd;
			HelpMe(cmd);
		}
		else if (cho == "exit")
		{
			return false;
		}
		else
		{
			if (CurrentUser == NULL)
			{
				if (cho == "register")
				{
					CMDRegister();
				}
				else if (cho == "login")
				{
					CMDLogin();
					ShowDetail = true;
				}
				else
					cout << "Command " << cho << " Not Fount." << endl;
			}
			else
			{
				if (cho == "new-acc")
				{
					CMDCreateAccount();
				}
				else if (cho == "use-acc")
				{
					CMDUseAccount();
					
					ShowDetail = true;
				}
				else if (cho == "show-acc")
				{
					CurrentUser->ShowAllAccount();
				}
				else if (cho == "logout")
				{
					Logout();
				}
				else if (CurrentUser->isAccountSelected())
				{
					if (cho == "logout-acc")
					{
						CurrentUser->AccountLogout();
					}
					if (cho == "deposit")
					{

						try
						{
							double amount;
							cin >> amount;
							//cout <<"Debug" << Today << endl;
							//cout <<"Debug::存款"<<endl;
							CurrentUser->Deposit(Today, amount);
						}
						catch (const std::exception &e)
						{
							std::cerr <<"【存款错误】:" << e.what() << '\n';
						}
					}
					else if (cho == "withdraw")
					{
						try
						{
							//cout << "哈哈哈"<<endl;
							double amount;
							cin >> amount;
							//cout <<"Debug" << Today << endl;
							//cout <<"Debug::取款"<<endl;
							CurrentUser->Withdraw(Today, amount);
						}
						catch (const std::exception &e)
						{
							std::cerr <<"【取款错误】:"<< e.what() << '\n';
						}
					}
					else if(cho == "show-log")
					{
						try
						{
							Date date;
							string method;
							cin >> date >> method;
							if(method == "time")
								CurrentUser -> CurrentAccount -> ShowLogTime(date);
							else
								CurrentUser -> CurrentAccount -> ShowLogAmount(date);
						}
						catch(const std::exception& e)
						{
							std::cerr <<"【查询错误】: "<< e.what() << '\n';
						}
					}
					else if (cho == "show")
					{
						CurrentUser->CurrentAccount->show();
					}
				}
				else
					cout << "Command " << cho << " Not Fount." << endl;
			}
		}
	}
	catch (const std::exception &e)
	{
		std::cerr <<"【其他错误】: "<< e.what() << '\n';
		return true;
	}
	return true;
}
