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

#include "LandParcelDetailDlg.h"

#include "Source/Objects/LandParcel.h"
#include "Source/Objects/Industry.h"
#include "Source/Objects/Company.h"
#include "Source/Objects/Garage.h"
#include "Source/Objects/Goods.h"
#include "Source/Objects/Government.h"
#include "Source/Objects/Machine.h"
#include "Source/Objects/Mine.h"
#include "Source/Commmands.h"

#include "Source/MachineBuilders.h"

#include "Source/Managers/LandParcelManager.h"
#include "Source/Managers/CompanyManager.h"
#include "Source/Managers/MachineManager.h"

#include "ui_LandParcelDetailDlg.h"
#include "WidgetHelper.h"

LandParcelDetailDlg::LandParcelDetailDlg(LandParcel *object, QWidget *parent)
    : QDialog(parent),
      building_(object),
      ui(new Ui::LandParcelDetailDlg) {
    ui->setupUi(this);

    signalSlotConfig();

    ui->expandStackedWidget->hide();
}

LandParcelDetailDlg::~LandParcelDetailDlg() {
    delete ui;
}

void LandParcelDetailDlg::updateDisplay() {
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

void LandParcelDetailDlg::closeEvent(QCloseEvent *) {

}

//void LandParcelDetailDlg::deliverGoods(const Goods &goods, Industry *dest) {
// Industry *industry = dynamic_cast<Industry *>(building_);
// industry->deliverGoods(goods, dest);
// emit dataChanged();
//}

void LandParcelDetailDlg::addNewMachine() {
    if (Industry *industry = dynamic_cast<Industry *>(building_)) {
        MachineBuilder *builder = new DefaultMachineBuilder;
        Machine *machine = MachineManager::instance().machine(builder);
        machine->setWarehouse(industry->warehouse());
        industry->addMachine(machine);
        delete builder;

        emit dataChanged();
    }
}

void LandParcelDetailDlg::addNewVihicle() {
    if (Garage *garage = dynamic_cast<Garage *>(building_)) {
        garage->addNewVihicle("Truck");
        emit dataChanged();
    }
}

void LandParcelDetailDlg::setNextMachineProduct(const QString &product) {
    selectedMachine_->setCurrentProduct(product);
    emit dataChanged();
}

void LandParcelDetailDlg::showMachineDetail(Machine *machine) {
    ui->expandStackedWidget->show();
    selectedMachine_ = machine;

    ui->selectNextProductComboBox->clear();
    for (const auto &product : machine->products()) {
        ui->selectNextProductComboBox->addItem(product.label);
    }

    updateMachineDetail(machine);
}

void LandParcelDetailDlg::updateMachineDetail(Machine *machine) {
    const QString &machineCurrentProductivity = WidgetHelper::toString(machine->currentProductivity());
    ui->machineCurrentProductivity->setText("Current Productivity: " + machineCurrentProductivity);

    const QString &machineMaximumProductivity = WidgetHelper::toString(machine->maximalProductivity());
    ui->machineMaximumProductivity->setText("Maximum Productivity: " + machineMaximumProductivity);
}

void LandParcelDetailDlg::receiveCommand(int command) {
    emit sendCommand(command, building_);
    emit dataChanged();
}

void LandParcelDetailDlg::displayAccordingToBuildingType() {
    bool isVisitorOwner = (building_->owner() == CompanyManager::instance().playerCompany());
    ui->basicOperationStackedWidget->setCurrentIndex(isVisitorOwner);

    const QString &type = building_->type();
    auto buildingType = LandParcelManager::stringToEnum(type);
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

void LandParcelDetailDlg::signalSlotConfig() {
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
    connect(this,                                       &LandParcelDetailDlg::dataChanged,
            this,                                       &LandParcelDetailDlg::updateDisplay);
    /* ---------------------------------------------------------------------------------------------- */
}

void LandParcelDetailDlg::setBuilding(LandParcel *building) {
    this->building_ = building;

    ui->buyPushButton->setCommand(std::make_shared<TransactionCommand>(
        this,
        CompanyManager::instance().playerCompany(), 
        building->owner(),
        building));

    ui->sellPushButton->setCommand(std::make_shared<TransactionCommand>(
        this,
        &Government::instance(),
        building->owner(),
        building));

    ui->dismantlePushButton->setCommand(
        std::make_shared<DismantleBuilding>(this, building));

    ui->buildBankPushButton->setCommand(
        std::make_shared<BuildBank>(this, building));
    ui->buildFactoryPushButton->setCommand(
        std::make_shared<BuildFactory>(this, building));
    ui->buildFarmPushButton->setCommand(
        std::make_shared<BuildFarm>(this, building));
    ui->buildGaragePushButton->setCommand(
        std::make_shared<BuildGarage>(this, building));
    ui->buildMinePushButton->setCommand(
        std::make_shared<BuildMine>(this, building));
    ui->buildSupermarketPushButton->setCommand(
        std::make_shared<BuildSupermarket>(this, building));
    ui->buildVillaPushButton->setCommand(
        std::make_shared<BuildVilla>(this, building));
}