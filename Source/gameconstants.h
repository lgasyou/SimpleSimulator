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

#ifndef GAMECONSTANTS_H
#define GAMECONSTANTS_H

// TODO: Move all of those into a file.
namespace gameconstants {

const int integerMinimum = (1 << (sizeof(int) * 8 - 1));
const int integerMaximum = (int)((unsigned)integerMinimum - 1);

const int mapHeight = 16;
const int mapWeight = 16;

enum StructureType {
    Bank,
    Factory,
    Farm,
    Garage,
    Mine,
    Supermarket,
    UnusedLand,
    Villa
};

enum Commands {
    BuildBank,
    BuildFactory,
    BuildFarm,
    BuildGarage,
    BuildMine,
    BuildSupermarket,
    BuildVilla,
    BuyBuilding,
    CloseAnAccount,
    Deposit,
    DismantleBuilding,
    Loan,
    OpenAnAccount,
    Repay,
    SellBuilding,
    ShowDetail,
    Withdraw,
};

}

#endif // !GAMECONSTANTS_H