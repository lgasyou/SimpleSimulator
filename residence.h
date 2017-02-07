#ifndef RESIDENCE_H
#define RESIDENCE_H

#include "basebuilding.h"

class Residence : public BaseBuilding {
public:
    Residence(const QString & = "Residence");

	// updates data after each turn
	void update() override;
};

#endif // RESIDENCE_H
