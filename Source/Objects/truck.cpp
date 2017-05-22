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

#include <algorithm>

#include "Truck.h"
#include "Industry.h"
#include "Warehouse.h"

Truck::Truck() :
    Vihicle(),
    freightHouse_(new GoodsContainer)
{ }

Truck::~Truck() {
    delete freightHouse_;
}

void Truck::operate() {
    --remainTime_;
    if (remainTime() <= 0.0)
        route()->repeated ? load() : truckState_ = State::Idle;
    else if (remainTime() <= halfwayTime())
        loaded() ? unload() : truckState_ = State::Backing;
    else
        truckState_ = State::Going;
}
void Truck::load() {
    Goods finalGoods = calculateLoadVolume();

    route()->orig->fetch(finalGoods);
    freightHouse_->store(finalGoods);

    setTripTime();

    loaded_ = true;
    truckState_ = State::Going;
}

void Truck::unload() {
    Goods finalGoods = calculateUnloadVolume();

    freightHouse_->fetch(finalGoods);
    route()->dest->store(finalGoods);

    loaded_ = false;
    truckState_ = State::Backing;
}

void Truck::goBack() {
    if (remainTime() <= 0.0) return;
    if (remainTime() > halfwayTime()) {
        remainTime_ = totalTime() - remainTime();
    }
    truckState_ = State::Backing;
}

Goods Truck::calculateLoadVolume() {
    double truckFreeVolume = freightHouse_->freeVolume();
    double warehouseRemain = route()->orig->warehouse()->volumeOf(route()->goods.label);
    double finalVolume = std::min({ truckFreeVolume, warehouseRemain, route()->goods.volume });
    return { route()->goods.label, finalVolume };
}

Goods Truck::calculateUnloadVolume() {
    double warehouseFreeVolume = route()->dest->warehouse()->freeVolume();
    double truckLoaded = freightHouse_->volumeOf(route()->goods.label);
    double finalVolume = std::min({ warehouseFreeVolume, truckLoaded, route()->goods.volume });
    return { route()->goods.label, finalVolume };
}

void Truck::setTripTime() {
    double distance = route()->dest->position().distanceToPoint(route()->orig->position());
    halfwayTime_ = distance / speed();
    remainTime_ = totalTime_ = 2 * halfwayTime_;
}