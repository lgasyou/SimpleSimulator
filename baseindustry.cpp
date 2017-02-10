#include "baseindustry.h"
#include "warehouse.h"
#include "garage.h"
#include "route.h"
#include "goods.h"

#include "industrychainmanager.h"

BaseIndustry::BaseIndustry(const QString &type) :
	BaseBuilding("Factory", type),
	warehouse_(new Warehouse),
	garage_(new Garage)
{
	if (type == "Factory") {
		const QString &product = "Product";
		products_.push_back(Goods(product, 1));
		rawMaterials_ = IndustryChainManager::instance().precursors(product);
	}
}

BaseIndustry::~BaseIndustry() {
	delete garage_;
	delete warehouse_;
	garage_ = nullptr;
	warehouse_ = nullptr;
}

void BaseIndustry::update() { 
	changeBaseValue();
	manufacture();
	garage_->update();
}

void BaseIndustry::manufacture() {
	for (const auto &rawMaterial : rawMaterials_)
		if (rawMaterial.volume > warehouse_->query(rawMaterial.name))
			return;

	for (const auto &rawMaterial : rawMaterials_)
		warehouse_->removeItem(rawMaterial);
	for (const auto &product : products_)
		warehouse_->addItem(product);
}

void BaseIndustry::deliverGoods(const Goods &goods, BaseIndustry *dest) {
	Route *route = new Route(goods, dest, this);
	garage_->sendVihicle(route);
}

double BaseIndustry::putInStorage(const Goods &goods) {
	return warehouse_->addItem(goods);
}

double BaseIndustry::putOutStorage(const Goods &goods) {
	return warehouse_->removeItem(goods);
}
