#ifndef ORDER_H
#define ORDER_H

#include <QString>
#include "goods.h"

class BaseIndustry;
class Truck;

struct Order {
	Order(const Goods &goods_, BaseIndustry *dest_,
		BaseIndustry *src_, bool repeated_ = false);

	Goods goods;

	BaseIndustry *dest;

	BaseIndustry *src;

	bool repeated;
};

#endif // !ORDER_H
