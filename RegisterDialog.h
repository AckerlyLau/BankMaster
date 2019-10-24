#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include "System.h"
namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(System *oss,QWidget *parent = nullptr);
    ~RegisterDialog();

private slots:
    void on_registerBtn_clicked();

private:
    Ui::RegisterDialog *ui;
    System *os;
};

#endif // REGISTERDIALOG_H
