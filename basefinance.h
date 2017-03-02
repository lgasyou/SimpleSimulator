#ifndef BASEFINANCE_H
#define BASEFINANCE_H

#include "basebuilding.h"

class QString;

//	This class should not be instantiated.
class BaseFinance : public BaseBuilding {
public:
	BaseFinance(const QString &name, const QString &type);

	virtual ~BaseFinance();
};

#endif // !BASEFINANCE_H
