#ifndef GAMECONSTANTS_H
#define GAMECONSTANTS_H

namespace GameConstants {
// about buildings
const double defaultBaseValueOfBuilding = 500.0;
const double sigmaOfdefaultBaseValueOfBuilding = 25.0;
const double minBaseValueOfBuilding = 20.0;
const int numberOfPropertiesOfBuilding = 4;
const int optionsOfBuildingManager = 2;
const int colOfBuildingInfoTableWidget = numberOfPropertiesOfBuilding + optionsOfBuildingManager;

// about warehouses
const double defaultMaxVolOfWarehouse = 60.0;
}


#endif // !GAMECONSTANTS_H