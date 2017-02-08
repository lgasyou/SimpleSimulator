#include "truck.h"
#include "order.h"
#include "baseindustry.h"
#include "goodscontainer.h"

Truck::Truck() :
	order_(nullptr), 
	occupied_(false),
	remainTime_(0.0),
	freightHouse_(new GoodsContainer)
{ }

Truck::~Truck() { }

void Truck::load() {
	order_->src->putOutStorage(order_->goods);
	freightHouse_->addItem(order_->goods);
	occupied_ = true;
}

void Truck::unload() {
	order_->dest->putInStorage(order_->goods);
	freightHouse_->removeItem(order_->goods);
	occupied_ = false;

	delete order_;
	order_ = nullptr;
}

const GoodsContainer *Truck::freightHouse() const {
	return this->freightHouse_;
}
