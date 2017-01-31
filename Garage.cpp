#include "Garage.h"
#include "Truck.h"
#include "Order.h"

Garage::Garage() { init(); }

Garage::~Garage() { }

void Garage::init() {
	addNewVihicle("truck");
}

void Garage::addNewVihicle(const QString &type) {
	if (type == "truck")
		vihicleList_.push_back(new Truck);
}

void Garage::sendVihicle(Order *order) {
	Truck *truck = selectFreeTruck();
	if (!truck)
		return;

	truck->setOrder(order);
	truck->load();
	transitingTrucks_.push(truck);
}

void Garage::update() {
	while (!transitingTrucks_.empty()) {
		Truck *truck = transitingTrucks_.front();
		transitingTrucks_.pop();
		truck->unload();
	}
}

Truck *Garage::selectFreeTruck() {
	for (auto &truck : vihicleList_)
		if (!truck->occupied())
			return truck;
	return nullptr;
}
