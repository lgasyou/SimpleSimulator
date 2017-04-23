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

#ifndef BUILDINGMANAGER_H
#define BUILDINGMANAGER_H

#include <array>
#include <vector>
#include <QString>

#include "Source/Objects/land.h"
#include "Source/Objects/company.h"

#include "Source/gameconstants.h"

// Owns and manages the pointers of buildings.
// Updates the data of buildings.
class BuildingManager {
public:
    typedef std::array<std::array<Land *, gameconstants::mapWeight>, gameconstants::mapHeight> BuildingsArray;

    // Converts type of building from QString to enum.
    static gameconstants::StructureType stringToEnum(const QString &type);

    // Gets single instance.
    static BuildingManager &instance();

    void init();

    void add(gameconstants::StructureType);

    const std::vector<Land *> &buildings() const;

    // In order to get the balance of Company.
    double deltaValueOfCompanyProperties(Company *) const;

    // Shows the number of existed buildings.
    std::size_t buildingNumber() const;

    // The range of id is [0, buildingNumber() - 1).
    Land *getById(int id) const;

    Land *getByPos(int x, int y) const { return buildings_[x][y]; }

    // Gets building's pointer and type.
    // Returns a pointer which is arg "type" asked.
    // If arg "type" isn't a standard type, returns "Unused Land".
    Land *resetType(Land *, gameconstants::StructureType type);

    void update();

private:
    // Hides constructor and destructor.
    BuildingManager();

    // Deletes all pointers while destructing.
    ~BuildingManager();

private:
    BuildingsArray buildings_;

private:
    // Flag of whether buildings_ has been modified.
    mutable bool dataChanged_ = true;

};

#endif // BUILDINGMANAGER_H
