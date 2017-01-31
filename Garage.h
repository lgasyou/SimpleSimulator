#pragma once

class Industry;
class Order;
class Truck;
#include <QList>
#include <queue>

class Garage {
public:
	Garage();

	~Garage();

	void init();

	void addNewVihicle(const QString &);

	void sendVihicle(Order *order);

	void update();

private:
	Truck *selectFreeTruck();

	QList<Truck *> vihicleList_;
	std::queue<Truck *> transitingTrucks_;
};
