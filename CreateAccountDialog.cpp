#include "CreateAccountDialog.h"
#include "ui_CreateAccountDialog.h"
#include "QMessageBox"
CreateAccountDialog::CreateAccountDialog(System *oss,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateAccountDialog),
    os(oss)
{
    ui->setupUi(this);
    ui -> AccountTypeComoBox->addItem("储蓄账户");
    ui ->AccountTypeComoBox->addItem("信用账户");
    ui -> CreditLineEdit->setEnabled(false);
    ui -> AnnualFeeLineEdit->setEnabled(false);
}

CreateAccountDialog::~CreateAccountDialog()
{
    delete ui;
}



void CreateAccountDialog::on_finishBtn_clicked()
{
    try
    {
       if(ui->AccountTypeComoBox->currentText() == "信用账户")
       {
           os -> CreateAccount(os->getToday(),
                               ui->IDLineEdit->text().toStdString() ,
                               ui->RateLineEdit->text().toDouble(),
                               ui -> CreditLineEdit->text().toDouble(),
                               ui->AnnualFeeLineEdit->text().toDouble()
                               );
           cout <<"Credit"<<endl;
       }
       else
       {
           os -> CreateAccount(os->getToday(),
                               ui->IDLineEdit->text().toStdString() ,
                               ui->RateLineEdit->text().toDouble(),
                               -1,
                               -1
                               );
           cout <<"Savings"<<endl;
       }
       emit sendData(ui->IDLineEdit->text());
       accept();
    }
    catch(const std::exception &e)
    {
        QMessageBox::warning(this,tr("Warning"),tr(e.what()),QMessageBox::Yes);
    }
}

void CreateAccountDialog::on_AccountTypeComoBox_currentTextChanged(const QString &arg1)
{
    if(ui->AccountTypeComoBox->currentText() == "信用账户")
    {
        ui -> CreditLineEdit->setEnabled(false);
        ui -> AnnualFeeLineEdit->setEnabled(false);
    }
    else
    {
        ui -> CreditLineEdit->setEnabled(true);
        ui -> AnnualFeeLineEdit->setEnabled(true);
    }
}
