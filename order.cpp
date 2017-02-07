#include "order.h"

Order::Order(const Goods &goods_, BaseIndustry *dest_, BaseIndustry *src_):
	goods(goods_),
	dest(dest_),
	src(src_)
{ }
