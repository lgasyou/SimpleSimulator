#include "Truck.h"
#include "Order.h"
#include "Industry.h"

Truck::Truck() :
	order_(nullptr), 
	occupied_(false)
{ }

void Truck::load() {
	QString &goods = order_->goods;
	double weight = order_->weight;
	order_->src->putOutStorage(goods, weight);
	this->addItem(goods, weight);
	occupied_ = true;
}

void Truck::unload() {
	QString &goods = order_->goods;
	double weight = order_->weight;
	order_->dest->putInStorage(goods, weight);
	this->removeItem(goods, weight);
	occupied_ = false;

	delete order_;
	order_ = nullptr;
}
