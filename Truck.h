#pragma once

#include "Vihicle.h"
#include "GoodsContainer.h"
class Industry;
class Order;
#include <QMap>

class Truck : public Vihicle, public GoodsContainer {
public:
	Truck();
	~Truck();

	void load();

	void unload();

	void setOrder(Order *order) { this->order_ = order; }
	Order *const order() const { return this->order_; }

	void setOccupied(bool occupied) { this->occupied_ = occupied; }
	const bool occupied() const { return this->occupied_; }

private:
	Order *order_;
	bool occupied_;
};
