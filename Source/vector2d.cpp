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

#include "vector2d.h"

#include <cmath>

Vector2D::Vector2D(double x, double y)
	: x_(x),
      y_(y) {
}

Vector2D::~Vector2D() { }

double Vector2D::length() const {
    return sqrt(lengthSquared());
}

double Vector2D::lengthSquared() const {
    return pow(x_, 2) + pow(y_, 2);
}

double Vector2D::distanceToPoint(const Vector2D &rhs) const {
    return sqrt(pow(x_ - rhs.x_, 2) + pow(y_ - rhs.y_, 2));
}

QString Vector2D::toString() const {
    return QString::number(x_) + ", " + QString::number(y_);
}
