#pragma once

#include "BuildingBase.h"

class Commerce : public BuildingBase {
public:
	Commerce(double value);
	Commerce(const BuildingBase &, const QString &);

	~Commerce();

	// manual manage building
	void manage(const QString &cmd) override;

	// update data after each turn
	void update() override;
};

