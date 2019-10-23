#include "logindialog.h"
#include "ui_logindialog.h"
#include "QMessageBox"
#include "System.h"
LoginDialog::LoginDialog(System *oss,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),
    os(oss)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_LoginBtn_clicked()
{
    try
    {
       os -> Login(ui->usrLineEdit->text().toStdString() , ui->pwdLineEdit->text().toStdString());
       accept();
    }
    catch(const std::exception &e)
    {
        QMessageBox::warning(this,tr("Warning"),tr(e.what()),QMessageBox::Yes);
    }
}
