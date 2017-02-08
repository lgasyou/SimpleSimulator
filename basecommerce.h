#ifndef BASECOMMERCE_H
#define BASECOMMERCE_H

#include "basebuilding.h"

class BaseCommerce : public BaseBuilding {
public:
	BaseCommerce(const QString & = "Commerce");

	virtual ~BaseCommerce();

	// update data after each turn
	void update() override;
};

#endif // BASECOMMERCE_H
