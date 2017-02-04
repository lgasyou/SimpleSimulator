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
		warehouse_->addItem(Goods("Iron", 1));
	} else if (type == "Coal Mine Factory") {
		warehouse_->addItem(Goods("Coal", 2));
	} else if (type == "Steel Factory") {
		if (warehouse_->query("Iron") < 1 || 
			warehouse_->query("Coal") < 2)
			return;

		warehouse_->addItem(Goods("Steel", 1));
		warehouse_->removeItem(Goods("Iron", 1));
		warehouse_->removeItem(Goods("Coal", 2));
	}
}

void Industry::deliverGoods(const Goods &goods, Industry *dest) {
	Order *order = new Order(goods, dest, this);
	garage_->sendVihicle(order);
}

void Industry::putInStorage(const Goods &goods) {
	warehouse_->addItem(goods);
}

void Industry::putOutStorage(const Goods &goods) {
	warehouse_->removeItem(goods);
}
