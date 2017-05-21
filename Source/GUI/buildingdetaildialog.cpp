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

#include "BuildingDetailDialog.h"

#include "Source/Objects/land.h"
#include "Source/Objects/baseindustry.h"
#include "Source/Objects/company.h"
#include "Source/Objects/garage.h"
#include "Source/Objects/goods.h"
#include "Source/Objects/government.h"
#include "Source/Objects/machine.h"
#include "Source/Objects/mine.h"
#include "Source/Commmand.h"

#include "Source/MachineBuilders.h"

#include "Source/Managers/buildingmanager.h"
#include "Source/Managers/companymanager.h"
#include "Source/Managers/machinemanager.h"

#include "ui_buildingdetaildialog.h"
#include "widgethelper.h"

BuildingDetailDialog::BuildingDetailDialog(Land *object, QWidget *parent)
    : QDialog(parent),
      building_(object),
      ui(new Ui::BuildingDetailDialog) {
    ui->setupUi(this);

    signalSlotConfig();

    ui->expandStackedWidget->hide();
}

BuildingDetailDialog::~BuildingDetailDialog() {
    delete ui;
}

void BuildingDetailDialog::updateDisplay() {
    // Returns if this window isn't showing.
    if (this->isHidden() || !building_)    return;

    const QString &name = building_->name();
    const QString &value = WidgetHelper::toString(building_->value());
    const QString &type = building_->type();
    const QString &owner = building_->owner()->name();
    const QString &position = building_->position().toString();
    setWindowTitle(name);
    ui->nameLabel->setText(tr("Name:  ") + name);
    ui->valueLabel->setText(tr("Value: $") + value);
    ui->typeLabel->setText(tr("Type:  ") + type);
    ui->ownerLabel->setText(tr("Owner: ") + owner);
    ui->positionLabel->setText(tr("Position: ") + position);

    if (ui->machinePage->isVisible()) {
        updateMachineDetail(selectedMachine_);
    }

    displayAccordingToBuildingType();
}

void BuildingDetailDialog::closeEvent(QCloseEvent *) {

}

//void BuildingDetailDialog::deliverGoods(const Goods &goods, BaseIndustry *dest) {
// BaseIndustry *industry = dynamic_cast<BaseIndustry *>(building_);
// industry->deliverGoods(goods, dest);
// emit dataChanged();
//}

void BuildingDetailDialog::addNewMachine() {
    if (BaseIndustry *industry = dynamic_cast<BaseIndustry *>(building_)) {
        MachineBuilder *builder = new DefaultMachineBuilder;
        Machine *machine = MachineManager::instance().machine(builder);
        machine->setWarehouse(industry->warehouse());
        industry->addMachine(machine);
        delete builder;

        emit dataChanged();
    }
}

void BuildingDetailDialog::addNewVihicle() {
    if (Garage *garage = dynamic_cast<Garage *>(building_)) {
        garage->addNewVihicle("Truck");
        emit dataChanged();
    }
}

void BuildingDetailDialog::setNextMachineProduct(const QString &product) {
    selectedMachine_->setCurrentProduct(product);
    emit dataChanged();
}

void BuildingDetailDialog::showMachineDetail(Machine *machine) {
    ui->expandStackedWidget->show();
    selectedMachine_ = machine;

    ui->selectNextProductComboBox->clear();
    for (const auto &product : machine->products()) {
        ui->selectNextProductComboBox->addItem(product.label);
    }

    updateMachineDetail(machine);
}

void BuildingDetailDialog::updateMachineDetail(Machine *machine) {
    const QString &machineCurrentProductivity = WidgetHelper::toString(machine->currentProductivity());
    ui->machineCurrentProductivity->setText("Current Productivity: " + machineCurrentProductivity);

    const QString &machineMaximumProductivity = WidgetHelper::toString(machine->maximalProductivity());
    ui->machineMaximumProductivity->setText("Maximum Productivity: " + machineMaximumProductivity);
}

void BuildingDetailDialog::receiveCommand(int command) {
    emit sendCommand(command, building_);
    emit dataChanged();
}

void BuildingDetailDialog::displayAccordingToBuildingType() {
    bool isVisitorOwner = (building_->owner() == CompanyManager::instance().playerCompany());
    ui->basicOperationStackedWidget->setCurrentIndex(isVisitorOwner);

    const QString &type = building_->type();
    auto buildingType = BuildingManager::stringToEnum(type);
    ui->detailStackedWidget->setCurrentIndex(buildingType);
    switch (buildingType) {
    case BANK:
        break;

    case FACTORY:
        ui->factoryTableWidget->setIndustry(building_);
        ui->factoryTableWidget->updateDisplay();
        break;

    case FARM:
        break;

    case GARAGE: {
        Garage *garage = dynamic_cast<Garage *>(building_);
        const QString &freeVicleCount = QString::number(garage->freeVihicleCount());
        const QString &vihicleCount = QString::number(garage->vihicleCount());
        const QString &text = QString("%1 / %2 Truck Free").arg(freeVicleCount, vihicleCount);
        ui->garageStateLabel->setText(text);

        ui->garageTableWidget->setGarage(building_);
        ui->garageTableWidget->updateDisplay();
        break;
    }

    case MINE: {
        Mine *mine = dynamic_cast<Mine *>(building_);
        const QString &typeText = QString("Type:  %1 Mine").arg(mine->resource());
        ui->typeLabel->setText(typeText);

        ui->mineTableWidget->setIndustry(building_);
        ui->mineTableWidget->updateDisplay();
        break;
    }

    case SUPERMARKET:
        break;

    case UNUSED_LAND:
        break;

    case VILLA:
        break;

    default:
        break;
    }
}

void BuildingDetailDialog::signalSlotConfig() {
    /* ---------------------------------- Basic Config ---------------------------------------------- */
    connect(ui->buyPushButton,                          &CommandPushButton::sendCommand,
            &WidgetHelper::placeCommand);

    connect(ui->sellPushButton,                         &CommandPushButton::sendCommand,
            &WidgetHelper::placeCommand);

    connect(ui->dismantlePushButton,                    &CommandPushButton::sendCommand,
            &WidgetHelper::placeCommand);
    /* ---------------------------------------------------------------------------------------------- */

    /* ----------------------------------- Bank Config ---------------------------------------------- */
    //connect(ui->closeAnAccountPushButton,               SIGNAL(sendCommand(int)),
    //        this,                                       SLOT(receiveCommand(int)));
    //ui->closeAnAccountPushButton->setCommand(CLOSE_AN_ACCOUNT);

    //connect(ui->depositPushButton,                      SIGNAL(sendCommand(int)),
    //        this,                                       SLOT(receiveCommand(int)));
    //ui->depositPushButton->setCommand(DEPOSIT);

    //connect(ui->loanPushButton,                         SIGNAL(sendCommand(int)),
    //        this,                                       SLOT(receiveCommand(int)));
    //ui->loanPushButton->setCommand(LOAN);

    //connect(ui->openAnAccountPushButton,                SIGNAL(sendCommand(int)),
    //        this,                                       SLOT(receiveCommand(int)));
    //ui->openAnAccountPushButton->setCommand(OPEN_AN_ACCOUNT);

    //connect(ui->repayPushButton,                        SIGNAL(sendCommand(int)),
    //        this,                                       SLOT(receiveCommand(int)));
    //ui->repayPushButton->setCommand(REPAY);

    //connect(ui->withdrawPushButton,                     SIGNAL(sendCommand(int)),
    //        this,                                       SLOT(receiveCommand(int)));
    //ui->withdrawPushButton->setCommand(WITHDRAW);
    /* ---------------------------------------------------------------------------------------------- */

    /* ---------------------------------- Garage Config --------------------------------------------- */
    connect(ui->purchaseNewVihiclePushButton,           SIGNAL(clicked()),
            this,                                       SLOT(addNewVihicle()));
    /* ---------------------------------------------------------------------------------------------- */

    /* --------------------------------- Industry Config -------------------------------------------- */
    connect(ui->purchaseNewMachineInFactoryPushButton,  SIGNAL(clicked()),
            this,                                       SLOT(addNewMachine()));
    connect(ui->purchaseNewMachineInMinePushButton,     SIGNAL(clicked()),
            this,                                       SLOT(addNewMachine()));

    connect(ui->factoryTableWidget,                     SIGNAL(sendSelectedMachine(Machine *)),
            this,                                       SLOT(showMachineDetail(Machine *)));
    connect(ui->mineTableWidget,                        SIGNAL(sendSelectedMachine(Machine *)),
            this,                                       SLOT(showMachineDetail(Machine *)));

    connect(ui->selectNextProductComboBox,              SIGNAL(currentIndexChanged(const QString &)),
            this,                                       SLOT(setNextMachineProduct(const QString &)));
    /* ---------------------------------------------------------------------------------------------- */

    /* -------------------------------- UnusedLand Config ------------------------------------------- */
    connect(ui->buildBankPushButton,                    &CommandPushButton::sendCommand,
            WidgetHelper::placeCommand);

    connect(ui->buildFactoryPushButton,                 &CommandPushButton::sendCommand,
            WidgetHelper::placeCommand);

    connect(ui->buildFarmPushButton,                    &CommandPushButton::sendCommand,
            WidgetHelper::placeCommand);

    connect(ui->buildGaragePushButton,                  &CommandPushButton::sendCommand,
            WidgetHelper::placeCommand);

    connect(ui->buildMinePushButton,                    &CommandPushButton::sendCommand,
            WidgetHelper::placeCommand);

    connect(ui->buildSupermarketPushButton,             &CommandPushButton::sendCommand,
            WidgetHelper::placeCommand);

    connect(ui->buildVillaPushButton,                   &CommandPushButton::sendCommand,
            WidgetHelper::placeCommand);
    /* ---------------------------------------------------------------------------------------------- */

    /* ---------------------------------- Display Config -------------------------------------------- */
    connect(this,                                       &BuildingDetailDialog::dataChanged,
            this,                                       &BuildingDetailDialog::updateDisplay);
    /* ---------------------------------------------------------------------------------------------- */
}

void BuildingDetailDialog::setBuilding(Land *building) {
    this->building_ = building;

    ui->buyPushButton->setCommand(std::make_shared<TransactionCommand>(
        CompanyManager::instance().playerCompany(), 
        building->owner(),
        building));

    ui->sellPushButton->setCommand(std::make_shared<TransactionCommand>(
        &Government::instance(),
        building->owner(),
        building));

    ui->dismantlePushButton->setCommand(
        std::make_shared<DismantleBuilding>(building));

    ui->buildBankPushButton->setCommand(
        std::make_shared<BuildBank>(building));
    ui->buildFactoryPushButton->setCommand(
        std::make_shared<BuildFactory>(building));
    ui->buildFarmPushButton->setCommand(
        std::make_shared<BuildFarm>(building));
    ui->buildGaragePushButton->setCommand(
        std::make_shared<BuildGarage>(building));
    ui->buildMinePushButton->setCommand(
        std::make_shared<BuildMine>(building));
    ui->buildSupermarketPushButton->setCommand(
        std::make_shared<BuildSupermarket>(building));
    ui->buildVillaPushButton->setCommand(
        std::make_shared<BuildVilla>(building));
}