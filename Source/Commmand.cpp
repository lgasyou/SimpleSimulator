#include "Commmand.h"
#include "Managers/buildingmanager.h"

void CommandInvoker::takeCommand(ICommmand *command) {
	commmandList_.push_back(command);
}

void CommandInvoker::placeCommands() {
	for(auto command : commmandList_) {
		command->execute();
	}
	commmandList_.clear();
}

void BuildBank::execute() {
    auto newBuilding = BuildingManager::instance().changeType(building_, BANK);
    mainWindow_->redirectData(newBuilding);
}

void BuildFactory::execute() {
    auto newBuilding = BuildingManager::instance().changeType(building_, FACTORY);
    mainWindow_->redirectData(newBuilding);
}

void BuildFarm::execute() {
    auto newBuilding = BuildingManager::instance().changeType(building_, FARM);
    mainWindow_->redirectData(newBuilding);
}

void BuildGarage::execute() {
    auto newBuilding = BuildingManager::instance().changeType(building_, GARAGE);
    mainWindow_->redirectData(newBuilding);
}

void BuildMine::execute() {
    auto newBuilding = BuildingManager::instance().changeType(building_, MINE);
    mainWindow_->redirectData(newBuilding);
}

void BuildSupermarket::execute() {
    auto newBuilding = BuildingManager::instance().changeType(building_, SUPERMARKET);
    mainWindow_->redirectData(newBuilding);
}

void BuildVilla::execute() {
    auto newBuilding = BuildingManager::instance().changeType(building_, VILLA);
    mainWindow_->redirectData(newBuilding);
}

void DismantleBuilding::execute() {
    auto newBuilding = BuildingManager::instance().changeType(building_, UNUSED_LAND);
    mainWindow_->redirectData(newBuilding);
}

void TransactionCommand::execute() {
    double objectValue = object_->value();
    firstParty_->setCash(firstParty_->cash() - objectValue);
    secondParty_->setCash(secondParty_->cash() + objectValue);
    object_->setOwner(firstParty_);
}

void ShowDetailCommand::execute() {

}
