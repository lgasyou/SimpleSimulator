#ifndef RESIDENCE_H
#define RESIDENCE_H

#include "buildingbase.h"

class Residence : public BuildingBase {
public:
    Residence(const QString & = "Residence");

    Residence(const BuildingBase &, const QString &);

	// manual manage building
    void manage(const QString &) override;

	// updates data after each turn
	void update() override;
};

#endif // RESIDENCE_H
