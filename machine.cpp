#include "machine.h"
#include "goods.h"
#include "warehouse.h"
#include "gameconstants.h"
#include "industrychainmanager.h"

Machine::Machine() { }

Machine::~Machine() { }

void Machine::produce() {
	// Finds the limit factor of producing goods.
	int limitFactor = maximalProductivity();
	for (const auto &rawMaterial : materials_) {
		double stock = warehouse_->query(rawMaterial.name);
		int ratio = static_cast<int>(stock / rawMaterial.volume);
		if (ratio < limitFactor)
			limitFactor = ratio;
	}

	// Produces several goods.
	for (const auto &material : materials_) {
		Goods finalMaterial = material;
		finalMaterial.volume *= limitFactor;
		warehouse_->removeItem(finalMaterial);
	}
	Goods finalProduct = { currentProduct_, 0.0 };
	finalProduct.volume *= limitFactor;
	warehouse_->addItem(finalProduct);
	currentProductivity_ = limitFactor;
}

void Machine::setMaximalProductivity(double maximalProductivity) {
	this->maximalProductivity_ = maximalProductivity;
}

void Machine::setCurrentProduct(const QString &product) {
	materials_ = IndustryChainManager::instance().precursors(product);
	this->currentProduct_ = product;
}

void Machine::setProducts(const std::vector<Goods> &products) {
	this->products_ = products;
	this->currentProduct_ = products[0].name;
}
