#ifndef ORDER_H
#define ORDER_H

#include <QString>
#include "goods.h"

class Industry;
class Truck;

struct Order {
	Order(const Goods &goods_, Industry *dest_, Industry *src_);

	Goods goods;
	Industry *dest;
	Industry *src;
};

#endif // !ORDER_H