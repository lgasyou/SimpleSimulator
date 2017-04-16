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

Truck::~Truck() { }

void Truck::load() {
	double freeVolume = freightHouse_->freeVolume();
	double remainVolume = route_->orig->warehouse()->query(route_->goods.name);
	double practialVolume = std::min({ freeVolume, remainVolume, route_->goods.volume });
	Goods practialGoods = route_->goods;
	practialGoods.volume = practialVolume;

	route_->orig->putOutStorage(practialGoods);
	freightHouse_->add(practialGoods);

	// Set remain time and total time.
	double distance = route_->dest->position().distanceToPoint(route_->orig->position());
	double remainTime = 2 * distance / speed_;
	remainTime_ = remainTime;
	totalTime_ = remainTime;

	loaded_ = true;
	occupied_ = true;
}

void Truck::unload() {
	double freeVolume = route_->dest->warehouse()->freeVolume();
	double remainVolume = freightHouse_->query(route_->goods.name);
	double practialVolume = std::min({ freeVolume, remainVolume, route_->goods.volume });
	Goods practialGoods = route_->goods;
	practialGoods.volume = practialVolume;

	freightHouse_->remove(practialGoods);
	route_->dest->putInStorage(practialGoods);

	loaded_ = false;
}