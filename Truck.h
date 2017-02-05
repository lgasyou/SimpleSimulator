#ifndef TRUCK_H
#define TRUCK_H

#include "vihicle.h"

class GoodsContainer;
class Industry;
struct Order;

class Truck : public Vihicle {
public:
	Truck();

	~Truck();

	// Exchanges goods with factory which is source
	// Set "occupied_" as true
	void load();

	// Exchanges goods with factory which is destination
	// Set "occupied_" as false
	// Delete "order_"
	void unload();

	inline void setOrder(Order *order) { this->order_ = order; }
	inline Order *const order() const { return this->order_; }

	inline void setOccupied(bool occupied) { this->occupied_ = occupied; }
	inline const bool occupied() const { return this->occupied_; }

	const GoodsContainer *freightHouse() const;

private:
	Order *order_;
	GoodsContainer *freightHouse_;
	bool occupied_;
};

#endif // !TRUCK_H