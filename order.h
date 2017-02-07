#ifndef ORDER_H
#define ORDER_H

#include <QString>
#include "goods.h"

class BaseIndustry;
class Truck;

struct Order {
	Order(const Goods &goods_, BaseIndustry *dest_, BaseIndustry *src_);

	Goods goods;
	BaseIndustry *dest;
	BaseIndustry *src;
};

#endif // !ORDER_H
