#ifndef Industry_H
#define Industry_H

class Warehouse;
class Garage;
#include "BuildingBase.h"
#include <QMap>

class Industry : public BuildingBase {
public:
	Industry(const QString & = "Factory");

    Industry(const BuildingBase &, const QString &);

	// manual manage building
    void manage(const QString &) override;

	// updates data after each turn
	void update() override;

	void manufacture();

	void putInStorage(const QString &, double);

	void putOutStorage(const QString &, double);

	Warehouse *warehouse() const { return this->warehouse_; }

private:
    Warehouse *warehouse_;
	Garage *garage_;
};

#endif // Industry_H
