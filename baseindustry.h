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

#ifndef BASEINDUSTRY_H
#define BASEINDUSTRY_H

#include "basebuilding.h"
#include <vector>

class Warehouse;
class Garage;
class Machine;
struct MachineSettings;
struct Goods;

class QString;

//	This class should not be instantiated.
class BaseIndustry : public BaseBuilding {
public:
	BaseIndustry(const QString &name, const QString &type);

	virtual ~BaseIndustry();

	void addMachine(Machine *);

	// updates data after each turn
	void update() override;

	void manufacture();

	double putInStorage(const Goods &goods);

	double putOutStorage(const Goods &goods);

	Warehouse *warehouse() const { return warehouse_; }

	const std::vector<Machine *> &machines() const { return machines_; }

	const std::vector<Goods> &products() const;

	const std::vector<Goods> &materials() const;

protected:
    Warehouse *warehouse_;

	std::vector<Machine *> machines_;

	std::vector<Goods> products_;

	std::vector<Goods> materials_;
};

#endif // BASEINDUSTRY_H
