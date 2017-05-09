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

#ifndef PERSON_H
#define PERSON_H

#include "legalperson.h"
#include "goodscontainer.h"

class Land;
class BaseResidence;

class Person : public LegalPerson {
public:
    Person(const QString &name = "This is a nameless person.");

    ~Person();

    virtual void update() override;

    void store(const Goods &goods);

    void fetch(const Goods &goods);

public:
    const BaseResidence *home() const { return home_; }

    const Land *workplace() const { return workplace_; }

    const GoodsContainer &properties() const { return properties_; }

private:
    BaseResidence *home_ = nullptr;

    Land *workplace_ = nullptr;

    GoodsContainer properties_;

};

inline void Person::store(const Goods &goods) {
    properties_.store(goods);
}

inline void Person::fetch(const Goods &goods) {
    properties_.fetch(goods);
}

#endif // !PERSON_H
