#include "RegisterDialog.h"
#include "ui_RegisterDialog.h"
#include "QMessageBox"
RegisterDialog::RegisterDialog(System *oss,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog),
    os(oss)
{
    ui->setupUi(this);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_registerBtn_clicked()
{
    try
    {
        string username,password;
        username = ui ->UsernameLineEdit->text().toStdString();
        password = ui->PasswordLineEdit->text().toStdString();

        if(ui->PasswordLineEdit_2->text().toStdString() == password)
        {
            os ->Register(username,password);
        }
        else
        {
            QMessageBox::warning(this,tr("Warning"),tr("两次密码输入不一致。"),QMessageBox::Yes);
        }
        accepted();
    }
    catch(const std::exception &e)
    {
        QMessageBox::warning(this,tr("Warning"),tr(e.what()),QMessageBox::Yes);
    }
}
