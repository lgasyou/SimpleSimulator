#include "Order.h"

Order::Order(const QString &_goods, double _weight, Industry *_dest, Industry *_src):
	goods(_goods),
	weight(_weight),
	dest(_dest),
	src(_src)
{ }
