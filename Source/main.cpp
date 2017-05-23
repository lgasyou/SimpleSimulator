/*
 *  Copyright 2017 Li Zeqing
 *
 *  This project is created at 2017.1.22.
 *
 *  This file is part of World Simulator.
 *  
 *  World Simulator is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  World Simulator is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with World Simulator. If not, see <http://www.gnu.org/licenses/>.
 */

#include <QApplication>
#include "GUI/MainWindow.h"
#include "Managers/PriceManager.h"
#include "Managers/IndustryChainManager.h"
#include "Managers/CompanyManager.h"
#include "Managers/LandParcelManager.h"
#include "Managers/MapManager.h"
#include <QFontDatabase>

#define NO_DEBUG
#ifndef DEBUG

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    int fontId = QFontDatabase::addApplicationFont("Resources/consola.ttf");
    QString consola = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont font(consola, 11);
    application.setFont(font);

    MapManager::instance().init();
    LandParcelManager::instance().init();
    CompanyManager::instance().init();
    IndustryChainManager::instance().init();
    PriceManager::instance().init();
    MainWindow::instance().init();
    MainWindow::instance().show();
    return application.exec();
}

#else
#include "GUI/BankDetailDialog.h"


int fcn1(int argc, char *argv[]) {
    QApplication application(argc, argv);

    BankDetailDialog dialog;
    dialog.show();
    return application.exec();
}

#include "GUI/Widget.h"

int fcn2(int argc, char *argv[]) {
    QApplication application(argc, argv);
    Widget dialog(nullptr);
    dialog.show();
    return application.exec();
}

int main(int argc, char *argv[]) {
    return fcn1(argc, argv);
}



#endif