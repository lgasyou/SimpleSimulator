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

#ifndef GARAGE_H
#define GARAGE_H

#include <vector>
#include <list>
#include "basetransportation.h"

struct Route;
class Truck;

class QString;

class Garage : public BaseTransportation {
public:
	Garage(const QString &name = "Garage");

	~Garage();

	void init();

	Truck *getById(int id);

	void addNewVihicle(const QString &);

	void removeVihicle(Truck *);

	void sendVihicle(Route *route, int id = -1);

	void stopVihicle(Truck *);

	void update() override;

	const std::vector<Truck *> &vihicleList() const { return vihicleList_; }

	int vihicleCount() const { return vihicleCount_; }

	int freeVihicleCount() const { return freeVihicleCount_; }

private:
	// Returns truck* if has free truck, 
	// Otherwise returns nullptr.
	Truck *selectFreeTruck();

private:
	std::vector<Truck *> vihicleList_;

	std::list<Truck *> transitingTrucks_;

	int vihicleCount_ = 0;

	int freeVihicleCount_ = 0;
};

inline Truck *Garage::getById(int id) {
	return vihicleList_[id];
}

#endif // !GARAGE_H
