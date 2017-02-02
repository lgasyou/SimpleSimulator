#pragma once

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

	void sendVihicle(Order *order);

	void update();

private:
	// If there's no free truck, returns nullptr
	Truck *selectFreeTruck();

	QList<Truck *> vihicleList_;
	std::queue<Truck *> transitingTrucks_;
};
