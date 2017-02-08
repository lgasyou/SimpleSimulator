#include "baseindustry.h"
#include "warehouse.h"
#include "garage.h"
#include "order.h"
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
	for (auto &rawMaterial : rawMaterials_)
		if (rawMaterial.weight > warehouse_->query(rawMaterial.goods))
			return;

	for (auto &rawMaterial : rawMaterials_)
		warehouse_->removeItem(rawMaterial);
	for (auto &product : products_)
		warehouse_->addItem(product);
}

void BaseIndustry::deliverGoods(const Goods &goods, BaseIndustry *dest) {
	Order *order = new Order(goods, dest, this);
	garage_->sendVihicle(order);
}

void BaseIndustry::putInStorage(const Goods &goods) {
	warehouse_->addItem(goods);
}

void BaseIndustry::putOutStorage(const Goods &goods) {
	warehouse_->removeItem(goods);
}
