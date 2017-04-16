/*
 *	Copyright 2017 Li Zeqing
 *
 *	This file is part of World Simulator.
 *	
 *	World Simulator is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU Lesser General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *	
 *	World Simulator is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *	
 *	You should have received a copy of the GNU Lesser General Public License
 *	along with World Simulator.  If not, see <http://www.gnu.org/licenses/>.
 */

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
	std::for_each(machines_.begin(), machines_.end(), [](Machine *m) { m->produce(); });
}

double BaseIndustry::putInStorage(const Goods &goods) {
	return warehouse_->add(goods);
}

double BaseIndustry::putOutStorage(const Goods &goods) {
	return warehouse_->remove(goods);
}
