#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "System.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool flagForAccountTypeComobox;

private slots:
    void on_actionNewAccount_triggered();

    void on_actionRegister_R_triggered();

    void on_TodayEdit_userDateChanged(const QDate &date);

    void on_AccountTypeComobox_currentTextChanged(const QString &arg1);

    void on_SubmitTransButton_clicked();
    void RenewAccountInfo();
    void receiveData(QString data);
    void on_actionLogout_triggered();
    void RenewUserInfo();
private:
    Ui::MainWindow *ui;
    System *os;
};
#endif // MAINWINDOW_H
