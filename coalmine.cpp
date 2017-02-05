#include "coalmine.h"
#include "warehouse.h"

CoalMine::CoalMine() :
	Industry("Coal Mine")
{ }

CoalMine::~CoalMine() { }

void CoalMine::manufacture() {
	warehouse_->addItem(Goods("Coal", 2));
}
