#ifndef ROUTE_H
#define ROUTE_H

#include <QString>
#include "goods.h"

class BaseIndustry;
class Truck;

struct Route {
	Route(const Goods &goods_, BaseIndustry *dest_,
		BaseIndustry *orig_, bool repeated_ = false);

	Goods goods;

	BaseIndustry *dest;

	BaseIndustry *orig;

	bool repeated;
};

#endif // !ROUTE_H
