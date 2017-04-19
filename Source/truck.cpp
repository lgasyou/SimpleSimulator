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

#include "truck.h"
#include "route.h"
#include "baseindustry.h"
#include "goodscontainer.h"
#include "warehouse.h"

#include <algorithm>

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

void Truck::goBack() {
	if (remainTime() <= 0.0) return;
	if (remainTime() > halfwayTime()) {
		remainTime_ = totalTime() - remainTime();
	}
	truckState_ = State::Backing;
}

void Truck::load() {
	double truckFreeVolume = freightHouse_->freeVolume();
	double warehouseRemain = route()->orig->warehouse()->volumeOf(route()->goods.label);
	double finalVolume = std::min({ truckFreeVolume, warehouseRemain, route()->goods.volume });
	Goods finalGoods = { route()->goods.label, finalVolume };

	route()->orig->fetch(finalGoods);
	freightHouse_->store(finalGoods);

	// Sets remain time, halfway time and total time.
	double distance = route()->dest->position().distanceToPoint(route()->orig->position());
	halfwayTime_ = distance / speed_;
	remainTime_ = totalTime_ = 2 * halfwayTime_;

	loaded_ = true;
	truckState_ = State::Going;
}

void Truck::unload() {
	double warehouseFreeVolume = route()->dest->warehouse()->freeVolume();
	double truckLoaded = freightHouse_->volumeOf(route()->goods.label);
	double finalVolume = std::min({ warehouseFreeVolume, truckLoaded, route()->goods.volume });
	Goods finalGoods = { route()->goods.label, finalVolume };

	freightHouse_->fetch(finalGoods);
	route()->dest->store(finalGoods);

	loaded_ = false;
	truckState_ = State::Backing;
}