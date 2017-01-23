#pragma once

#include "BuildingBase.h"

class Commerce : public BuildingBase {
public:
	Commerce(const QString & = "Commerce");

	Commerce(const BuildingBase &, const QString &);

	~Commerce();

	// manual manage building
	void manage(const QString &cmd) override;

	// update data after each turn
	void update() override;
};

