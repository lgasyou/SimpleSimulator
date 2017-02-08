#include "ironmine.h"
#include "warehouse.h"
#include "goods.h"

IronMine::IronMine() :
	BaseIndustry("Iron Mine")
{ 
	const QString &product = "Iron";
	products_.push_back(Goods(product, 1));
}

IronMine::~IronMine() { }
