#include "basecommerce.h"
#include "factory.h"
#include "person.h"
#include "warehouse.h"

#include <QString>

BaseCommerce::BaseCommerce(const QString &name, const QString &type) :
	BaseBuilding(name, type),
	warehouse_(new Warehouse)
{ }

BaseCommerce::~BaseCommerce() { }

void BaseCommerce::purchaseCommodity(BaseIndustry *factory, const Goods &goods) {
	factory->putOutStorage(goods);
}

void BaseCommerce::sellCommodity(Person *consumer, const Goods &goods) {

}

void BaseCommerce::update() {
	changeBaseValue();
}
