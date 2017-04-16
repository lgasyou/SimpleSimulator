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

#include "garage.h"
#include "truck.h"
#include "route.h"

#include "baseindustry.h"
#include "vector2d.h"

#include <algorithm>
#include <QString>

Garage::Garage(const QString &name) :
	BaseTransportation(name, "Garage") {
	init(); 
}

Garage::~Garage() { }

void Garage::init() {
	addNewVihicle("Truck");
	addNewVihicle("Truck");
}

void Garage::addNewVihicle(const QString &type) {
	if (type == "Truck")
		vihicleList_.push_back(new Truck);
	++vihicleCount_;
	++freeVihicleCount_;
}

void Garage::removeVihicle(Truck *truck) {
	if (truck->occupied())
		transitingTrucks_.remove(truck);
	vihicleList_.erase(std::find(vihicleList_.begin(), vihicleList_.end(), truck));
	delete truck;
	--vihicleCount_;
	--freeVihicleCount_;
}

void Garage::sendVihicle(Route *route, int id) {
	Truck *truck = (id < 0) ?
		selectFreeTruck() : vihicleList_[id];
	if (truck == nullptr)	return;

	truck->setRoute(route);
	truck->load();
	transitingTrucks_.push_back(truck);
	--freeVihicleCount_;
}

void Garage::stopVihicle(Truck *truck) {
	transitingTrucks_.remove(truck);
	truck->setOccupied(false);
	++freeVihicleCount_;
}

void Garage::update() {
	for (auto iter = transitingTrucks_.begin(); iter != transitingTrucks_.end(); ++iter) {
		auto truck = *iter;
		truck->setRemainTime(truck->remainTime() - 1.0);
		double remainTime = truck->remainTime();
		if (truck->loaded() && (remainTime <= truck->totalTime() / 2))
			truck->unload();
		if (remainTime <= 0.0) {
			truck->setOccupied(false);
			truck->setRemainTime(0.0);
			if (truck->route()->repeated) {
				truck->load();
			} else {
				transitingTrucks_.erase(iter);
				++freeVihicleCount_;
			}
		}

	}
}

Truck *Garage::selectFreeTruck() {
	for (auto truck : vihicleList_)
		if (!truck->occupied())
			return truck;
	return nullptr;
}
