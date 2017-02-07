#ifndef INDUSTRY_H
#define INDUSTRY_H

#include "basebuilding.h"
#include "goods.h"
#include <QString>
#include <QMap>

class Warehouse;
class Garage;

class Industry : public BaseBuilding {
public:
	Industry(const QString & = "Factory");

	virtual ~Industry();

	// updates data after each turn
	void update() override;

	virtual void manufacture();

	void deliverGoods(const Goods &goods, Industry *dest);

	void putInStorage(const Goods &goods);

	void putOutStorage(const Goods &goods);

	inline Warehouse *warehouse() const { return this->warehouse_; }

	inline Garage *garage() const { return this->garage_; }

protected:
    Warehouse *warehouse_;
	Garage *garage_;
};

#endif // INDUSTRY_H
