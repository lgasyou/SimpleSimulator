#ifndef BUILDINGINTERFACE_H
#define BUILDINGINTERFACE_H

class BaseBuilding;
class Company;
class QString;
class Vector2D;

class BuildingInterface {
public:
	// Copies data from right hand side.
	virtual void copyFrom(const BaseBuilding &rhs) = 0;

	virtual void changeBaseValue() = 0;

	// Updates data after each turn
	virtual void update() = 0;

	virtual void setDeltaValue(double deltaValue) = 0;
	virtual double deltaValue() const = 0;

	virtual void setName(const QString &name) = 0;
	virtual const QString &name() const = 0;

	virtual void setOwner(Company *const owner) = 0;
	virtual Company *owner() const = 0;

	virtual void setPosition(const Vector2D pos) = 0;
	virtual const Vector2D &position() const = 0;

	virtual void setResource(const QString &resource) = 0;
	virtual const QString &resource() const = 0;

	virtual void setType(const QString &type) = 0;
	virtual const QString &type() const = 0;

	virtual void setValue(double value) = 0;
	virtual double value() const = 0;

protected:
	virtual void initBasicValue() = 0;

};

#endif // !BUILDINGINTERFACE_H