#include "IndustryWarehouse.h"
#include "GameConstant.h"

IndustryWarehouse::IndustryWarehouse() :
    maxVolume_(GameConstant::maxVolumeOfWarehouses),
    curVolume_(0)
{ }

bool IndustryWarehouse::addItem(const QString &item, double volume) {
	// the space is full
    if (curVolume_ + volume > maxVolume_)
        return false;

    warehouse_[item] += volume;
    curVolume_ += volume;
    return true;
}

void IndustryWarehouse::removeItem(const QString &item, double volume) {
	if ((warehouse_[item] -= volume) == 0)
		warehouse_.remove(item);
    curVolume_ -= volume;
}
