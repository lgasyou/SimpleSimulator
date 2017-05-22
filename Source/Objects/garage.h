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

#ifndef GARAGE_H
#define GARAGE_H

#include <vector>
#include <list>

#include "Transportation.h"
#include "Route.h"

class Truck;

class Garage : public Transportation {
public:
    Garage(const QString &name = "Garage");

    ~Garage();

    Truck *getById(int id);

    void addNewVihicle(const QString &);

    void removeVihicle(Truck *);

    // Lets truck[id] join route.
    // If id < 0 then selects a free vihicle to continue.
    void sendVihicle(Route *route, int id = -1);

    void stopVihicle(Truck *);

    void update() override;

public:
    const std::vector<Truck *> &vihicleList() const { return vihicleList_; }

    std::size_t vihicleCount() const { return vihicleList_.size(); }

    std::size_t freeVihicleCount() const;

private:
    // Returns truck* if has free truck, 
    // Otherwise returns nullptr.
    Truck *selectFreeTruck();

private:
    std::vector<Truck *> vihicleList_;

    std::list<Truck *> transitingTrucks_;
};

inline Truck *Garage::getById(int id) {
    return vihicleList_[id];
}

inline std::size_t Garage::freeVihicleCount() const {
    return vihicleList_.size() - transitingTrucks_.size();
}

#endif // !GARAGE_H
