#include "Industry.h"
#include "IndustryWarehouse.h"

Industry::Industry(const QString &type) :
	BuildingBase("Factory", type, nullptr),
	warehouse_(new IndustryWarehouse)
{ }

Industry::Industry(const BuildingBase &rhs, const QString &type) :
	BuildingBase(rhs, type),
    warehouse_(new IndustryWarehouse)
{ }

void Industry::manage(const QString &cmd) {

}

void Industry::update() { 
	changeBaseValue();
	manufacture();
}

void Industry::manufacture() {
	const QString &type = this->type();
	if (type == "Iron Mine Factory") {
		warehouse_->addItem("Iron", 1);
	} else if (type == "Coal Mine Factory") {
		warehouse_->addItem("Coal", 2);
	} else if (type == "Steel Factory") {
		warehouse_->addItem("Steel", 1);
		warehouse_->removeItem("Iron", 1);
		warehouse_->removeItem("Coal", 2);
	} else {
		warehouse_->addItem("Goods", 1);
	}
}
