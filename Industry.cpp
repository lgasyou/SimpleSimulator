#include "industry.h"
#include "Warehouse.h"
#include "garage.h"
#include "order.h"

Industry::Industry(const QString &type) :
	BaseBuilding("Factory", type, nullptr),
	warehouse_(new Warehouse),
	garage_(new Garage)
{ }

Industry::~Industry() {
	delete garage_;
	delete warehouse_;
	garage_ = nullptr;
	warehouse_ = nullptr;
}

void Industry::update() { 
	changeBaseValue();
	manufacture();
	garage_->update();
}

void Industry::manufacture() {
	warehouse_->addItem(Goods("Goods", 1));
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
