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

#ifndef BUILDINGINTERFACE_H
#define BUILDINGINTERFACE_H

class BaseBuilding;
class Company;
class QString;
class Vector2D;

// The interface of BuildingBase.
class IBuilding {
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