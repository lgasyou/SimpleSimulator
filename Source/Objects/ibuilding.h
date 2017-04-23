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

#ifndef IBUILDING_H
#define IBUILDING_H

class BaseBuilding;

// Interface of BaseBuilding.
class IBuilding {
public:
    // Copies data from the other building. Only the basic part of BaseBuilding is copiesd.
    virtual void copyFrom(const BaseBuilding &rhs) = 0;

    // Updates data each turn
    virtual void update() = 0;

protected:
    // Changes the value of building in ten percent.
    virtual void changeBaseValue() = 0;

private:
    // Gives a primitive value to this building.
    virtual void initBasicValue() = 0;

};

#endif // !IBUILDING_H