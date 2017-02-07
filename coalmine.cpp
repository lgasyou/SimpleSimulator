#include "coalmine.h"
#include "warehouse.h"
#include "goods.h"

CoalMine::CoalMine() :
	BaseIndustry("Coal Mine")
{ }

CoalMine::~CoalMine() { }

void CoalMine::manufacture() {
	warehouse_->addItem(Goods("Coal", 2));
}
