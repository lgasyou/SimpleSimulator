#include "Order.h"

Order::Order(const Goods &goods_, Industry *dest_, Industry *src_):
	goods(goods_),
	dest(dest_),
	src(src_)
{ }
