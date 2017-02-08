#ifndef GARAGE_H
#define GARAGE_H

#include <QList>

class BaseIndustry;
struct Order;
class Truck;

class Garage {
public:
	Garage();

	~Garage();

	void init();

	void addNewVihicle(const QString &);

	void removeVihicle(Truck *);

	void sendVihicle(Order *order);

	void update();

	inline const QList<Truck *> &vihicleList() const { return this->vihicleList_; }

	inline int vihicleCount() const { return this->vihicleCount_; }

	inline int freeVihicleCount() const { return this->freeVihicleCount_; }

private:
	// Returns truck* if has free truck, 
	// otherwise returns nullptr.
	Truck *selectFreeTruck();

	QList<Truck *> vihicleList_;
	QList<Truck *> transitingTrucks_;
	int vihicleCount_;
	int freeVihicleCount_;
};

#endif // !GARAGE_H
