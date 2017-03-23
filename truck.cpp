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
	freightHouse_->addItem(practialGoods);

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

	freightHouse_->removeItem(practialGoods);
	route_->dest->putInStorage(practialGoods);

	loaded_ = false;
}