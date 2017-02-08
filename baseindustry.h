#ifndef BASEINDUSTRY_H
#define BASEINDUSTRY_H

#include "basebuilding.h"
#include <QString>
#include <vector>

class Warehouse;
class Garage;
struct Goods;

class BaseIndustry : public BaseBuilding {
public:
	BaseIndustry(const QString & = "Factory");

	virtual ~BaseIndustry();

	// updates data after each turn
	void update() override;

	void manufacture();

	void deliverGoods(const Goods &goods, BaseIndustry *dest);

	void putInStorage(const Goods &goods);

	void putOutStorage(const Goods &goods);

	inline Warehouse *warehouse() const { return this->warehouse_; }

	inline Garage *garage() const { return this->garage_; }

protected:
    Warehouse *warehouse_;
	Garage *garage_;
	std::vector<Goods> products_;
	std::vector<Goods> rawMaterials_;
};

#endif // BASEINDUSTRY_H
