#ifndef BASEFINANCE_H
#define BASEFINANCE_H

#include "basebuilding.h"

class QString;

class BaseFinance : public BaseBuilding {
public:
	BaseFinance(const QString &name, const QString &type);
};

#endif // !BASEFINANCE_H
