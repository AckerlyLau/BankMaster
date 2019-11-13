#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "System.h"
#include "CreateAccountDialog.h"
#include "RegisterDialog.h"
#include <ctime>
#include "Date.h"
#include <vector>
#include "QMessageBox"
#include <string>
#include <Account.h>
#include "logindialog.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    os = new System(ui);
    os -> UIStart();
    flagForAccountTypeComobox = true;
    RenewUserInfo();
}
void MainWindow::RenewUserInfo()
{
    try
    {
        flagForAccountTypeComobox = false;
        ui->AccountTypeComobox->clear();
        flagForAccountTypeComobox = true;
        ui->TransTypeComboBox->clear();
        //初始化当前日期
        time_t curtime;
        curtime = time(NULL);
        tm *timeinfo = localtime(&curtime);
        ui->TodayEdit->setDate(QDate(timeinfo ->tm_year+1900,timeinfo->tm_mon+1,timeinfo ->tm_mday));
        os->setToday(Date(timeinfo ->tm_year+1900,timeinfo ->tm_mon+1,timeinfo ->tm_mday));

        //初始化用户信息显示
        ui->UserNameLabel->setText((os->getCurrentUser() ->getUsername()).c_str());
        string balance = to_string(os->getCurrentUser()->getTotal());
        balance = balance.substr(0,balance.find('.')+3);
        ui->UserBalanceLabel->setText(balance.c_str());

        //初始化账户信息界面
        vector<string> ids = os->getCurrentUser()->getAllAccountID();
        for(vector<string>::iterator it = ids.begin();it != ids.end();it ++)
        {
            string dat = it -> data();
            ui -> AccountTypeComobox->addItem(dat.c_str());
        }
        ui->AccountCreditLabel->setVisible(false);
        ui->AccountAnnualFeeLabel->setVisible(false);
        ui->AccountCreditTitleLabek->setVisible(false);
        ui->AccountAnnualFeeTitleLabel->setVisible(false);


        //初始化交易界面
        ui->TransTypeComboBox->addItem("存款");
        ui->TransTypeComboBox->addItem("取款");
        // ui->ShowUserNameLabel->setText(os->CurrentUser->getUsername());
        //ui->nowDateLabel->setText(ctime(&curtime));
        /*
        ui->tableWidget->setRowCount(10);
        ui->tableWidget->setColumnCount(3);
        QStringList header;
        ui->tableWidget->horizontalHeader()->setSectionsClickable(false);
        header<<tr("ID")<<tr("账户类型")<<tr("余额");
        ui->tableWidget->setHorizontalHeaderLabels(header);
        ui->tableWidget->setSelectionBehavior ( QAbstractItemView::SelectRows ); //设置选择行为，以行为单位
        ui->tableWidget->setSelectionMode ( QAbstractItemView::SingleSelection ); //设置选择模式，选择单行
        ui->tableWidget->setItem(0,0,new QTableWidgetItem("1"));
        ui->tableWidget->setItem(1,0,new QTableWidgetItem("2"));
        //ui->tableWidget->tableHeader<<"ID"<<"账户类型"<<"";
        //ui->tableWidget->
        */
    }
    catch(const std::exception &e)
    {
        string str  = "刷新页面信息时发生错误:";
        str += e.what();
        QMessageBox::warning(this,tr("Warning"),tr(str.c_str()),QMessageBox::Yes);
    }
}
MainWindow::~MainWindow()
{
    delete os;
    delete ui;
}


void MainWindow::on_actionNewAccount_triggered()
{
    CreateAccountDialog *newAcc =new CreateAccountDialog(os);
    connect(newAcc,SIGNAL(sendData(QString)),this,SLOT(receiveData(QString)));
    newAcc->exec();

}

void MainWindow::receiveData(QString data)
{
    ui->AccountTypeComobox->addItem(data);
}

void MainWindow::on_actionRegister_R_triggered()
{
    RegisterDialog rsg(os);
    rsg.exec();
}

void MainWindow::on_TodayEdit_userDateChanged(const QDate &date)
{
    os->setToday(date.year(),date.month(),date.day());
}
void MainWindow::RenewAccountInfo()
{
    try
    {
        Account * acc;
        string nowstrid = ui->AccountTypeComobox->currentText().toStdString();
        os->getCurrentUser()->FindAccount(nowstrid,acc);
        Date today = (acc->getLastRecordedDate());
        if(os->getToday()<today)
        {
            os->setToday(today);
            ui->TodayEdit->setDate(QDate(today.getYear(),today.getMonth(),today.getDay()));
        }
        os->UseAccount(nowstrid);

        if(os->getCurrentUser()->getCurrentAccount()->getAccountType() == 1)//是信用账户?
        {
            ui->AccountCreditLabel->setVisible(true);
            ui->AccountAnnualFeeLabel->setVisible(true);
            ui->AccountCreditTitleLabek->setVisible(true);
            ui->AccountAnnualFeeTitleLabel->setVisible(true);
            ui->AccountTypeRateTitleLabel->setText("借款利率");
            ui->AccountTypeLabel->setText("信用账户");
            //string credit = to_string((dynamic_cast<CreditAccount*>(os->getCurrentUser()->getCurrentAccount())->getCredits()));
            //credit = credit.substr(0,credit.find('.')+3);
            ui->AccountCreditLabel->setNum(dynamic_cast<CreditAccount*>(os->getCurrentUser()->getCurrentAccount())->getCredits());
            // string fee = to_string((dynamic_cast<CreditAccount*>(os->getCurrentUser()->getCurrentAccount())->getAnnualFee()));
            //fee = fee.substr(0,fee.find('.')+3);
            ui->AccountAnnualFeeLabel->setNum(dynamic_cast<CreditAccount*>(os->getCurrentUser()->getCurrentAccount())->getAnnualFee());
        }
        else
        {
            ui->AccountCreditLabel->setVisible(false);
            ui->AccountAnnualFeeLabel->setVisible(false);
            ui->AccountCreditTitleLabek->setVisible(false);
            ui->AccountAnnualFeeTitleLabel->setVisible(false);
            ui->AccountTypeRateTitleLabel->setText("储蓄利率");
            ui->AccountTypeLabel->setText("储蓄账户");
        }

        ui->AccountRateLabel->setNum(os->getCurrentUser()->getCurrentAccount()->getRate());

        string balance = to_string(os->getCurrentUser()->getCurrentAccount()->getBalance());
        balance = balance.substr(0,balance.find('.')+3);
        ui->AccountBalanceLabel->setNum(os->getCurrentUser()->getCurrentAccount()->getBalance());
        ui->AccountOperateDateLabel->setText((os->getCurrentUser()->getCurrentAccount()->getLastRecordedDate()).TransferToString().c_str());
        balance = to_string(os->getCurrentUser()->getTotal());
        balance = balance.substr(0,balance.find('.')+3);
        ui->UserBalanceLabel->setText(balance.c_str());

    }
    catch(const std::exception &e)
    {
        string str  = "刷新账户信息时发生错误:";
        str += e.what();
        QMessageBox::warning(this,tr("Warning"),tr(str.c_str()),QMessageBox::Yes);
    }
}

void MainWindow::on_AccountTypeComobox_currentTextChanged(const QString &arg1)
{
    if(flagForAccountTypeComobox)
        RenewAccountInfo();
}

void MainWindow::on_SubmitTransButton_clicked()
{
    try
    {
        double amount = ui->TransAmountLineEdit->text().toDouble();
        if(ui->TransTypeComboBox->currentText().toStdString()=="存款")
        {
            os->Deposit(amount);
        }
        else
        {
            os->Withdraw(amount);
        }
        string balance ="操作成功，当前余额:";
        balance += to_string(os->getCurrentUser()->getCurrentAccount()->getBalance());
        balance = balance.substr(0,balance.find('.')+3);
        QMessageBox::information(this,"操作成功",balance.c_str());
        RenewAccountInfo();
    }
    catch(const std::exception& e)
    {
        QMessageBox::warning(this,"操作失败",e.what());
    }
}

void MainWindow::on_actionLogout_triggered()
{
   LoginDialog login(os);
   login.exec();
   RenewUserInfo();
}
