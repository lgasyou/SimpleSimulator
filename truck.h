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
	inline bool loaded() const { return this->loaded_; }

	inline void setOccupied(bool occupied) { this->occupied_ = occupied; }
	inline bool occupied() const { return this->occupied_; }

	inline void setRemainTime(double remainTime) { this->remainTime_ = remainTime; }
	inline double remainTime() const { return this->remainTime_; }

	inline double totalTime() const { return this->totalTime_; }

	inline GoodsContainer *const freightHouse() const;

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

inline GoodsContainer *const Truck::freightHouse() const {
	return this->freightHouse_;
}

#endif // !TRUCK_H
