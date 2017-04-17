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

	// Add products of this factory.
	for (const auto &product : machine->products()) {
		if (std::count(products_.cbegin(), products_.cend(), product.name) == 0) {
			products_.push_back(product.name);
		}
	}

	// Add materials of this factory.
	for (const auto &material : machine->materials()) {
		if (std::count(materials_.cbegin(), materials_.cend(), material.name) == 0) {
			materials_.push_back(material.name);
		}
	}
}

void BaseIndustry::removeMachine(Machine *machine) {
	auto iter = std::find(machines_.begin(), machines_.end(), machine);
	machines_.erase(iter);
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
