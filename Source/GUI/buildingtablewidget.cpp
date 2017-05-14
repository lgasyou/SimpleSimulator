/*
 *  Copyright 2017 Li Zeqing
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

#include "buildingtablewidget.h"

#include <QFile>
#include <QApplication>

#include "Source/Objects/company.h"

#include "Source/Managers/buildingmanager.h"
#include "Source/Managers/companymanager.h"
#include "Source/Objects/government.h"

#include "commandpushbutton.h"
#include "mainwindow.h"
#include "widgethelper.h"

BuildingTableWidget::BuildingTableWidget(QWidget *parent) :
    QTableWidget(parent) {
    init();
}

void BuildingTableWidget::init() {
    resize(QSize(800, 600));

    setWindowTitle(tr("Building Information List"));

    this->setColumnCount(6);
    QStringList header{ tr("Name"),tr("Value"),tr("Type"), tr("Ownership"),tr("Option"), tr("Option") };
    this->setHorizontalHeaderLabels(header);
}

void BuildingTableWidget::updateDisplay() {
    auto &buildingManager = BuildingManager::instance();
    int buildingNumber = (int)buildingManager.buildingNumber();
    this->setRowCount(buildingNumber);

    const auto &buildings = buildingManager.buildings();

    this->clearContents();
    for (int index = 0; index != buildingNumber; ++index) {
        displayBasicInfo(index, buildings[index]);
        displayAccordingToVisitor(index, buildings[index]);
    }
}

void BuildingTableWidget::displayBasicInfo(int index, Land *building) {
    const QString &name = building->name();
    const QString &deltaValue = " " + WidgetHelper::toString(building->deltaValue());
    const QString &value = "$" + WidgetHelper::toString(building->value()) + deltaValue;
    const QString &type = building->type();
    const QString &owner = building->owner()->name();
    setItem(index, 0, new QTableWidgetItem(name));
    setItem(index, 1, new QTableWidgetItem(value));
    setItem(index, 2, new QTableWidgetItem(type));
    setItem(index, 3, new QTableWidgetItem(owner));
}

void BuildingTableWidget::displayAccordingToVisitor(int index, Land *building) {
    Company *playerCompany = CompanyManager::instance().playerCompany();

	CommandPushButton *optionBtn =
        (building->owner() != playerCompany) ?
        new CommandPushButton(tr("Buy"), std::make_shared<TransactionCommand>(
			&Government::instance(), 
			building->owner(), 
			building)) :
        new CommandPushButton(tr("Sell"), std::make_shared<TransactionCommand>(
			CompanyManager::instance().playerCompany(), 
			building->owner(), 
			building));
    connect(optionBtn, &CommandPushButton::sendCommand,
            &WidgetHelper::placeCommand);
    setCellWidget(index, 4, optionBtn);

    CommandPushButton *detailBtn = new CommandPushButton(tr("Details"), std::make_shared<ShowDetailCommand>(building));
    connect(detailBtn, &CommandPushButton::sendCommand,
			&WidgetHelper::placeCommand);
    setCellWidget(index, 5, detailBtn);
}
