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

#ifndef COMMERCE_H
#define COMMERCE_H

#include "LandParcel.h"
#include "Industry.h"
#include "Goods.h"
#include "Person.h"
#include "Warehouse.h"

abstract class Commerce : public LandParcel {
public:
    Commerce(const QString &name, const QString &type);

    virtual ~Commerce();

    void restock(Industry *factory, const Goods &goods);

    void sellTo(Person *consumer, const Goods &goods);

    // update data after each turn
    void update() override;

private:
    Warehouse *warehouse_ = nullptr;
};

#endif // !COMMERCE_H
