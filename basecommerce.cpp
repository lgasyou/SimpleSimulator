#include "basecommerce.h"

BaseCommerce::BaseCommerce(const QString &type) :
	BaseBuilding("BaseCommerce", type, nullptr)
{ }

BaseCommerce::~BaseCommerce() { }

void BaseCommerce::update() {
	changeBaseValue();
}
