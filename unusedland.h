#ifndef UNUSEDLAND_H
#define UNUSEDLAND_H

#include "basebuilding.h"

class QString;

class UnusedLand : public BaseBuilding {
public:
	UnusedLand(const QString &name = "Unused Land");

	void update() override;
};

#endif // !UNUSEDLAND_H
