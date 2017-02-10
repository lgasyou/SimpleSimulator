#include "route.h"

Route::Route(const Goods &goods_, BaseIndustry *dest_, BaseIndustry *orig_, bool repeated_):
	goods(goods_),
	dest(dest_),
	orig(orig_),
	repeated(repeated_)
{ }
