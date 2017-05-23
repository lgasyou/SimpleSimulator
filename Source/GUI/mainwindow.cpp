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

#include "MainWindow.h"

#include "Source/Objects/Government.h"

#include "Source/Managers/LandParcelManager.h"
#include "Source/Managers/CompanyManager.h"
#include "Source/Managers/MapManager.h"
#include "Source/Managers/TimeManager.h"
#include "Source/Managers/UIManager.h"

#include "MapUi.h"
#include "ui_mainwindow.h"
#include "LandParcelDetailDlg.h"
#include "HelpDialog.h"
#include "BuildingTableWidget.h"
#include "CompanyDetailDialog.h"
#include "WidgetHelper.h"

MainWindow &MainWindow::instance() {
    static MainWindow mainWindow;
    return mainWindow;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::init() {
    playerCompany_ = CompanyManager::instance().playerCompany();

    signalSlotConfig();
    updateDisplay();
    ui->userInterface->updateDisplay();
}

void MainWindow::redirectData(LandParcel *object) {
    ui->buildingInfoWidget->setTarget(object);
    UIManager<LandParcelDetailDlg>::get()->setBuilding(object);
}

void MainWindow::endTurns() {
    LandParcelManager::instance().update();
    CompanyManager::instance().update();
    Government::instance().update();

    TimeManager::instance().increaseTime();
}

void MainWindow::showBuildingTableWidget() {
    UIManager<BuildingTableWidget>::get()->show();
}

void MainWindow::showHelp() {
    UIManager<HelpDialog>::get()->show();
}

void MainWindow::showCompanyDetail() const {
    auto dialog = UIManager<CompanyDetailDialog>::get();
    dialog->setCompany(playerCompany_);
    WidgetHelper::showUp(dialog);
    dialog->updateDisplay();
}

void MainWindow::getBuildingByPos(int x, int y) {
    auto building = LandParcelManager::instance().getByPos(x, y);
    emit sendSelectedBuilding(building);
}

void MainWindow::updateDisplay() const {
    auto &turnText = tr("Turn ") + QString::number(TimeManager::instance().currentTime());
    ui->label_Turns->setText(turnText);
    auto &cashText = tr("Cash: $") + WidgetHelper::toString(playerCompany_->cash());
    ui->label_CompanyCash->setText(cashText);
}

void MainWindow::signalSlotConfig() {
    /* ------------------------------ Main Functions Config ----------------------------------------- */
    connect(ui->buildingListPushButton, &QPushButton::clicked,
            this,                       &MainWindow::showBuildingTableWidget);
    connect(ui->companyPushButton,      &QPushButton::clicked,
            this,                       &MainWindow::showCompanyDetail);
    connect(ui->endTurnPushButton,      &QPushButton::clicked,
            this,                       &MainWindow::endTurns);
    connect(ui->helpPushButton,         &QPushButton::clicked,
            this,                       &MainWindow::showHelp);
    /* ---------------------------------------------------------------------------------------------- */

    /* ---------------------------------- Display Config -------------------------------------------- */
    connect(ui->userInterface,          &MapUi::sendPosition,    
            this,                       &MainWindow::getBuildingByPos);
    connect(this,                       &MainWindow::sendSelectedBuilding,
            ui->buildingInfoWidget,     &BuildingInfoWidget::showBuildingInfo);
    /* ---------------------------------------------------------------------------------------------- */
}
