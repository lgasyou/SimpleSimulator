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

	inline void setRoute(Route *route);
	inline Route *const route() const { return this->route_; }

	inline void setLoaded(bool loaded) { this->loaded_ = loaded; }
	inline const bool loaded() const { return this->loaded_; }

	inline void setOccupied(bool occupied) { this->occupied_ = occupied; }
	inline const bool occupied() const { return this->occupied_; }

	inline void setRemainTime(double remainTime) { this->remainTime_ = remainTime; }
	inline const double remainTime() const { return this->remainTime_; }

	inline const double totalTime() const { return this->totalTime_; }

	inline const GoodsContainer *freightHouse() const;

private:
	Route *route_;
	GoodsContainer *freightHouse_;
	bool loaded_;
	bool occupied_;
	double remainTime_;
	double totalTime_;
};

inline void Truck::setRoute(Route *route) {
	if (this->route_ != route && this->route_)
		delete route_;
	this->route_ = route;
}

inline const GoodsContainer *Truck::freightHouse() const {
	return this->freightHouse_;
}

#endif // !TRUCK_H
