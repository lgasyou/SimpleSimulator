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

#include "defaultmachinebuilder.h"

DefaultMachineBuilder::DefaultMachineBuilder() {
    machine = new Machine;
}

void DefaultMachineBuilder::setMaximumProductivity() {
    machine->setMaximalProductivity(1.0);
}

void DefaultMachineBuilder::setProducts() {
    machine->setProducts({ { "Coal", 1 } });
}

Machine *DefaultMachineBuilder::getMachine() {
    return machine;
}
