/*
 *	Copyright 2017 Li Zeqing
 *
 *	This file is part of World Simulator.
 *	
 *	World Simulator is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU Lesser General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *	
 *	World Simulator is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *	
 *	You should have received a copy of the GNU Lesser General Public License
 *	along with World Simulator.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BUILDINGBASE_H
#define BUILDINGBASE_H

#include "ibuilding.h"
#include "vector2d.h"
#include <QString>

class Company;

//	The base of building classes.
//	This class cannot be instantiated.
class BaseBuilding : public IBuilding {
public:
	BaseBuilding(const QString &name, const QString &type);

	virtual ~BaseBuilding();

	// Copies data from right hand side.
	void copyFrom(const BaseBuilding &rhs);

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

protected:
	void changeBaseValue();

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
