#ifndef ROUTE_H
#define ROUTE_H

#include "goods.h"

class BaseIndustry;
class Truck;

class QString;

struct Route {
	Route(const Goods &goods_, BaseIndustry *dest_,
		BaseIndustry *orig_, bool repeated_ = false);

	Goods goods;

	BaseIndustry *dest;

	BaseIndustry *orig;

	bool repeated = false;
};

#endif // !ROUTE_H
