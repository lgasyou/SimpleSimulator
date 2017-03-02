#ifndef FARM_H
#define FARM_H

#include "baseagriculture.h"

class QString;

class Farm : public BaseAgriculture {
public:
	Farm(const QString &name = "Farm");

	~Farm();
};

#endif // !FARM_H
