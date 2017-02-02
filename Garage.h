#ifndef GARAGE_H
#define GARAGE_H

class Industry;
struct Order;
class Truck;
#include <QList>
#include <queue>

class Garage {
public:
	Garage();

	~Garage();

	void init();

	void addNewVihicle(const QString &);

	void removeVihicle(const QString &);

	void sendVihicle(Order *order);

	void update();

private:
	// Returns truck* if has free truck, 
	// otherwise returns nullptr.
	Truck *selectFreeTruck();

	QList<Truck *> vihicleList_;
	std::queue<Truck *> transitingTrucks_;
};

#endif // !GARAGE_H