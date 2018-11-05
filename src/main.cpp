#include "mainwindow.h"
#include <QApplication>
#include <windows.h>


void Stealth()
{
 HWND Stealth;
 AllocConsole();
 Stealth = FindWindowA("ConsoleWindowClass", NULL);
 ShowWindow(Stealth,0);
}


int main(int argc, char *argv[])
{
    Stealth();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    a.exec();
    return 0;
}
