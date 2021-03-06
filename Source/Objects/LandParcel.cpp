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

#include "LandParcel.h"

#include "Source/Random.h"

LandParcel::LandParcel(const QString &name, const QString &type)
    : name_(name),
      type_(type) {
    
}

void LandParcel::changeBaseValue() {
    double sigma = value_ * 0.1 / 3;
    deltaValue_ = Random::instance().normalDistribution(0, sigma);
    value_ += deltaValue_;
}