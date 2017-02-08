#include "coalmine.h"
#include "warehouse.h"
#include "goods.h"

CoalMine::CoalMine() :
	BaseIndustry("Coal Mine")
{
	const QString &product = "Coal";
	products_.push_back(Goods(product, 2));
}

CoalMine::~CoalMine() { }
