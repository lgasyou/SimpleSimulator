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
