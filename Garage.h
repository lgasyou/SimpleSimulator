#ifndef GARAGE_H
#define GARAGE_H

#include <QList>
#include <queue>

class Industry;
struct Order;
class Truck;

class Garage {
public:
	Garage();

	~Garage();

	void init();

	void addNewVihicle(const QString &);

	void removeVihicle(const QString &);

	void sendVihicle(Order *order);

	void update();

	inline const QList<Truck *> &vihicleList() const { return this->vihicleList_; }

private:
	// Returns truck* if has free truck, 
	// otherwise returns nullptr.
	Truck *selectFreeTruck();

	QList<Truck *> vihicleList_;
	std::queue<Truck *> transitingTrucks_;
};

#endif // !GARAGE_H