#include "basecommerce.h"

BaseCommerce::BaseCommerce(const QString &type) :
	BaseBuilding("Commerce", type)
{ }

BaseCommerce::~BaseCommerce() { }

void BaseCommerce::update() {
	changeBaseValue();
}
