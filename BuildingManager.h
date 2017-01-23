#ifndef BUILDINGMANAGER_H
#define BUILDINGMANAGER_H

#include <QList>
#include "BuildingBase.h"

class BuildingManager {
public:
    BuildingManager();
    BuildingManager(int number);

    BuildingBase *getBuildingById(unsigned id);
    const int buildingNumber() const { return buildingList_.size(); }
    const double totalDeltaValue();

    BuildingBase *setItemType(BuildingBase *, const QString &);
    void manage(BuildingBase *, const QString &);

    void addItem(BuildingBase *);
    void removeItem(BuildingBase *);

    void update();

private:
    QList<BuildingBase *> buildingList_;
    double totalDeltaValue_;
};

#endif // BUILDINGMANAGER_H
