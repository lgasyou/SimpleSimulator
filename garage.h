#ifndef GARAGE_H
#define GARAGE_H

#include <QList>
#include <queue>

class BaseIndustry;
struct Order;
class Truck;

class Garage {
public:
	Garage();

	~Garage();

	void init();

	void addNewVihicle(const QString &);

	// TODO
	// This function is not determined yet.
	void removeVihicle(const QString &);

	void sendVihicle(Order *order);

	void update();

	inline const QList<Truck *> &vihicleList() const { return this->vihicleList_; }

	inline unsigned vihicleCount() const { return this->vihicleCount_; }

	inline unsigned freeVihicleCount() const { return this->freeVihicleCount_; }

private:
	// Returns truck* if has free truck, 
	// otherwise returns nullptr.
	Truck *selectFreeTruck();

	QList<Truck *> vihicleList_;
	std::queue<Truck *> transitingTrucks_;
	unsigned vihicleCount_;
	unsigned freeVihicleCount_;
};

#endif // !GARAGE_H
