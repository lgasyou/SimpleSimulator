#include "FactoryCargo.h"

FactoryCargo::FactoryCargo() :
    maxVolume_(100),
    curVolume_(0)
{ }

inline bool FactoryCargo::add(const QString &item, double volume) {
    if (curVolume_ + volume > maxVolume_)
        return false;

    cargo_[item] += volume;
    curVolume_ += volume;
    return true;
}

inline void FactoryCargo::remove(const QString &item, double volume) {
	if ((cargo_[item] -= volume) == 0)
		cargo_.remove(item);
    curVolume_ -= volume;
}
