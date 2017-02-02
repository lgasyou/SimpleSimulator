#include "GoodsContainer.h"
#include "GameConstants.h"

GoodsContainer::GoodsContainer() :
	maxVolume_(GameConstants::defaultMaxVolOfWarehouses),
	curVolume_(0.0)
{ }

GoodsContainer::~GoodsContainer() { }

const double GoodsContainer::query(const QString &item) {
	return container_[item];
}

bool GoodsContainer::addItem(const QString &item, double volume) {
	// the space is full
	if (curVolume_ + volume > maxVolume_)
		return false;

	container_[item] += volume;
	curVolume_ += volume;
	return true;
}

void GoodsContainer::removeItem(const QString &item, double volume) {
	if ((container_[item] -= volume) == 0)
		container_.remove(item);
	curVolume_ -= volume;
}