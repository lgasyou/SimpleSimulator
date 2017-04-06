#ifndef VIHICLE_H
#define VIHICLE_H

class Vihicle {
public:
	Vihicle(double speed = 5.0);

	virtual ~Vihicle();

	void setSpeed(double speed) { this->speed_ = speed; }
	double speed() const { return speed_; }

protected:
	double speed_;
};

#endif // !VIHICLE_H
