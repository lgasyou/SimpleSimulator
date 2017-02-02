#include "Industry.h"
#include "Warehouse.h"
#include "Garage.h"
#include "Order.h"

Industry::Industry(const QString &type) :
	BuildingBase("Factory", type, nullptr),
	warehouse_(new Warehouse),
	garage_(new Garage)
{ }

Industry::Industry(const BuildingBase &rhs, const QString &type) :
	BuildingBase(rhs, type),
    warehouse_(new Warehouse),
	garage_(new Garage)
{ }

void Industry::manage(const QString &cmd) {

}

void Industry::update() { 
	changeBaseValue();
	manufacture();
	garage_->update();
}

void Industry::manufacture() {
	const QString &type = this->type();
	if (type == "Iron Mine Factory") {
		warehouse_->addItem("Iron", 1);
	} else if (type == "Coal Mine Factory") {
		warehouse_->addItem("Coal", 2);
	} else if (type == "Steel Factory") {
		if (warehouse_->query("Iron") < 1 || 
			warehouse_->query("Coal") < 2)
			return;

		warehouse_->addItem("Steel", 1);
		warehouse_->removeItem("Iron", 1);
		warehouse_->removeItem("Coal", 2);
	} else {
		warehouse_->addItem("Goods", 1);
	}
}

void Industry::transit(const QString &goods, double weight, Industry *dest) {
	Order *order = new Order(goods, weight, dest, this);
	garage_->sendVihicle(order);
}

void Industry::putInStorage(const QString &item, double volume) {
	warehouse_->addItem(item, volume);
}

void Industry::putOutStorage(const QString &item, double volume) {
	warehouse_->removeItem(item, volume);
}
