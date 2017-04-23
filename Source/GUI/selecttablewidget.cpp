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

#include "selecttablewidget.h"

#include "Source/Objects/land.h"

#include "Source/Managers/buildingmanager.h"

SelectTableWidget::SelectTableWidget(QWidget *parent) :
    QTableWidget(parent) {    
    init();
}

SelectTableWidget::~SelectTableWidget() { }

void SelectTableWidget::init() {
    setColumnCount(3);
    QStringList header{ tr("Name"), tr("Type"), tr("Option") };
    setHorizontalHeaderLabels(header);
    setWindowTitle(tr("Select Building:"));
}

void SelectTableWidget::updateDisplay() {
    const auto &buildingManager = BuildingManager::instance();
    auto &buildings = buildingManager.buildings();
    setRowCount((int)buildingManager.buildingNumber());
    clearContents();
    int indexOfBuilding = 0;
    int indexOfChosen = 0;
    for (auto item : buildings) {
        for (const auto &typeName : typeNames_) {
            if (item->type().contains(typeName)) {
                updateEachLine(indexOfChosen, indexOfBuilding, item);
                ++indexOfChosen;
            }
        }
        ++indexOfBuilding;
    }
    setRowCount(indexOfChosen);
}

void SelectTableWidget::updateEachLine(int indexInWidget, int indexInManager, const Land *building) {
    const QString &name = building->name();
    const QString &type = building->type();
    setItem(indexInWidget, 0, new QTableWidgetItem(name));
    setItem(indexInWidget, 1, new QTableWidgetItem(type));

    TableWidgetPushButton *selectButton = new TableWidgetPushButton(tr("Select"));
    setCellWidget(indexInWidget, 2, selectButton);
    selectButton->setIndex(indexInManager);
    connect(selectButton,    SIGNAL(sendData(int, int)),
            this,            SLOT(getDestAndSendBuilding(int)));
}

void SelectTableWidget::setSelector(int type) {
    typeNames_.clear();
    if (type) {
        if (type & UnusedLand)
            typeNames_.push_back("Unused Land");
        if (type & Factory)
            typeNames_.push_back("Factory");
        if (type & Mine)
            typeNames_.push_back("Mine");
    }
}

void SelectTableWidget::getDestAndSendBuilding(int index) {
    Land *building = BuildingManager::instance().getById(index);
    emit sendBuilding(building);
}
