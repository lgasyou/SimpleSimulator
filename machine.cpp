#include "machine.h"
#include "goods.h"
#include "warehouse.h"
#include "gameconstants.h"
#include "industrychainmanager.h"

Machine::Machine() { 
	init();
}

Machine::Machine(const MachineSettings &settings) {
	init();
	setParameters(settings);
}

Machine::~Machine() { }

void Machine::init() {
	currentProductivity_ = 0.0;
	maximalProductivity_ = 1.0;
	warehouse_ = nullptr;
}

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
	Goods finalProduct = currentProduct_;
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

void Machine::setParameters(const MachineSettings &settings) {
	this->maximalProductivity_ = settings.maximalProductivity;
	setCurrentProduct(settings.currentProduct);
	this->warehouse_ = settings.warehouse;
	this->products_ = settings.products;
}

