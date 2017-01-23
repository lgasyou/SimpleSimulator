#pragma once

#include "Vihicle.h"
#include "GoodsContainer.h"
class Industry;
#include <QMap>

class Truck : public Vihicle, public GoodsContainer {
public:
	Truck();
	~Truck();

	void setDest(Industry *dest) { this->dest_ = dest; }
	Industry *const dest() const { return this->dest_; }

	void setOccupied(bool isOccupied) { this->isOccupied_ = isOccupied; }
	const bool isOccupied() const { return this->isOccupied_; }

private:
	Industry *dest_;
	bool isOccupied_;
};
