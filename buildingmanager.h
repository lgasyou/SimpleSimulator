#ifndef BUILDINGMANAGER_H
#define BUILDINGMANAGER_H

#include <vector>

class BaseBuilding;
class Company;

class QString;

// Owns and manages the pointers of buildings.
// Updates the data of buildings.
class BuildingManager {
public:
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

	// Converts type of building from QString to enum.
	static BuildingTypes stringToEnum(const QString &type);

	// Use singleton pattern.
	static BuildingManager &instance();

	void init();

	void addItem(BaseBuilding *);

	inline const auto &buildingList() const { return this->buildings_; }

	inline size_t buildingNumber() const { return buildings_.size(); }

	// In order to get the balance of Company.
	double deltaValueOfCompanyProperties(Company *) const;

	inline BaseBuilding *getBuildingById(size_t id) const;

	BaseBuilding *getBuildingByPos(int x, int y) const;

	int indexOf(BaseBuilding *) const;

	void removeItem(BaseBuilding *);

	// Gets building's pointer and type.
	// Returns a pointer which is arg "type" asked.
	// If arg "type" isn't a standard type, returns "Unused Land".
    BaseBuilding *resetItemType(BaseBuilding *building, const QString &type);

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

inline BaseBuilding *BuildingManager::getBuildingById(size_t id) const {
	return buildings_[id];
}

#endif // BUILDINGMANAGER_H
