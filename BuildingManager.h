#ifndef BUILDINGMANAGER_H
#define BUILDINGMANAGER_H

class Company;
#include <QList>
#include "BuildingBase.h"

class BuildingManager {
public:
    BuildingManager();

    BuildingBase *getBuildingById(unsigned id);
    const int buildingNumber() const { return buildingList_.size(); }
    const double deltaValueOfCompanyProperties(Company *);

    BuildingBase *setItemType(BuildingBase *, const QString &);
    void manage(BuildingBase *, const QString &);

    void addItem(BuildingBase *);
    void removeItem(BuildingBase *);

    void update();

private:
    QList<BuildingBase *> buildingList_;
};

#endif // BUILDINGMANAGER_H
