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

#include "buildingdetaildialog.h"

#include "Source/Objects/land.h"
#include "Source/Objects/baseindustry.h"
#include "Source/Objects/company.h"
#include "Source/Objects/garage.h"
#include "Source/Objects/goods.h"
#include "Source/Objects/machine.h"
#include "Source/Objects/mine.h"
#include "Source/Commmand.h"

#include "Source/gameconstants.h"
#include "Source/defaultmachinebuilder.h"

#include "Source/Managers/buildingmanager.h"
#include "Source/Managers/companymanager.h"
#include "Source/Managers/machinemanager.h"

#include "garagetablewidget.h"
#include "ui_buildingdetaildialog.h"
#include "widgethelper.h"

BuildingDetailDialog::BuildingDetailDialog(QWidget *parent) :
    QDialog(parent),
    building_(nullptr),
    selectMachine_(nullptr),
    ui(new Ui::BuildingDetailDialog)
{
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
        updateMachineDetail(selectMachine_);
    }

    displayAccordingToBuildingType();
}

void BuildingDetailDialog::closeEvent(QCloseEvent *) {
    ui->expandStackedWidget->hide();
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
    selectMachine_->setCurrentProduct(product);
    emit dataChanged();
}

void BuildingDetailDialog::showMachineDetail(Machine *machine) {
    ui->expandStackedWidget->show();
    selectMachine_ = machine;

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
    using namespace gameconstants;

    /* ---------------------------------- Basic Config ---------------------------------------------- */
    connect(ui->buyPushButton,                          SIGNAL(sendCommand(int)),
            this,                                       SLOT(receiveCommand(int)));
    ui->buyPushButton->setCommand(BUY_BUILDING);

    connect(ui->sellPushButton,                         SIGNAL(sendCommand(int)),
            this,                                       SLOT(receiveCommand(int)));
    ui->sellPushButton->setCommand(SELL_BUILDING);

    connect(ui->dismantlePushButton,                    SIGNAL(sendCommand(int)),
            this,                                       SLOT(receiveCommand(int)));
    ui->dismantlePushButton->setCommand(DISMANTLE_BUILDING);
    /* ---------------------------------------------------------------------------------------------- */

    /* ----------------------------------- Bank Config ---------------------------------------------- */
    connect(ui->closeAnAccountPushButton,               SIGNAL(sendCommand(int)),
            this,                                       SLOT(receiveCommand(int)));
    ui->closeAnAccountPushButton->setCommand(CLOSE_AN_ACCOUNT);

    connect(ui->depositPushButton,                      SIGNAL(sendCommand(int)),
            this,                                       SLOT(receiveCommand(int)));
    ui->depositPushButton->setCommand(DEPOSIT);

    connect(ui->loanPushButton,                         SIGNAL(sendCommand(int)),
            this,                                       SLOT(receiveCommand(int)));
    ui->loanPushButton->setCommand(LOAN);

    connect(ui->openAnAccountPushButton,                SIGNAL(sendCommand(int)),
            this,                                       SLOT(receiveCommand(int)));
    ui->openAnAccountPushButton->setCommand(OPEN_AN_ACCOUNT);

    connect(ui->repayPushButton,                        SIGNAL(sendCommand(int)),
            this,                                       SLOT(receiveCommand(int)));
    ui->repayPushButton->setCommand(REPAY);

    connect(ui->withdrawPushButton,                     SIGNAL(sendCommand(int)),
            this,                                       SLOT(receiveCommand(int)));
    ui->withdrawPushButton->setCommand(WITHDRAW);
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
    connect(ui->buildBankPushButton,                    SIGNAL(sendCommand(int)),
            this,                                       SLOT(receiveCommand(int)));
    ui->buildBankPushButton->setCommand(Commands::BuildBank);

    connect(ui->buildFactoryPushButton,                 SIGNAL(sendCommand(int)),
            this,                                       SLOT(receiveCommand(int)));
    ui->buildFactoryPushButton->setCommand(Commands::BuildFactory);

    connect(ui->buildFarmPushButton,                    SIGNAL(sendCommand(int)),
            this,                                       SLOT(receiveCommand(int)));
    ui->buildFarmPushButton->setCommand(Commands::BuildFarm);

    connect(ui->buildGaragePushButton,                  SIGNAL(sendCommand(int)),
            this,                                       SLOT(receiveCommand(int)));
    ui->buildGaragePushButton->setCommand(Commands::BuildGarage);

    connect(ui->buildMinePushButton,                    SIGNAL(sendCommand(int)),
            this,                                       SLOT(receiveCommand(int)));
    ui->buildMinePushButton->setCommand(Commands::BuildMine);

    connect(ui->buildSupermarketPushButton,             SIGNAL(sendCommand(int)),
            this,                                       SLOT(receiveCommand(int)));
    ui->buildSupermarketPushButton->setCommand(Commands::BuildSupermarket);

    connect(ui->buildVillaPushButton,                   SIGNAL(sendCommand(int)),
            this,                                       SLOT(receiveCommand(int)));
    ui->buildVillaPushButton->setCommand(Commands::BuildVilla);
    /* ---------------------------------------------------------------------------------------------- */

    /* ---------------------------------- Display Config -------------------------------------------- */
    connect(this,                                       SIGNAL(dataChanged()),
            this,                                       SLOT(updateDisplay()));
    /* ---------------------------------------------------------------------------------------------- */
}
