#ifndef COMMERCE_H
#define COMMERCE_H

#include "basebuilding.h"

class Commerce : public BaseBuilding {
public:
	Commerce(const QString & = "Commerce");

	~Commerce();

	// update data after each turn
	void update() override;
};

#endif // COMMERCE_H