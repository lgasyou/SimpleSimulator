#ifndef BUILDINGMANAGER_H
#define BUILDINGMANAGER_H

#include <vector>
#include "gameconstants.h"

class BaseBuilding;
class Company;

class QString;

// Owns and manages the pointers of buildings.
// Updates the data of buildings.
class BuildingManager {
public:
	// Converts type of building from QString to enum.
	static GameConstants::BuildingTypes stringToEnum(const QString &type);

	// Use singleton pattern.
	static BuildingManager &instance();

	void init();

	void addItem(BaseBuilding *);

	void addItem(GameConstants::BuildingTypes);

	const std::vector<BaseBuilding *> &buildingList() const { return this->buildings_; }

	std::size_t buildingNumber() const { return buildings_.size(); }

	// In order to get the balance of Company.
	double deltaValueOfCompanyProperties(Company *) const;

	BaseBuilding *getBuildingById(int id) const;

	BaseBuilding *getBuildingByPos(int x, int y) const;

	int indexOf(BaseBuilding *) const;

	void removeItem(BaseBuilding *);

	// Gets building's pointer and type.
	// Returns a pointer which is arg "type" asked.
	// If arg "type" isn't a standard type, returns "Unused Land".
    BaseBuilding *resetItemType(BaseBuilding *, GameConstants::BuildingTypes);

    void update();

private:
	// Hide constructor and destructor.
    BuildingManager();

	~BuildingManager();

	BuildingManager(const BuildingManager &) = delete;

	BuildingManager &operator=(const BuildingManager &) = delete;

	std::vector<BaseBuilding *>::iterator iteratorOf(BaseBuilding *);

private:
    std::vector<BaseBuilding *> buildings_;
};

inline BaseBuilding *BuildingManager::getBuildingById(int id) const {
	return buildings_.at(id);
}

#endif // BUILDINGMANAGER_H
