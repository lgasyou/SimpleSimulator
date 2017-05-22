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

#include "Industry.h"

#include "Source/Managers/IndustryChainManager.h"

Industry::Industry(const QString &name, const QString &type)
    : LandParcel(name, type),
      warehouse_(new Warehouse) {
    
}

Industry::~Industry() {
    delete warehouse_;
}

void Industry::setMaterialsAccordingToMachine(Machine *machine) {
    for (const auto &material : machine->materials()) {
        if (std::find(materials_.cbegin(), materials_.cend(), material.label) == materials_.cend()) {
            materials_.push_back(material.label);
        }
    }
}

void Industry::setProductsAccordingToMachine(Machine *machine) {
    for (const auto &product : machine->products()) {
        if (std::find(products_.cbegin(), products_.cend(), product.label) == products_.cend()) {
            products_.push_back(product.label);
        }
    }
}