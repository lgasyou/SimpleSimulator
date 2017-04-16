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

#ifndef TRUCK_H
#define TRUCK_H

#include "vihicle.h"
#include "route.h"

class GoodsContainer;
class BaseIndustry;

class Truck : public Vihicle {
public:
	Truck();

	~Truck();

	// Loads goods from factory
	// Calculates and sets remain time
	// Sets occupied_ as true
	// Sets loaded_ as true
	void load();

	// Unloads goods to factory
	// Sets loaded_ as false
	void unload();

	void setRoute(Route *route);
	Route *const route() const { return route_; }

	void setLoaded(bool loaded) { this->loaded_ = loaded; }
	bool loaded() const { return loaded_; }

	void setOccupied(bool occupied) { this->occupied_ = occupied; }
	bool occupied() const { return occupied_; }

	void setRemainTime(double remainTime) { this->remainTime_ = remainTime; }
	double remainTime() const { return remainTime_; }

	double totalTime() const { return totalTime_; }

	GoodsContainer *freightHouse() const;

private:
	Route *route_ = nullptr;

	GoodsContainer *freightHouse_;

	bool loaded_ = false;

	bool occupied_ = false;

	double remainTime_ = 0.0;

	double totalTime_ = 0.0;
};

inline void Truck::setRoute(Route *route) {
	if (this->route_ != route && this->route_)
		delete route_;
	this->route_ = route;
}

inline GoodsContainer *Truck::freightHouse() const {
	return freightHouse_;
}

#endif // !TRUCK_H
