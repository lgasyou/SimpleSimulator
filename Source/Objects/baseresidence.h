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
 *  along with World Simulator.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BASERESIDENCE_H
#define BASERESIDENCE_H

#include <list>
#include <QString>

#include "basebuilding.h"
#include "person.h"

// This class should not be instantiated.
class BaseResidence : public BaseBuilding {
public:
    BaseResidence(const QString &name, const QString &type);

    virtual ~BaseResidence();

    // updates data after each turn
    virtual void update() override;

    void checkin(Person *resident);

    void checkout(Person *resident);

    const std::list<Person *> &residents() const { return residents_; }

private:
    std::list<Person *> residents_;
};

#endif // BASERESIDENCE_H
