/*
 *	Copyright 2017 Li Zeqing
 *
 *	This file is part of World Simulator.
 *	
 *	World Simulator is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU Lesser General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *	
 *	World Simulator is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *	
 *	You should have received a copy of the GNU Lesser General Public License
 *	along with World Simulator.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "buildinginfowidget.h"

#include "Source/Objects/company.h"

#include "Source/Managers/companymanager.h"

#include "Source/gameconstants.h"

#include "ui_buildinginfowidget.h"
#include "tablewidgetpushbutton.h"

BuildingInfoWidget::BuildingInfoWidget(QWidget *parent) : 
    QWidget(parent) {
    ui = new Ui::BuildingInfoWidget;
    ui->setupUi(this); 

    connect(ui->detailsPushButton,      SIGNAL(sendCommand(int)),
            this,                       SLOT(receiveCommand(int)));
    ui->detailsPushButton->setCommand(gameconstants::ShowDetail);
    ui->detailsPushButton->hide();

    connect(ui->buyOrSellpushButton,    SIGNAL(sendCommand(int)),
            this,                       SLOT(receiveCommand(int)));
    ui->buyOrSellpushButton->hide();
}

BuildingInfoWidget::~BuildingInfoWidget() {
    delete ui;
}

void BuildingInfoWidget::setTarget(BaseBuilding *building) {
    this->displayedBuilding_ = building;
}

void BuildingInfoWidget::receiveCommand(int command) {
    emit sendCommand(command, displayedBuilding_);
}

void BuildingInfoWidget::showBuildingInfo(BaseBuilding *building) {
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
        const QString &name = displayedBuilding_->name();
        ui->buildingNameLabel->setText(name);
        const QString &owner = displayedBuilding_->owner()->name();
        ui->buildingOwnerLabel->setText("Owner:\n\n" + owner);

        bool owned = (displayedBuilding_->owner() == CompanyManager::instance().playerCompany());
        const QString buttonText = owned ? tr("Sell") : tr("Buy");
        ui->buyOrSellpushButton->setCommand(owned ? gameconstants::SellBuilding : gameconstants::BuyBuilding);
        ui->buyOrSellpushButton->setText(buttonText);
    }
}