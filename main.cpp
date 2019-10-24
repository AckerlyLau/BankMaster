#include "mainwindow.h"
#include <QTextCodec>
#include <QApplication>
#include "logindialog.h"
#include "System.h"
int main(int argc, char *argv[])
{
    System *os = new System(argc,argv);
    os -> UIStart();
}
