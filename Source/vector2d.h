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

#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <QString>

class Vector2D {
    friend bool operator==(const Vector2D &v1, const Vector2D &v2);
    friend bool operator!=(const Vector2D &v1, const Vector2D &v2);
    friend const Vector2D operator+(const Vector2D &v1, const Vector2D &v2);
    friend const Vector2D operator-(const Vector2D &v1, const Vector2D &v2);
    friend const Vector2D operator-(const Vector2D &vector);

public:
    Vector2D(double x = 0.0, double y = 0.0);
    
    ~Vector2D();

    double length() const;

    double lengthSquared() const;

    double distanceToPoint(const Vector2D &) const;

    const QString toString() const;

    void setX(double x) { this->x_ = x; }
    double x() const { return x_; }

    void setY(double y) { this->y_ = y; }
    double y() const { return y_; }

    Vector2D &operator+=(const Vector2D &vector);
    Vector2D &operator-=(const Vector2D &vector);

private:
    double x_;
    double y_;
};

inline Vector2D &Vector2D::operator+=(const Vector2D &vector) {
    x_ += vector.x_;
    y_ += vector.y_;
    return *this;
}

inline Vector2D &Vector2D::operator-=(const Vector2D &vector) {
    x_ -= vector.x_;
    y_ -= vector.y_;
    return *this;
}

inline bool operator==(const Vector2D &v1, const Vector2D &v2) {
    return v1.x_ == v2.x_ && v1.y_ == v2.y_;
}

inline bool operator!=(const Vector2D &v1, const Vector2D &v2) {
    return v1.x_ != v2.x_ || v1.y_ != v2.y_;
}

inline const Vector2D operator+(const Vector2D &v1, const Vector2D &v2) {
    return Vector2D(v1.x_ + v2.x_, v1.y_ + v2.y_);
}

inline const Vector2D operator-(const Vector2D &v1, const Vector2D &v2) {
    return Vector2D(v1.x_ - v2.x_, v1.y_ - v2.y_);
}

inline const Vector2D operator-(const Vector2D &vector) {
    return Vector2D(-vector.x_, -vector.y_);
}

#endif // !VECTOR2D_H