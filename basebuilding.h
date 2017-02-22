#ifndef BUILDINGBASE_H
#define BUILDINGBASE_H

#include <QString>
#include "vector2d.h"

class Company;

//	the base of building classes.
//	three types of building are:
//	* BaseResidence,
//	* BaseCommerce,
//	* BaseIndustry.
class BaseBuilding {
public:
	BaseBuilding(const QString &name, const QString &type,
		double deltaValue = 0.0, Company *owner = nullptr, const Vector2D & = Vector2D(0.0, 0.0));

    virtual ~BaseBuilding() { }

	// Copys data from right hand side.
	void copyFrom(const BaseBuilding &rhs);

	// Updates data after each turn
	virtual void update();

	void changeBaseValue();

    inline void setValue(double value) { this->value_ = value; }
	inline const double value() const { return this->value_; }

    inline void setDeltaValue(double deltaValue) { this->deltaValue_ = deltaValue; }
    inline const double deltaValue() const { return this->deltaValue_; }

    inline void setName(const QString &name) { this->name_ = name; }
    inline const QString &name() const { return this->name_; }

    inline void setType(const QString &type) { this->type_ = type; }
    inline const QString &type() const { return this->type_; }

    inline void setOwner(Company *const owner) { this->owner_ = owner; }
    inline Company *const owner() const { return this->owner_; }

	inline void setPosition(const Vector2D pos) { this->position_ = pos; }
	inline const Vector2D &position() const { return this->position_; }

private:
	void initBasicValue();

private:
    QString name_;

    double value_;

    double deltaValue_;

    QString type_;

    Company *owner_;

	Vector2D position_;
};

#endif // BUILDINGBASE_H