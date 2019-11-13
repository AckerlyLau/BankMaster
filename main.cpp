#include "mainwindow.h"
#include <QTextCodec>
#include <QApplication>
#include "logindialog.h"
#include "System.h"
int main(int argc, char *argv[])
{
    QApplication App(argc, argv);
    MainWindow Window;
    Window.show();
    App.exec();
}
