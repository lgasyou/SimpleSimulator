#include "mainwindow.h"
#include <QApplication>

/******************************************
	Project:	Building-Value-Simulator
	Author:		Xenon
	Create at:	2017.1.22
******************************************/

#include "industrychainmanager.h"

int main(int argc, char *argv[])
{
	IndustryChainManager::instance().successors("Steel");

    QApplication application(argc, argv);
    MainWindow window;
    window.show();
    return application.exec();
}