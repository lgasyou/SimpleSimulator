#include "mainwindow.h"
#include <QApplication>

/*******************************************
	Project:	Building-Value-Simulator
	Author:		Xenon
	Create at:	2017.1.22
*******************************************/

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    MainWindow window;
    window.show();
    return application.exec();
}