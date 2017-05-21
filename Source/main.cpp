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
#include "GUI/mainwindow.h"
#include "Managers/timemanager.h"
#include "Managers/pricemanager.h"
#include "Managers/industrychainmanager.h"
#include "Managers/companymanager.h"
#include "Managers/buildingmanager.h"
#include "Managers/mapmanager.h"
#include "Managers/uimanager.h"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    MapManager::instance().init();
    BuildingManager::instance().init();
    CompanyManager::instance().init();
    IndustryChainManager::instance().init();
    PriceManager::instance().init();
    TimeManager::instance().init();
    MainWindow::instance().init();
    MainWindow::instance().show();
    return application.exec();
}
