#ifndef Industry_H
#define Industry_H

#include "BuildingBase.h"
#include <QString>
#include <QMap>

class Warehouse;
class Garage;

class Industry : public BuildingBase {
public:
	Industry(const QString & = "Factory");

    Industry(const BuildingBase &, const QString &);

	// manual manage building
    void manage(const QString &) override;

	// updates data after each turn
	void update() override;

	void manufacture();

	void deliverGoods(const QString &goods, double weight, Industry *dest);

	void putInStorage(const QString &, double);

	void putOutStorage(const QString &, double);

	inline Warehouse *warehouse() const { return this->warehouse_; }

	inline Garage *garage() const { return this->garage_; }

private:
    Warehouse *warehouse_;
	Garage *garage_;
};

#endif // Industry_H
