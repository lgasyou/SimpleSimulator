#ifndef BASECOMMERCE_H
#define BASECOMMERCE_H

#include "basebuilding.h"

class BaseIndustry;
struct Goods;
class Person;
class QString;
class Warehouse;

//	This class should not be instantiated.
class BaseCommerce : public BaseBuilding {
public:
	BaseCommerce(const QString &name, const QString &type);

	virtual ~BaseCommerce();

	void purchaseCommodity(BaseIndustry *factory, const Goods &goods);

	void sellCommodity(Person *consumer, const Goods &goods);

	// update data after each turn
	void update() override;

private:
	Warehouse *warehouse_;
};

#endif // BASECOMMERCE_H
