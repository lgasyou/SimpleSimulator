#include "baseindustry.h"
#include "warehouse.h"
#include "garage.h"
#include "route.h"
#include "goods.h"
#include "machine.h"

#include "industrychainmanager.h"

#include <QString>
#include <algorithm>
#include <functional>

BaseIndustry::BaseIndustry(const QString &type) :
	BaseBuilding("Factory", type),
	addedMachine_(false),
	warehouse_(new Warehouse),
	garage_(new Garage)
{ }

BaseIndustry::~BaseIndustry() {
	delete garage_;
	delete warehouse_;
	garage_ = nullptr;
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
	garage_->update();
}

void BaseIndustry::manufacture() {
	std::for_each(machines_.begin(), machines_.end(), std::mem_fun(&Machine::produce));
}

void BaseIndustry::deliverGoods(const Goods &goods, BaseIndustry *dest) {
	Route *route = new Route(goods, dest, this);
	garage_->sendVihicle(route);
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
