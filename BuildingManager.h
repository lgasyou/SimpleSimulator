#ifndef BUILDINGMANAGER_H
#define BUILDINGMANAGER_H

#include <QList>
#include "BuildingBase.h"

class Company;

class BuildingManager {
public:
    BuildingManager();

    BuildingBase *getBuildingById(unsigned id);
    const int buildingNumber() const { return buildingList_.size(); }
    const double deltaValueOfCompanyProperties(Company *);

    BuildingBase *resetItemType(BuildingBase *, const QString &);
    void manage(BuildingBase *, const QString &);

    void addItem(BuildingBase *);
    void removeItem(BuildingBase *);

    void update();

	inline const QList<BuildingBase *> &buildingList() const { return this->buildingList_; }

private:
	QList<BuildingBase *>::iterator iteratorOf(BuildingBase *);

    QList<BuildingBase *> buildingList_;
};

#endif // BUILDINGMANAGER_H
