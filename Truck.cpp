#include "Truck.h"
#include "Order.h"
#include "Industry.h"
#include "GoodsContainer.h"

Truck::Truck() :
	order_(nullptr), 
	occupied_(false)
{ }

Truck::~Truck() { }

void Truck::load() {
	const QString &goods = order_->goods;
	const double weight = order_->weight;
	order_->src->putOutStorage(goods, weight);
	freightHouse_->addItem(goods, weight);
	occupied_ = true;
}

void Truck::unload() {
	const QString &goods = order_->goods;
	const double weight = order_->weight;
	order_->dest->putInStorage(goods, weight);
	freightHouse_->removeItem(goods, weight);
	occupied_ = false;

	delete order_;
	order_ = nullptr;
}

const GoodsContainer *Truck::freightHouse() const {
	return this->freightHouse_;
}
