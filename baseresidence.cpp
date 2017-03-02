#include "baseresidence.h"
#include "person.h"

BaseResidence::BaseResidence(const QString &name, const QString &type) :
	BaseBuilding(name, type)
{ }

BaseResidence::~BaseResidence() { }

void BaseResidence::update() {
	changeBaseValue();
}

void BaseResidence::checkin(Person *resident) { }

void BaseResidence::checkout(Person *resident) { }
