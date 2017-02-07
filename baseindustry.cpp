#include "baseindustry.h"
#include "Warehouse.h"
#include "garage.h"
#include "order.h"
#include "goods.h"

BaseIndustry::BaseIndustry(const QString &type) :
	BaseBuilding("Factory", type, nullptr),
	warehouse_(new Warehouse),
	garage_(new Garage)
{ }

BaseIndustry::~BaseIndustry() {
	delete garage_;
	delete warehouse_;
	garage_ = nullptr;
	warehouse_ = nullptr;
}

void BaseIndustry::update() { 
	changeBaseValue();
	manufacture();
	garage_->update();
}

void BaseIndustry::manufacture() {
	warehouse_->addItem(Goods("Goods", 1));
}

void BaseIndustry::deliverGoods(const Goods &goods, BaseIndustry *dest) {
	Order *order = new Order(goods, dest, this);
	garage_->sendVihicle(order);
}

void BaseIndustry::putInStorage(const Goods &goods) {
	warehouse_->addItem(goods);
}

void BaseIndustry::putOutStorage(const Goods &goods) {
	warehouse_->removeItem(goods);
}
