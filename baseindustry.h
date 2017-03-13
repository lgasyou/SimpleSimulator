#ifndef BASEINDUSTRY_H
#define BASEINDUSTRY_H

#include "basebuilding.h"
#include <vector>

class Warehouse;
class Garage;
class Machine;
struct MachineSettings;
struct Goods;

class QString;

//	This class should not be instantiated.
class BaseIndustry : public BaseBuilding {
public:
	BaseIndustry(const QString &name, const QString &type);

	virtual ~BaseIndustry();

	void addMachine(Machine *);

	// updates data after each turn
	void update() override;

	void manufacture();

	double putInStorage(const Goods &goods);

	double putOutStorage(const Goods &goods);

	Warehouse *warehouse() const { return this->warehouse_; }

	const std::vector<Machine *> &machines() const { return this->machines_; }

	const std::vector<Goods> &products() const;

	const std::vector<Goods> &materials() const;

protected:
    Warehouse *warehouse_;

	std::vector<Machine *> machines_;

	std::vector<Goods> products_;

	std::vector<Goods> materials_;
};

#endif // BASEINDUSTRY_H
