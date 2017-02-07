#ifndef BASERESIDENCE_H
#define BASERESIDENCE_H

#include "basebuilding.h"

class BaseResidence : public BaseBuilding {
public:
    BaseResidence(const QString & = "Residence");

	// updates data after each turn
	void update() override;
};

#endif // BASERESIDENCE_H
