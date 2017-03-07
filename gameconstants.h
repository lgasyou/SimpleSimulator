#ifndef GAMECONSTANTS_H
#define GAMECONSTANTS_H

#include <cstdlib>

// TODO:
// Move all those into a file.
namespace GameConstants {
// about buildings
const double defaultBaseValueOfBuilding = 50.0;
const double sigmaOfdefaultBaseValueOfBuilding = 25.0;
const double minBaseValueOfBuilding = 20.0;
const int numberOfPropertiesOfBuilding = 4;
const int optionsOfBuildingManager = 2;
const int colOfBuildingTableWidget = numberOfPropertiesOfBuilding + optionsOfBuildingManager;

// about warehouses
const double defaultMaxVolOfWarehouse = 60.0;

const int integerMaximum = INT_MAX;
const int integerMinimum = INT_MIN;

enum BuildingTypes {
	Bank,
	Factory,
	Farm,
	Garage,
	Mine,
	Supermarket,
	UnusedLand,
	Villa
};

enum Commands {
	BuildBank,
	BuildFactory,
	BuildFarm,
	BuildGarage,
	BuildMine,
	BuildSupermarket,
	BuildVilla,
	BuyBuilding,
	CloseAnAccount,
	Deposit,
	DismantleBuilding,
	Loan,
	OpenAnAccount,
	Repay,
	SellBuilding,
	ShowDetail,
	Withdraw,
};

}

#endif // !GAMECONSTANTS_H