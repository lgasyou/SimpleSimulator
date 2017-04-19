/*
 *	Copyright 2017 Li Zeqing
 *
 *	This file is part of World Simulator.
 *	
 *	World Simulator is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU Lesser General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *	
 *	World Simulator is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *	
 *	You should have received a copy of the GNU Lesser General Public License
 *	along with World Simulator.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BUILDINGMANAGER_H
#define BUILDINGMANAGER_H

#include <vector>

class BaseBuilding;
class Company;

class QString;

namespace GameConstants {
enum BuildingTypes : int;
}

// Owns and manages the pointers of buildings.
// Updates the data of buildings.
class BuildingManager {
public:
	// Converts type of building from QString to enum.
	static GameConstants::BuildingTypes stringToEnum(const QString &type);

	// Use singleton pattern.
	static BuildingManager &instance();

	void init();

	void add(BaseBuilding *);

	void add(GameConstants::BuildingTypes);

	void remove(BaseBuilding *);

	const std::vector<BaseBuilding *> &buildings() const { return buildings_; }

	std::size_t buildingNumber() const { return buildings_.size(); }

	// In order to get the balance of Company.
	double deltaValueOfCompanyProperties(Company *) const;

	BaseBuilding *getById(int id) const;

	BaseBuilding *getByPos(int x, int y) const;

	int indexOf(BaseBuilding *) const;

	// Gets building's pointer and type.
	// Returns a pointer which is arg "type" asked.
	// If arg "type" isn't a standard type, returns "Unused Land".
    BaseBuilding *resetType(BaseBuilding *, GameConstants::BuildingTypes type);

    void update();

private:
	// Hide constructor and destructor.
    BuildingManager();

	// Delete all pointers while destructing.
	~BuildingManager();

private:
    std::vector<BaseBuilding *> buildings_;
};

inline BaseBuilding *BuildingManager::getById(int id) const {
	return buildings_.at(id);
}

#endif // BUILDINGMANAGER_H
