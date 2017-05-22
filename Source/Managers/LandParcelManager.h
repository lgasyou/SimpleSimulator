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

#ifndef LAND_PARCEL_MANAGER_H
#define LAND_PARCEL_MANAGER_H

#include <array>
#include <vector>

#include "Source/Objects/LandParcel.h"
#include "Source/Objects/Company.h"

#include "Source/GameConstants.h"

// Owns and manages the pointers of LandParcel.
// Updates the data of LandParcel.
class LandParcelManager {
public:
    typedef std::array<std::array<LandParcel *, gameconstants::mapWeight>, gameconstants::mapHeight> ParcelArray;

    // Converts type of building from QString to enum.
    static StructureType stringToEnum(const QString &type);

    // Gets single instance.
    static LandParcelManager &instance();

    void init();

    void add(StructureType);

    const std::vector<LandParcel *> &buildings() const;

    // In order to get the balance of Company.
    double deltaValueOfCompanyProperties(Company *) const;

    // Shows the number of existed buildings.
    std::size_t buildingNumber() const;

    // The range of id is [0, buildingNumber() - 1).
    LandParcel *getById(int id) const;

    LandParcel *getByPos(int x, int y) const { return buildings_[x][y]; }

    // Gets building's pointer and type.
    // Returns a pointer which is arg "type" asked.
    // If arg "type" isn't a standard type, returns "Unused Land".
    LandParcel *changeType(LandParcel *, StructureType type);

    void update();

private:
    // Hides constructor and destructor.
    LandParcelManager();

    // Deletes all pointers while destructing.
    ~LandParcelManager();

private:
    ParcelArray buildings_;

private:
    // Detects whether buildings_ has been modified.
    mutable bool dataChanged_ = true;

};

#endif // !LAND_PARCEL_MANAGER_H
