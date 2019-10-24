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
    MainWindow(System *oss,QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNewAccount_triggered();

private:
    Ui::MainWindow *ui;
    System *os;
};
#endif // MAINWINDOW_H
