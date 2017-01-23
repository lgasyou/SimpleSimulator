#include "Garage.h"
#include "Truck.h"
#include "Order.h"

Garage::Garage() { }

Garage::~Garage() { }

void Garage::addNewVihicle(const QString &type) {
	if (type == "truck")
		vihicleList_.push_back(new Truck);
}

void Garage::send(Order *order) {
	// todo
	orders_.push(nullptr);
}

void Garage::update() {
	while (!orders_.empty()) {
		Order *order = orders_.front();
		orders_.pop();
		Industry *dest = order->dest;

	}
}
