#ifndef BUILDINGMANAGER_H
#define BUILDINGMANAGER_H

#include <QList>

class BaseBuilding;
class Company;

// Owns and manages the pointers of buildings.
// Updates the data of buildings.
class BuildingManager {
public:
	static BuildingManager &instance();

    BaseBuilding *getBuildingById(unsigned id);

    inline const int buildingNumber() const { return buildingList_.size(); }

	// In order to get the balance of Company.
    const double deltaValueOfCompanyProperties(Company *) const;

    BaseBuilding *resetItemType(BaseBuilding *, const QString &);

    void addItem(BaseBuilding *);
    void removeItem(BaseBuilding *);

    void update();

	inline const QList<BaseBuilding *> &buildingList() const { return this->buildingList_; }

private:
    BuildingManager();
	~BuildingManager();
	BuildingManager(const BuildingManager &) = delete;
	BuildingManager &operator=(const BuildingManager &) = delete;

	QList<BaseBuilding *>::iterator iteratorOf(BaseBuilding *);

    QList<BaseBuilding *> buildingList_;
};

#endif // BUILDINGMANAGER_H
