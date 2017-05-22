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

#ifndef TRUCK_H
#define TRUCK_H

#include "Vihicle.h"
#include "Route.h"
#include "GoodsContainer.h"

class Truck : public Vihicle {
public:
    enum class State : char { 
        Idle,
        Going, 
        Backing
    };

    Truck();

    ~Truck();

    // Loads goods from factory
    void load();

    // Unloads goods to factory
    void unload();

    void operate();

    // Stops jobs and goes back to garage.
    void goBack();

public:
    State truckState() const { return truckState_; }

    bool isWorking() const;

    void setRoute(Route *route);
    Route *route() const { return route_; }

    bool loaded() const { return loaded_; }

    double remainTime() const { return remainTime_; }

    double halfwayTime() const { return halfwayTime_; }

    double totalTime() const { return totalTime_; }

    const GoodsContainer *freightHouse() const { return freightHouse_; }

private:
    Goods calculateLoadVolume();

    Goods calculateUnloadVolume();

    void setTripTime();

private:
    State truckState_ = State::Idle;

    Route *route_ = nullptr;

    GoodsContainer *freightHouse_ = nullptr;

    bool loaded_ = false;

    double remainTime_ = 0.0;

    double halfwayTime_ = 0.0;

    double totalTime_ = 0.0;
};

inline bool Truck::isWorking() const {
    return truckState() != State::Idle;
}

inline void Truck::setRoute(Route *route) {
    if (this->route_ != route && this->route_)
        delete route_;
    this->route_ = route;
}

#endif // !TRUCK_H
