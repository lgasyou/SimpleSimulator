/*
 *  Copyright 2017 Li Zeqing
 *
 *  This file is part of World Simulator.
 *
 *  World Simulator is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  World Simulator is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with World Simulator. If not, see <http://www.gnu.org/licenses/>.
 */

#include "baseindustry.h"

#include <algorithm>

#include "Source/Managers/industrychainmanager.h"

BaseIndustry::BaseIndustry(const QString &name, const QString &type) :
    Land(name, type),
    warehouse_(new Warehouse) { }

BaseIndustry::~BaseIndustry() {
    delete warehouse_;
}

void BaseIndustry::addMachine(Machine *machine) {
    machines_.push_back(machine);
    setMaterialsAccordingToMachine(machine);
    setProductsAccordingToMachine(machine);
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

double BaseIndustry::store(const Goods &goods) {
    return warehouse_->store(goods);
}

double BaseIndustry::fetch(const Goods &goods) {
    return warehouse_->fetch(goods);
}

void BaseIndustry::setMaterialsAccordingToMachine(Machine *machine) {
    for (const auto &material : machine->materials()) {
        if (std::find(materials_.cbegin(), materials_.cend(), material.label) == materials_.cend()) {
            materials_.push_back(material.label);
        }
    }
}

void BaseIndustry::setProductsAccordingToMachine(Machine *machine) {
    for (const auto &product : machine->products()) {
        if (std::find(products_.cbegin(), products_.cend(), product.label) == products_.cend()) {
            products_.push_back(product.label);
        }
    }
}