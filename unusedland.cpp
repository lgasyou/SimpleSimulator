#include "unusedland.h"

#include <QString>

UnusedLand::UnusedLand(const QString &name) :
	BaseBuilding(name, "Unused Land")
{ }

void UnusedLand::update() {
	changeBaseValue();
}
