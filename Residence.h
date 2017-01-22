#ifndef RESIDENCE_H
#define RESIDENCE_H

#include "BaseBuilding.h"

class Residence : public BaseBuilding {
public:
    Residence(double value);

    Residence(const BaseBuilding &);

	// manual manage building
    void manage(const QString &) override;

	// updates data after each turn
	void update() override;
};

#endif // RESIDENCE_H
