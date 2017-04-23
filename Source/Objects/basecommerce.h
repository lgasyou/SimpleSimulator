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

#ifndef BASECOMMERCE_H
#define BASECOMMERCE_H

#include <QString>

#include "land.h"
#include "baseindustry.h"
#include "goods.h"
#include "person.h"
#include "warehouse.h"

// This class should not be instantiated.
class BaseCommerce : public Land {
public:
    BaseCommerce(const QString &name, const QString &type);

    virtual ~BaseCommerce();

    void restock(BaseIndustry *factory, const Goods &goods);

    void sellTo(Person *consumer, const Goods &goods);

    // update data after each turn
    virtual void update() override;

private:
    Warehouse *warehouse_ = nullptr;
};

#endif // BASECOMMERCE_H
