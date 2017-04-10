#ifndef BUILDINGBASE_H
#define BUILDINGBASE_H

#include "ibuilding.h"
#include "vector2d.h"
#include <QString>

class Company;

//	The base of building classes.
//	This class should not be instantiated.
class BaseBuilding : public IBuilding {
public:
	BaseBuilding(const QString &name, const QString &type);

	virtual ~BaseBuilding();

	// Copies data from right hand side.
	void copyFrom(const BaseBuilding &rhs);

	void changeBaseValue();

	// Updates data after each turn
	void update() = 0;

	void setDeltaValue(double deltaValue) { this->deltaValue_ = deltaValue; }
	double deltaValue() const { return deltaValue_; }

	void setName(const QString &name) { this->name_ = name; }
	const QString &name() const { return name_; }

	void setOwner(Company *const owner) { this->owner_ = owner; }
	Company *owner() const { return owner_; }

	void setPosition(const Vector2D pos) { this->position_ = pos; }
	const Vector2D &position() const { return position_; }

	void setResource(const QString &resource) { this->resource_ = resource; }
	const QString &resource() const { return resource_; }

	void setType(const QString &type) { this->type_ = type; }
	const QString &type() const { return type_; }

	void setValue(double value) { this->value_ = value; }
	double value() const { return value_; }

private:
	void initBasicValue();

private:
    double deltaValue_ = 0.0;

	QString name_;

    Company *owner_ = nullptr;

	Vector2D position_;

	QString resource_;

    QString type_;

    double value_ = 0.0;
};

#endif // BUILDINGBASE_H
