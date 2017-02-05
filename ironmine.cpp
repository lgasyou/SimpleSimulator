#include "ironmine.h"
#include "warehouse.h"

IronMine::IronMine() :
	Industry("Iron Mine")
{ }

IronMine::~IronMine() { }

void IronMine::manufacture() {
	warehouse_->addItem(Goods("Iron", 1));
}
