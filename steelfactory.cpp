#include "steelfactory.h"
#include "warehouse.h"
#include "goods.h"

SteelFactory::SteelFactory() :
	BaseIndustry("Steel Factory")
{ }

SteelFactory::~SteelFactory() { }

void SteelFactory::manufacture() {
	if (warehouse_->query("Iron") < 1 || 
		warehouse_->query("Coal") < 2)
		return;

	warehouse_->removeItem(Goods("Iron", 1));
	warehouse_->removeItem(Goods("Coal", 2));
	warehouse_->addItem(Goods("Steel", 1));
}
