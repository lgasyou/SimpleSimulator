#ifndef Industry_H
#define Industry_H

class IndustryWarehouse;
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

	IndustryWarehouse *warehouse() const { return this->warehouse_; }

private:
    IndustryWarehouse *warehouse_;
};

#endif // Industry_H
