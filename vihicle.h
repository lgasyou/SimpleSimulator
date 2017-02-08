#ifndef VIHICLE_H
#define VIHICLE_H

class Vihicle {
public:
	Vihicle(double speed = 5.0);

	virtual ~Vihicle();

	inline void setSpeed(double speed) { this->speed_ = speed; }
	inline double speed() const { return this->speed_; }

protected:
	double speed_;
};

#endif // !VIHICLE_H
