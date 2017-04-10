#ifndef GARAGE_H
#define GARAGE_H

#include <vector>
#include <list>
#include "basetransportation.h"

struct Route;
class Truck;

class QString;

class Garage : public BaseTransportation {
public:
	Garage(const QString &name = "Garage");

	~Garage();

	void init();

	Truck *getById(int id);

	void addNewVihicle(const QString &);

	void removeVihicle(Truck *);

	void sendVihicle(Route *route, int id = -1);

	void stopVihicle(Truck *);

	void update() override;

	const std::vector<Truck *> &vihicleList() const { return vihicleList_; }

	int vihicleCount() const { return vihicleCount_; }

	int freeVihicleCount() const { return freeVihicleCount_; }

private:
	// Returns truck* if has free truck, 
	// Otherwise returns nullptr.
	Truck *selectFreeTruck();

private:
	std::vector<Truck *> vihicleList_;

	std::list<Truck *> transitingTrucks_;

	int vihicleCount_ = 0;

	int freeVihicleCount_ = 0;
};

inline Truck *Garage::getById(int id) {
	return vihicleList_[id];
}

#endif // !GARAGE_H
