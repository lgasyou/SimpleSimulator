#ifndef BUILDINGFACTORY_H
#define BUILDINGFACTORY_H

class BaseBuilding;
class QString;

class BuildingFactory {
public:
	// Creates a new object and allocates a location to it.
	BaseBuilding *create(const QString &type);
};

#endif // !BUILDINGFACTORY_H
