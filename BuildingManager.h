#ifndef BUILDINGMANAGER_H
#define BUILDINGMANAGER_H

#include <QList>
#include "BaseBuilding.h"

class BuildingManager {
public:
    BuildingManager();
    BuildingManager(int number);

    BaseBuilding *getBuildingById(unsigned id);
    const int buildingNumber() const { return buildingList_.size(); }
    const double totalDeltaValue();

    BaseBuilding *setItemType(BaseBuilding *, const QString &);
    void manage(BaseBuilding *, const QString &);

    void addItem(BaseBuilding *);
    void removeItem(BaseBuilding *);

    void update();

private:
    QList<BaseBuilding *> buildingList_;
    double totalDeltaValue_;
};

#endif // BUILDINGMANAGER_H
