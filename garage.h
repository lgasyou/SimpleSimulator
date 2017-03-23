#ifndef GARAGE_H
#define GARAGE_H

#include <QList>
#include "basetransportation.h"

struct Route;
class Truck;

class QString;

class Garage : public BaseTransportation {
public:
	Garage(const QString &name = "Garage");

	~Garage();

	void init();

	inline Truck *getTruckById(int id);

	void addNewVihicle(const QString &);

	void removeVihicle(Truck *);

	void sendVihicle(Route *route, int id = -1);

	void stopVihicle(Truck *);

	void update();

	inline const QList<Truck *> &vihicleList() const { return this->vihicleList_; }

	inline int vihicleCount() const { return this->vihicleCount_; }

	inline int freeVihicleCount() const { return this->freeVihicleCount_; }

private:
	// Returns truck* if has free truck, 
	// Otherwise returns nullptr.
	Truck *selectFreeTruck();

private:
	QList<Truck *> vihicleList_;

	QList<Truck *> transitingTrucks_;

	int vihicleCount_ = 0;

	int freeVihicleCount_ = 0;
};

inline Truck *Garage::getTruckById(int id) {
	return vihicleList_[id];
}

#endif // !GARAGE_H
