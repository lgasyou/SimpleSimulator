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

#include "buildinginfowidget.h"

#include <memory>

#include "Source/Objects/company.h"
#include "Source/Objects/government.h"
#include "Source/Commmand.h"

#include "Source/Managers/companymanager.h"

#include "ui_buildinginfowidget.h"
#include "tablewidgetpushbutton.h"
#include "mainwindow.h"
#include "widgethelper.h"

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

void BuildingInfoWidget::setTarget(Land *building) {
    this->displayedBuilding_ = building;
	ui->detailsPushButton->setCommand(std::make_shared<ShowDetailCommand>(building));
}

void BuildingInfoWidget::showBuildingInfo(Land *building) {
    if (building != displayedBuilding_) {
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
    if (displayedBuilding_) {
        auto &name = displayedBuilding_->name();
        ui->buildingNameLabel->setText(name);
        auto &owner = displayedBuilding_->owner()->name();
        ui->buildingOwnerLabel->setText("Owner:\n\n" + owner);

        bool owned = (displayedBuilding_->owner() == CompanyManager::instance().playerCompany());
        const QString buttonText = owned ? tr("Sell") : tr("Buy");
        ui->buyOrSellpushButton->setCommand(
			owned ?
			std::make_shared<TransactionCommand>(
				&Government::instance(), 
				displayedBuilding_->owner(), 
				displayedBuilding_) :
			std::make_shared<TransactionCommand>(
				CompanyManager::instance().playerCompany(), 
				displayedBuilding_->owner(), 
				displayedBuilding_)
		);
		ui->buyOrSellpushButton->setText(buttonText);
    }
}