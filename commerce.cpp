#include "commerce.h"

Commerce::Commerce(const QString &type) :
	BaseBuilding("Commerce", type, nullptr)
{ }

Commerce::~Commerce() { }

void Commerce::update() {
	changeBaseValue();
}
