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
	if (this->type() == "Iron Mine Factory") {
		warehouse_->addItem("Iron", 1);
	} else if (this->type() == "Coal Mine Factory") {
		warehouse_->addItem("Coal", 2);
	} else if (this->type() == "Steel Factory") {
		warehouse_->addItem("Stell", 1);
		warehouse_->removeItem("Iron", 1);
		warehouse_->removeItem("Coal", 2);
	} else {
		warehouse_->addItem("Goods", 1);
	}
}
