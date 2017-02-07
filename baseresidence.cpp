#include "baseresidence.h"

BaseResidence::BaseResidence(const QString &type) :
	BaseBuilding("World", type, nullptr)
{ }

void BaseResidence::update() {
	changeBaseValue();
}
