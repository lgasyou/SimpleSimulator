#ifndef VECTOR2D_H
#define VECTOR2D_H

class QString;

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