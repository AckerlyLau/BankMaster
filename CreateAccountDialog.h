#ifndef CREATEACCOUNTDIALOG_H
#define CREATEACCOUNTDIALOG_H

#include <QDialog>
#include "System.h"
namespace Ui {
class CreateAccountDialog;
}

class CreateAccountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateAccountDialog(System *oss,QWidget *parent = nullptr);
    ~CreateAccountDialog();

private slots:
    void on_finishBtn_clicked();
    void on_AccountTypeComoBox_currentTextChanged(const QString &arg1);
signals:
    void sendData(QString data);

private:
    Ui::CreateAccountDialog *ui;
    System *os;
};

#endif // CREATEACCOUNTDIALOG_H
