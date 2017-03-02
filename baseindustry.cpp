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
	addedMachine_(false),
	warehouse_(new Warehouse)
{ }

BaseIndustry::~BaseIndustry() {
	delete warehouse_;
	warehouse_ = nullptr;
}

void BaseIndustry::addMachine(const MachineSettings &settings) {
	Machine *newMachine = new Machine;
	newMachine->setParameters(settings);
	machines_.push_back(newMachine);

	products_.insert(products_.end(), newMachine->products().cbegin(), newMachine->products().cend());
	materials_.insert(materials_.end(), newMachine->materials().cbegin(), newMachine->materials().cend());
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
	return this->products_;
}

const std::vector<Goods> &BaseIndustry::materials() const {
	return this->materials_;
}
