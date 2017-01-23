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

	void addNewVihicle(const QString &);

	void send(Order *order);

	void update();

private:
	QList<Truck *> vihicleList_;
	std::queue<Order *> orders_;
};
