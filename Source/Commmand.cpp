#include "Commmand.h"

#include "Managers/buildingmanager.h"
#include "Objects/land.h"
#include "GUI/BuildingDetailDialog.h"
#include "GUI/widgethelper.h"
#include "GUI/mainwindow.h"
#include "Managers/uimanager.h"

void BuildBank::execute() {
    auto newBuilding = BuildingManager::instance().changeType(building_, BANK);
    MainWindow::instance().redirectData(newBuilding);
}

void BuildFactory::execute() {
    auto newBuilding = BuildingManager::instance().changeType(building_, FACTORY);
    MainWindow::instance().redirectData(newBuilding);
}

void BuildFarm::execute() {
    auto newBuilding = BuildingManager::instance().changeType(building_, FARM);
    MainWindow::instance().redirectData(newBuilding);
}

void BuildGarage::execute() {
    auto newBuilding = BuildingManager::instance().changeType(building_, GARAGE);
    MainWindow::instance().redirectData(newBuilding);
}

void BuildMine::execute() {
    auto newBuilding = BuildingManager::instance().changeType(building_, MINE);
    MainWindow::instance().redirectData(newBuilding);
}

void BuildSupermarket::execute() {
    auto newBuilding = BuildingManager::instance().changeType(building_, SUPERMARKET);
    MainWindow::instance().redirectData(newBuilding);
}

void BuildVilla::execute() {
    auto newBuilding = BuildingManager::instance().changeType(building_, VILLA);
    MainWindow::instance().redirectData(newBuilding);
}

void DismantleBuilding::execute() {
    auto newBuilding = BuildingManager::instance().changeType(building_, UNUSED_LAND);
    MainWindow::instance().redirectData(newBuilding);
}

void TransactionCommand::execute() {
    double objectValue = object_->value();
    firstParty_->setCash(firstParty_->cash() - objectValue);
    secondParty_->setCash(secondParty_->cash() + objectValue);
    object_->setOwner(firstParty_); 
    MainWindow::instance().setDirty();
}

void ShowDetailCommand::execute() {
    auto dlg = UIManager<BuildingDetailDialog>::get();
    dlg->setBuilding(object_);
    WidgetHelper::showUp(dlg);
    dlg->updateDisplay();
}
