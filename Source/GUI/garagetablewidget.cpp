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

#include "garagetablewidget.h"

#include "Source/Objects/baseindustry.h"
#include "Source/Objects/goodscontainer.h"

#include "Source/Managers/uimanager.h"

#include "setroutedialog.h"
#include "tablewidgetpushbutton.h"
#include "widgethelper.h"

GarageTableWidget::GarageTableWidget(QWidget *parent) : 
    QTableWidget(parent) {
    init();
}

GarageTableWidget::~GarageTableWidget() { }

void GarageTableWidget::init() {
    this->setColumnCount(6);
    QStringList header{ tr("Name"), tr("State"), tr("Destination"), tr("Plan"),  tr("Remain Time"), tr("Option") };
    this->setHorizontalHeaderLabels(header);
}

void GarageTableWidget::updateDisplay() {
    if (garage_ != nullptr) {
        auto &vihicleList = garage_->vihicleList();
        this->setRowCount((int)vihicleList.size());

        int index = 0;
        this->clearContents();
        for (auto vihicle : vihicleList) {
            updateEachRow(index++, vihicle);
        }
    }
}

void GarageTableWidget::updateEachRow(int index, Truck *truck) {
    setItem(index, 0, new QTableWidgetItem(tr("Truck")));
    const QString &curVolume = WidgetHelper::toString(truck->freightHouse()->curVolume());
    const QString &maxVolume = WidgetHelper::toString(truck->freightHouse()->maxVolume());
    setItem(index, 1, new QTableWidgetItem(curVolume + " / " + maxVolume));
    if (truck->isWorking()) {
        const QString &dest = truck->route()->dest->name();
        const QString &goods = truck->route()->goods.label;
        const QString &volume = WidgetHelper::toString(truck->route()->goods.volume);
        const QString &remainTime = WidgetHelper::toString(truck->remainTime());
        setItem(index, 2, new QTableWidgetItem(dest));
        setItem(index, 3, new QTableWidgetItem(goods + " / " + volume));
        setItem(index, 4, new QTableWidgetItem(remainTime));
    }

    const QString &text = truck->isWorking() ? tr("Stop") : tr("Route");
    TableWidgetPushButton *routeBtn = new TableWidgetPushButton(text);
    routeBtn->setIndex(index);
    setCellWidget(index, 5, routeBtn);

    connect(routeBtn,    SIGNAL(sendData(int, int)),
            this,        SLOT(buttonClicked(int, int)));
}

void GarageTableWidget::setGarage(Land *garage) {
    this->garage_ = dynamic_cast<Garage *>(garage);
}

void GarageTableWidget::buttonClicked(int index, int command) {
    // TODO:
    switch (command) {
    case 1:// Show
        showSetRouteDialog(index);
        break;

    case 2: // Stop
        Truck *truck = garage_->getById(index);
        garage_->stopVihicle(truck);
        emit dataChanged();
        break;
    }
}

void GarageTableWidget::showSetRouteDialog(int index) {
    selectedTruckId_ = index;

    SetRouteDialog *setRouteDialog = UIManager::instance().setRouteDialog();
    setRouteDialog->createNewRoute();
    static bool isTheFirstTimeCall = true;
    if (isTheFirstTimeCall) {
        connect(setRouteDialog, SIGNAL(sendRoute(Route*)),
                this,           SLOT(setRoute(Route*)));
        setRouteDialog->setParent(this, Qt::Window);
        isTheFirstTimeCall = false;
    }
    WidgetHelper::showUp(setRouteDialog);
    setRouteDialog->updateDisplay();
}

void GarageTableWidget::setRoute(Route *route) {
    garage_->sendVihicle(route, selectedTruckId_);
    emit dataChanged();
}
