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

#include "Source/Objects/government.h"

#include "Source/Managers/buildingmanager.h"
#include "Source/Managers/companymanager.h"
#include "Source/Managers/mapmanager.h"
#include "Source/Managers/timemanager.h"
#include "Source/Managers/uimanager.h"

#include "mainui.h"
#include "ui_mainwindow.h"
#include "buildingdetaildialog.h"
#include "helpdialog.h"
#include "companydetaildialog.h"
#include "buildingtablewidget.h"
#include "widgethelper.h"

MainWindow &MainWindow::instance() {
    static MainWindow mainWindow;
    return mainWindow;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
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

void MainWindow::redirectData(Land *object) {
    ui->buildingInfoWidget->setTarget(object);
    dynamic_cast<BuildingDetailDialog *>(UIManager::get("BuildingDetailDialog"))->setBuilding(object);
    emit dataChanged();
}

void MainWindow::setDirty() {
    emit dataChanged();
}

void MainWindow::endTurns() {
    BuildingManager::instance().update();
    CompanyManager::instance().update();
    Government::instance().update();

    TimeManager::instance().increaseTime();
    emit dataChanged();
}

void MainWindow::showBuildingTableWidget() {
    dynamic_cast<BuildingTableWidget *>(UIManager::get("BuildingTableWidget"))->show();
}

void MainWindow::showHelp() {
    dynamic_cast<HelpDialog *>(UIManager::get("HelpDialog"))->show();
}

void MainWindow::showCompanyDetail() const {
    CompanyDetailDialog *dialog = dynamic_cast<CompanyDetailDialog *>(UIManager::get("CompanyDetailDialog"));
    dialog->setCompany(playerCompany_);
    WidgetHelper::showUp(dialog);
    dialog->updateDisplay();
}

void MainWindow::getBuildingByPos(int x, int y) {
    auto building = BuildingManager::instance().getByPos(x, y);
    emit sendSelectedBuilding(building);
}

void MainWindow::updateDisplay() const {
    const QString &turnText = tr("Turn ") + QString::number(TimeManager::instance().currentTime());
    ui->label_Turns->setText(turnText);
    const QString &cashText = tr("Cash: $") + WidgetHelper::toString(playerCompany_->cash());
    ui->label_CompanyCash->setText(cashText);

    dynamic_cast<BuildingTableWidget *>(UIManager::get("BuildingTableWidget"))->updateDisplay();
}

void MainWindow::signalSlotConfig() {
    /* ------------------------------ Main Functions Config ----------------------------------------- */
    connect(ui->buildingListPushButton, &QPushButton::clicked,
            this,                        &MainWindow::showBuildingTableWidget);
    connect(ui->companyPushButton,        &QPushButton::clicked,
            this,                       &MainWindow::showCompanyDetail);
    connect(ui->endTurnPushButton,        &QPushButton::clicked,
            this,                       &MainWindow::endTurns);
    connect(ui->helpPushButton,            &QPushButton::clicked,
            this,                       &MainWindow::showHelp);
    /* ---------------------------------------------------------------------------------------------- */

    /* ---------------------------------- Display Config -------------------------------------------- */
    connect(ui->userInterface,          &MainUI::sendPosition,    
            this,                       &MainWindow::getBuildingByPos);
    connect(this,                       &MainWindow::sendSelectedBuilding,
            ui->buildingInfoWidget,     &BuildingInfoWidget::showBuildingInfo);
    /* ---------------------------------------------------------------------------------------------- */

    /* ------------------------------- Update Display Config ---------------------------------------- */
    connect(this,                       SIGNAL(dataChanged()),
            this,                       SLOT(updateDisplay()));
    connect(this,                       SIGNAL(dataChanged()),
            ui->buildingInfoWidget,     SLOT(updateDisplay()));
    //connect(this,                       SIGNAL(dataChanged()),
    //        buildingDetailDialog_,      SLOT(updateDisplay()));
    //connect(this,                       SIGNAL(dataChanged()),
    //        companyDetailDialog_,       SLOT(updateDisplay()));
    connect(this,                       SIGNAL(dataChanged()),
            ui->userInterface,          SLOT(updateDisplay()));
    /* ---------------------------------------------------------------------------------------------- */
}
