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
    void on_pushButton_clicked();

    void on_finishBtn_clicked();

private:
    Ui::CreateAccountDialog *ui;
    System *os;
};

#endif // CREATEACCOUNTDIALOG_H
