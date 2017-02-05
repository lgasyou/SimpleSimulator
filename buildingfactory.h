#ifndef BUILDINGFACTORY_H
#define BUILDINGFACTORY_H

class BaseBuilding;
class QString;

class BuildingFactory {
public:
	BaseBuilding *create(const QString &type);
};

#endif // !BUILDINGFACTORY_H
