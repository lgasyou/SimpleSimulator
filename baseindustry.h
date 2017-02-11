#ifndef BASEINDUSTRY_H
#define BASEINDUSTRY_H

#include "basebuilding.h"
#include <vector>

class Warehouse;
class Garage;
struct Goods;

class QString;

class BaseIndustry : public BaseBuilding {
public:
	BaseIndustry(const QString & = "Factory");

	virtual ~BaseIndustry();

	// updates data after each turn
	void update() override;

	void manufacture();

	// Creates a route object and send vihicle by this route.
	void deliverGoods(const Goods &goods, BaseIndustry *dest);

	double putInStorage(const Goods &goods);

	double putOutStorage(const Goods &goods);

	inline Warehouse *warehouse() const { return this->warehouse_; }

	inline Garage *garage() const { return this->garage_; }

	const std::vector<Goods> &products() const { return this->products_; }

	const std::vector<Goods> &rawMaterials() const { return this->rawMaterials_; }

protected:
    Warehouse *warehouse_;

	Garage *garage_;

	std::vector<Goods> products_;
	std::vector<Goods> rawMaterials_;
};

#endif // BASEINDUSTRY_H
