#include "vector2d.h"

#include <cmath>
#include <QString>

Vector2D::Vector2D(double x, double y) :
	x_(x),
	y_(y)
{ }

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

const QString Vector2D::toString() const {
	return QString::number(x_) + ", " + QString::number(y_);
}
