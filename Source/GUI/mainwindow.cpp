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

#include "mainwindow.h"

#include <QString>

#include "Source/Objects/government.h"

#include "Source/Managers/buildingmanager.h"
#include "Source/Managers/companymanager.h"
#include "Source/Managers/industrychainmanager.h"
#include "Source/Managers/mapmanager.h"
#include "Source/Managers/pricemanager.h"
#include "Source/Managers/timemanager.h"
#include "Source/Managers/uimanager.h"

#include "buildinginfowidget.h"
#include "mainui.h"
#include "ui_mainwindow.h"
#include "widgethelper.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    buildingDetailDialog_(nullptr),
    buildingInfoList_(new BuildingTableWidget),
    companyDetailDialog_(new CompanyDetailDialog),
    helpDialog_(new HelpDialog),
    ui(new Ui::MainWindow) {
    init();
}

MainWindow::~MainWindow() {
    delete helpDialog_;
    delete ui;
}

void MainWindow::init() {
    MapManager::instance().init();
    BuildingManager::instance().init();
    CompanyManager::instance().init();
    IndustryChainManager::instance().init();
    PriceManager::instance().init();
    TimeManager::instance().init();

    ui->setupUi(this);
    ui->userInterface->updateDisplay();

    playerCompany_ = CompanyManager::instance().playerCompany();

    buildingDetailDialog_ = UIManager::instance().buildingDetailDialog();

    signalSlotConfig();

    updateDisplay();
}

void MainWindow::redirectData(Land *newBuilding) {
    ui->buildingInfoWidget->setTarget(newBuilding);
    buildingDetailDialog_->setBuilding(newBuilding);
    emit dataChanged();
}

//void MainWindow::goBank() {
// BankDialog *bankDialog_ = UIManager::instance().bankDialog();
// bankDialog_->setClient(playerCompany_);
// bankDialog_->updateDisplay();
// if (bankDialog_->exec() == QDialog::Accepted) {
//     updateStatusBar("Back.");
//     emit dataChanged();
// }
//}

void MainWindow::endTurns() {
    BuildingManager::instance().update();
    CompanyManager::instance().update();
    Government::instance().update();

    TimeManager::instance().increaseTime();
    emit dataChanged();
}

void MainWindow::showBuildingTableWidget() {
    buildingInfoList_->show();
}

void MainWindow::showHelp() {
    helpDialog_->show();
}

void MainWindow::showCompanyDetail() {
    companyDetailDialog_->setCompany(playerCompany_);
    WidgetHelper::showUp(companyDetailDialog_);
    companyDetailDialog_->updateDisplay();
}

void MainWindow::getBuildingByPos(int x, int y) {
    Land *building = BuildingManager::instance().getByPos(x, y);
    emit sendSelectedBuilding(building);
}

void MainWindow::updateDisplay() {
    const QString &turnText = tr("Turn ") + QString::number(TimeManager::instance().currentTime());
    ui->label_Turns->setText(turnText);
    const QString &cashText = tr("Cash: $") + WidgetHelper::toString(playerCompany_->cash());
    ui->label_CompanyCash->setText(cashText);

    buildingInfoList_->updateDisplay();
}

void MainWindow::processCommand(ICommmand *command) {
	command->execute();
    //switch (command) {
    //case BuildBank: {
    //    Land *newBuilding = BuildingManager::instance().changeType(building, BANK);
    //    ui->buildingInfoWidget->setTarget(newBuilding);
    //    buildingDetailDialog_->setBuilding(newBuilding);
    //    emit dataChanged();
    //    break;
    //}

    //case BuildFactory: {
    //    Land *newBuilding = BuildingManager::instance().changeType(building, FACTORY);
    //    ui->buildingInfoWidget->setTarget(newBuilding);
    //    buildingDetailDialog_->setBuilding(newBuilding);
    //    emit dataChanged();
    //    break;
    //}

    //case BuildFarm: {
    //    Land *newBuilding = BuildingManager::instance().changeType(building, FARM);
    //    ui->buildingInfoWidget->setTarget(newBuilding);
    //    buildingDetailDialog_->setBuilding(newBuilding);
    //    emit dataChanged();
    //    break;
    //}


    //case BuildGarage: {
    //    Land *newBuilding = BuildingManager::instance().changeType(building, GARAGE);
    //    ui->buildingInfoWidget->setTarget(newBuilding);
    //    buildingDetailDialog_->setBuilding(newBuilding);
    //    emit dataChanged();
    //    break;
    //}

    //case BuildMine: {
    //    Land *newBuilding = BuildingManager::instance().changeType(building, MINE);
    //    ui->buildingInfoWidget->setTarget(newBuilding);
    //    buildingDetailDialog_->setBuilding(newBuilding);
    //    emit dataChanged();
    //    break;
    //}

    //case BuildSupermarket: {
    //    Land *newBuilding = BuildingManager::instance().changeType(building, SUPERMARKET);
    //    ui->buildingInfoWidget->setTarget(newBuilding);
    //    buildingDetailDialog_->setBuilding(newBuilding);
    //    emit dataChanged();
    //    break;
    //}

    //case BuildVilla: {
    //    Land *newBuilding = BuildingManager::instance().changeType(building, VILLA);
    //    ui->buildingInfoWidget->setTarget(newBuilding);
    //    buildingDetailDialog_->setBuilding(newBuilding);
    //    emit dataChanged();
    //    break;
    //}

    //case BuyBuilding:
    //    if (playerCompany_->phrchase(building)) {
    //        emit dataChanged();
    //        msg = QString("%1 %2 bought.").arg(building->type(), building->name());
    //    } else {
    //        msg = "Cannot Afford it.";
    //    }
    //    break;

    //case CloseAnAccount:
    //    break;

    //case Deposit:
    //    break;

    //case DismantleBuilding: {
    //    Land *newBuilding = BuildingManager::instance().changeType(building, UNUSED_LAND);
    //    ui->buildingInfoWidget->setTarget(newBuilding);
    //    buildingDetailDialog_->setBuilding(newBuilding);
    //    msg = newBuilding->name() + " has been dismantled.";
    //    emit dataChanged();
    //    break;
    //}

    //case Loan:
    //    break;

    //case OpenAnAccount:
    //    break;

    //case Repay:
    //    break;

    //case SellBuilding:
    //    playerCompany_->sell(building);
    //    emit dataChanged();
    //    msg = QString("%1 %2 sold.").arg(building->type(), building->name());
    //    break;

    //case ShowDetail:
    //    buildingDetailDialog_->setBuilding(building);
    //    WidgetHelper::showUp(buildingDetailDialog_);
    //    buildingDetailDialog_->updateDisplay();
    //    break;

    //case Withdraw:
    //    break;

    //default:
    //    break;
    //}
}

void MainWindow::updateStatusBar(const QString &msg) {
    ui->statusBar->showMessage(msg, 5000);
}

void MainWindow::signalSlotConfig() {
    /* ------------------------------ Main Functions Config ----------------------------------------- */
    connect(ui->buildingListPushButton, SIGNAL(clicked()),
            this,                       SLOT(showBuildingTableWidget()));
    connect(ui->companyPushButton,      SIGNAL(clicked()),
            this,                       SLOT(showCompanyDetail()));
    connect(ui->endTurnPushButton,      SIGNAL(clicked()),
            this,                       SLOT(endTurns()));
    connect(ui->helpPushButton,         SIGNAL(clicked()),
            this,                       SLOT(showHelp()));
    /* ---------------------------------------------------------------------------------------------- */

    /* ---------------------------------- Orders Config --------------------------------------------- */
    connect(ui->buildingInfoWidget,     SIGNAL(sendCommand(int, Land *)),
            this,                       SLOT(processCommand(int, Land *)));
    connect(buildingInfoList_,          SIGNAL(sendCommand(int, Land *)),
            this,                       SLOT(processCommand(int, Land *)));
    connect(buildingDetailDialog_,      SIGNAL(sendCommand(int, Land *)),
            this,                       SLOT(processCommand(int, Land *)));
    /* ---------------------------------------------------------------------------------------------- */

    /* ---------------------------------- Display Config -------------------------------------------- */
    connect(ui->userInterface,          SIGNAL(sendPosition(int, int)),    
            this,                       SLOT(getBuildingByPos(int, int)));
    connect(this,                       SIGNAL(sendSelectedBuilding(Land *)),
            ui->buildingInfoWidget,     SLOT(showBuildingInfo(Land *)));
    /* ---------------------------------------------------------------------------------------------- */

    /* ------------------------------- Update Display Config ---------------------------------------- */
    connect(this,                       SIGNAL(dataChanged()),
            this,                       SLOT(updateDisplay()));
    connect(this,                       SIGNAL(dataChanged()),
            ui->buildingInfoWidget,     SLOT(updateDisplay()));
    connect(this,                       SIGNAL(dataChanged()),
            buildingDetailDialog_,      SLOT(updateDisplay()));
    connect(this,                       SIGNAL(dataChanged()),
            companyDetailDialog_,       SLOT(updateDisplay()));
    connect(this,                       SIGNAL(dataChanged()),
            ui->userInterface,          SLOT(updateDisplay()));
    /* ---------------------------------------------------------------------------------------------- */
}
