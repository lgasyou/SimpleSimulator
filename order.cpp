#include "order.h"

Order::Order(const Goods &goods_, BaseIndustry *dest_, BaseIndustry *src_, bool repeated_):
	goods(goods_),
	dest(dest_),
	src(src_),
	repeated(repeated_)
{ }
