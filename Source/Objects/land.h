/*
 *  Copyright 2017 Li Zeqing
 *  
 *  This file is part of World Simulator.
 *  
 *  World Simulator is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  World Simulator is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with World Simulator. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LAND_H
#define LAND_H

#include <QString>

#include "iland.h"
#include "legalperson.h"
#include "Source/vector2d.h"

//  The base of building classes.
//  This class cannot be instantiated.
class Land : public ILand {
public:
    Land(const QString &name, const QString &type);

    virtual ~Land();

    virtual void update() = 0;

public:
    void setDeltaValue(double deltaValue) { this->deltaValue_ = deltaValue; }

    void setValue(double value) { this->value_ = value; }

    void setOwner(LegalPerson *owner) { this->owner_ = owner; }

    void setName(const QString &name) { this->name_ = name; }

    void setResource(const QString &resource) { this->resource_ = resource; }

    void setType(const QString &type) { this->type_ = type; }

    void setPosition(const Vector2D pos) { this->position_ = pos; }

    double deltaValue() const { return deltaValue_; }

    double value() const { return value_; }

    LegalPerson *owner() const { return owner_; }

    const QString &name() const { return name_; }

    const QString &resource() const { return resource_; }

    const QString &type() const { return type_; }

    const Vector2D &position() const { return position_; }

protected:
    void changeBaseValue();

private:
    double deltaValue_ = 0.0;

    double value_ = 0.0;

    LegalPerson *owner_ = nullptr;

    QString name_;

    QString resource_;

    QString type_;

    Vector2D position_;
};

#endif // LAND_H
