#ifndef RESIDENCE_H
#define RESIDENCE_H

#include "BuildingBase.h"

class Residence : public BuildingBase {
public:
    Residence(double value);

    Residence(const BuildingBase &);

	// manual manage building
    void manage(const QString &) override;

	// updates data after each turn
	void update() override;
};

#endif // RESIDENCE_H
