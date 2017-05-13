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

#include "buildingfactory.h"

#include "Source/Objects/unusedland.h"  
#include "Source/Objects/factory.h"
#include "Source/Objects/mine.h"    
#include "Source/Objects/supermarket.h"    
#include "Source/Objects/bank.h"
#include "Source/Objects/villa.h"
#include "Source/Objects/farm.h"
#include "Source/Objects/garage.h"
#include "Source/Objects/government.h"

#include "Source/random.h"

Land *BuildingFactory::create(const LandInitialParameter &landParameter) {
    parameter = landParameter;
    createInstance();

    allocatePosition();
    setValue();
    setOwner();
    setResource();

    return building;
}

void BuildingFactory::createInstance() {
    switch (parameter.type) {
    case BANK:
        building = new Bank;
        break;

    case FACTORY:
        building = new Factory;
        break;

    case FARM:
        building = new Farm;
        break;

    case GARAGE:
        building = new Garage;
        break;

    case MINE:
        building = new Mine;
        break;

    case SUPERMARKET:
        building = new Supermarket;
        break;

    case UNUSED_LAND:
        building = new UnusedLand;
        break;

    case VILLA:
        building = new Villa;
        break;

    default:
        building = nullptr;
        break;
    }
}

void BuildingFactory::setValue() {
    double value = parameter.basicValue;
    if (parameter.basicValue == 0.0) {
        const double basicValue = 50.0;
        const double sigma = 25.0;
        do {
            value = Random::instance().normalDistribution(basicValue, sigma);
        } while (value <= 20.0);
        building->setDeltaValue(parameter.deltaValue);
    }
    building->setValue(value);
}

void BuildingFactory::setOwner() {
    (parameter.owner == nullptr) ?
        building->setOwner(&Government::instance()) :
        building->setOwner(parameter.owner);
}

void BuildingFactory::setResource() {
    if (parameter.resource == "Unallocated") {
        switch (int resourceNumber = Random::instance().uniformDistribution(0, 2)) {
        case 0:
            parameter.resource = "Coal";
            break;

        case 1:
            parameter.resource = "Iron";
            break;

        case 2:
            parameter.resource = "Log";
            break;

        default:
            parameter.resource.clear();
            break;
        }
    }
    building->setResource(parameter.resource);
}
