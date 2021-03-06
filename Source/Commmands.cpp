﻿#include "Commmands.h"

#include "Managers/LandParcelManager.h"
#include "Objects/LandParcel.h"
#include "GUI/LandParcelDetailDlg.h"
#include "GUI/WidgetHelper.h"
#include "GUI/MainWindow.h"
#include "Managers/UIManager.h"

std::unordered_set<QWidget *> WriteCommand::cachedWidgets_;

void WriteCommand::execute() {
    for (auto widget : cachedWidgets_) {
        // TODO: change this into updateDisplay rather than update().
    }
}

void BuildBank::execute() {
    auto newBuilding = LandParcelManager::instance().changeType(building_, BANK);
    MainWindow::instance().redirectData(newBuilding);
    WriteCommand::execute();
}

void BuildFactory::execute() {
    auto newBuilding = LandParcelManager::instance().changeType(building_, FACTORY);
    MainWindow::instance().redirectData(newBuilding);
    WriteCommand::execute();
}

void BuildFarm::execute() {
    auto newBuilding = LandParcelManager::instance().changeType(building_, FARM);
    MainWindow::instance().redirectData(newBuilding);
    WriteCommand::execute();
}

void BuildGarage::execute() {
    auto newBuilding = LandParcelManager::instance().changeType(building_, GARAGE);
    MainWindow::instance().redirectData(newBuilding);
    WriteCommand::execute();
}

void BuildMine::execute() {
    auto newBuilding = LandParcelManager::instance().changeType(building_, MINE);
    MainWindow::instance().redirectData(newBuilding);
    WriteCommand::execute();
}

void BuildSupermarket::execute() {
    auto newBuilding = LandParcelManager::instance().changeType(building_, SUPERMARKET);
    MainWindow::instance().redirectData(newBuilding);
    WriteCommand::execute();
}

void BuildVilla::execute() {
    auto newBuilding = LandParcelManager::instance().changeType(building_, VILLA);
    MainWindow::instance().redirectData(newBuilding);
    WriteCommand::execute();
}

void DismantleBuilding::execute() {
    auto newBuilding = LandParcelManager::instance().changeType(building_, UNUSED_LAND);
    MainWindow::instance().redirectData(newBuilding);
    WriteCommand::execute();
}

void TransactionCommand::execute() {
    double objectValue = object_->value();
    firstParty_->setCash(firstParty_->cash() - objectValue);
    secondParty_->setCash(secondParty_->cash() + objectValue);
    object_->setOwner(firstParty_); 
    WriteCommand::execute();
}

void ShowDetailCommand::execute() {
    auto dlg = UIManager<LandParcelDetailDlg>::get();
    dlg->setBuilding(object_);
    WidgetHelper::showUp(dlg);
    dlg->updateDisplay();
}
