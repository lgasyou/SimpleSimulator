#ifndef BASEAGRICULTURE_H
#define BASEAGRICULTURE_H

#include "basebuilding.h"

class BaseAgriculture : public BaseBuilding {
public:
	BaseAgriculture(const QString & = "Farm");

	virtual ~BaseAgriculture();

	void update() override;
};

#endif // !BASEAGRICULTURE_H
