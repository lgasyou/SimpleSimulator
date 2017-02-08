#include "garage.h"
#include "truck.h"
#include "order.h"

#include "baseindustry.h"
#include "vector2d.h"

Garage::Garage() :
	vihicleCount_(0),
	freeVihicleCount_(0)
{ init(); }

Garage::~Garage() { }

void Garage::init() {
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
		transitingTrucks_.removeOne(truck);
	vihicleList_.removeOne(truck);
	delete truck;
	--vihicleCount_;
	--freeVihicleCount_;
}

void Garage::sendVihicle(Order *order) {
	Truck *truck = selectFreeTruck();
	if (truck == nullptr)	return;

	truck->setOrder(order);
	double remainTime = order->dest->pos().distanceToPoint(order->src->pos());
	truck->setRemainTime(remainTime);
	truck->load();
	transitingTrucks_.push_back(truck);
	--freeVihicleCount_;
}

void Garage::update() {
	for (auto iter = transitingTrucks_.begin(); iter != transitingTrucks_.end(); ++iter) {
		auto truck = *iter;
		truck->setRemainTime(truck->remainTime() - 1.0);
		if (truck->remainTime() <= 0.0) {
			truck->unload();
			transitingTrucks_.erase(iter);
			++freeVihicleCount_;
		}
	}
}

Truck *Garage::selectFreeTruck() {
	for (auto &truck : vihicleList_)
		if (!truck->occupied())
			return truck;
	return nullptr;
}
