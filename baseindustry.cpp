#include "baseindustry.h"
#include "warehouse.h"
#include "route.h"
#include "goods.h"
#include "machine.h"

#include "industrychainmanager.h"

#include <QString>
#include <algorithm>
#include <functional>

BaseIndustry::BaseIndustry(const QString &name, const QString &type) :
	BaseBuilding(name, type),
	warehouse_(new Warehouse)
{ }

BaseIndustry::~BaseIndustry() {
	delete warehouse_;
	warehouse_ = nullptr;
}

void BaseIndustry::addMachine(Machine *machine) {
	machines_.push_back(machine);

	products_.insert(products_.end(), machine->products().cbegin(), machine->products().cend());
	products_.erase(std::unique(products_.begin(), products_.end()), products_.end());
	materials_.insert(materials_.end(), machine->materials().cbegin(), machine->materials().cend());
	materials_.erase(std::unique(materials_.begin(), materials_.end()), materials_.end());
}

void BaseIndustry::update() { 
	changeBaseValue();
	manufacture();
}

void BaseIndustry::manufacture() {
	std::for_each(machines_.begin(), machines_.end(), std::mem_fun(&Machine::produce));
}

double BaseIndustry::putInStorage(const Goods &goods) {
	return warehouse_->addItem(goods);
}

double BaseIndustry::putOutStorage(const Goods &goods) {
	return warehouse_->removeItem(goods);
}

const std::vector<Goods> &BaseIndustry::products() const {
	return products_;
}

const std::vector<Goods> &BaseIndustry::materials() const {
	return materials_;
}
