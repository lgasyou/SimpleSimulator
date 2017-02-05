#include "garage.h"
#include "truck.h"
#include "order.h"

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

void Garage::removeVihicle(const QString &) { }

void Garage::sendVihicle(Order *order) {
	Truck *truck = selectFreeTruck();
	if (truck == nullptr)	return;

	truck->setOrder(order);
	truck->load();
	transitingTrucks_.push(truck);
	--freeVihicleCount_;
}

void Garage::update() {
	while (!transitingTrucks_.empty()) {
		Truck *truck = transitingTrucks_.front();
		transitingTrucks_.pop();
		truck->unload();
		++freeVihicleCount_;
	}
}

Truck *Garage::selectFreeTruck() {
	for (auto &truck : vihicleList_)
		if (!truck->occupied())
			return truck;
	return nullptr;
}
