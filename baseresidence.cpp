#include "baseresidence.h"

BaseResidence::BaseResidence(const QString &type) :
	BaseBuilding("World", type)
{ }

BaseResidence::~BaseResidence() { }

void BaseResidence::update() {
	changeBaseValue();
}
