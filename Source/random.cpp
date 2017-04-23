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
 *  along with World Simulator.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "random.h"

#include <ctime>

Random &Random::instance() {
    static Random valueGenerator;
    return valueGenerator;
}

int Random::uniformDistribution(int lowerBound, int upperBound) {
    std::uniform_int_distribution<int> range(lowerBound, upperBound);
    return range(generator_);
}

double Random::normalDistribution(double mu, double sigma) {
    std::normal_distribution<double> range(mu, sigma);
    return range(generator_);
}

Random::Random() :
    generator_(std::default_random_engine(static_cast<unsigned>(time(0))))
{ }
