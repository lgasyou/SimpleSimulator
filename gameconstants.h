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
const int colOfBuildingInfo = numberOfPropertiesOfBuilding + optionsOfBuildingManager;

// about warehouses
const double defaultMaxVolOfWarehouse = 60.0;

const int integerMaximum = INT_MAX;
const int integerMinimum = INT_MIN;
}

#endif // !GAMECONSTANTS_H