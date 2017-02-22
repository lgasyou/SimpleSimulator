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

class BaseIndustry : public BaseBuilding {
public:
	BaseIndustry(const QString &name, const QString &type);

	virtual ~BaseIndustry();

	void addMachine(const MachineSettings &settings);

	// updates data after each turn
	void update() override;

	void manufacture();

	// Creates a route object and send vihicle by this route.
	void deliverGoods(const Goods &goods, BaseIndustry *dest);

	double putInStorage(const Goods &goods);

	double putOutStorage(const Goods &goods);

	inline Warehouse *warehouse() const { return this->warehouse_; }

	inline Garage *garage() const { return this->garage_; }

	const std::vector<Goods> &products() const;

	const std::vector<Goods> &materials() const;

protected:
    Warehouse *warehouse_;

	Garage *garage_;

	bool addedMachine_;

	std::vector<Machine *> machines_;

	std::vector<Goods> products_;

	std::vector<Goods> materials_;
};

#endif // BASEINDUSTRY_H
