#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "System.h"
namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(System *oss = nullptr,QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void on_LoginBtn_clicked();
    void on_LoginDialog_objectNameChanged(const QString &objectName);

    void on_CancleBtn_clicked();
    
private:
    Ui::LoginDialog *ui;
    System *os;

};

#endif // LOGINDIALOG_H
