﻿/*
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

#include "BuildingInfoWidget.h"

#include <memory>

#include "Source/Objects/Company.h"
#include "Source/Objects/Government.h"
#include "Source/Commmands.h"

#include "Source/Managers/CompanyManager.h"

#include "MainWindow.h"
#include "WidgetHelper.h"
#include "ui_buildinginfowidget.h"

BuildingInfoWidget::BuildingInfoWidget(QWidget *parent)
    : QWidget(parent) {
    ui = new Ui::BuildingInfoWidget;
    ui->setupUi(this);

    connect(ui->detailsPushButton, &CommandPushButton::sendCommand,
            WidgetHelper::placeCommand);
    ui->detailsPushButton->hide();

    connect(ui->buyOrSellpushButton, &CommandPushButton::sendCommand,
            WidgetHelper::placeCommand);
    ui->buyOrSellpushButton->hide();
}

BuildingInfoWidget::~BuildingInfoWidget() {
    delete ui;
}

void BuildingInfoWidget::setTarget(LandParcel *building) {
    this->displayingObject_ = building;
    ui->detailsPushButton->setCommand(std::make_shared<ShowDetailCommand>(building));
}

void BuildingInfoWidget::showBuildingInfo(LandParcel *building) {
    if (building != displayingObject_) {
        setTarget(building);

        if (building) {
            updateDisplay();
        } else {
            ui->buildingNameLabel->clear();
            ui->buildingOwnerLabel->clear();
        }
        ui->buyOrSellpushButton->setVisible(building);
        ui->detailsPushButton->setVisible(building);
    }
}

void BuildingInfoWidget::updateDisplay() {
    if (displayingObject_) {
        auto &name = displayingObject_->name();
        ui->buildingNameLabel->setText(name);
        auto &owner = displayingObject_->owner()->name();
        ui->buildingOwnerLabel->setText("Owner:\n\n" + owner);

        bool owned = displayingObject_->owner() == CompanyManager::instance().playerCompany();
        const QString buttonText = owned ? tr("Sell") : tr("Buy");
        ui->buyOrSellpushButton->setCommand(
            owned ?
            std::make_shared<TransactionCommand>(
                this,
                &Government::instance(), 
                displayingObject_->owner(), 
                displayingObject_) :
            std::make_shared<TransactionCommand>(
                this,
                CompanyManager::instance().playerCompany(), 
                displayingObject_->owner(), 
                displayingObject_)
        );
        ui->buyOrSellpushButton->setText(buttonText);
    }
}