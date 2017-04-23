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

Land *BuildingFactory::create(gameconstants::StructureType buildingType, Vector2D position) {
    createInstance(buildingType);

    setBasicValue();

    allocatePosition(buildingType, position);

    building->setOwner(&Government::instance());

    // TODO: Generate true resource.
    building->setResource("Coal");

    return building;
}

void BuildingFactory::createInstance(gameconstants::StructureType buildingType) {
    switch (buildingType) {
    case gameconstants::Bank:
        building = new Bank;
        break;

    case gameconstants::Factory:
        building = new Factory;
        break;

    case gameconstants::Farm:
        building = new Farm;
        break;

    case gameconstants::Garage:
        building = new Garage;
        break;

    case gameconstants::Mine:
        building = new Mine;
        break;

    case gameconstants::Supermarket:
        building = new Supermarket;
        break;

    case gameconstants::UnusedLand:
        building = new UnusedLand;
        break;

    case gameconstants::Villa:
        building = new Villa;
        break;

    default:
        building = nullptr;
        break;
    }
}

void BuildingFactory::setBasicValue() {
    const double basicValue = 50.0;
    const double sigma = 25.0;
    double value = 0.0;
    do {
        value = Random::instance().normalDistribution(basicValue, sigma);
    } while (value <= 20.0);
    building->setValue(value);
}
