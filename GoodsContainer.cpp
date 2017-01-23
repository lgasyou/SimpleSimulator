#include "GoodsContainer.h"
#include "GameConstant.h"

GoodsContainer::GoodsContainer() :
	maxVolume_(GameConstant::maxVolumeOfWarehouses),
	curVolume_(0)
{ }

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