#include "ironmine.h"
#include "warehouse.h"
#include "goods.h"

IronMine::IronMine() :
	BaseIndustry("Iron Mine")
{ }

IronMine::~IronMine() { }

void IronMine::manufacture() {
	warehouse_->addItem(Goods("Iron", 1));
}
