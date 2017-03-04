#include "machine.h"
#include "goods.h"
#include "warehouse.h"
#include "gameconstants.h"

Machine::Machine() { 
	init();
}

Machine::~Machine() { }

void Machine::init() {
	currentProductivity_ = 0.0;
	maximalProductivity_ = 0.0;
	warehouse_ = nullptr;
}

void Machine::produce() {
	// Finds the limit factor of producing goods.
	int limitFactor = GameConstants::integerMaximum;
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
	for (const auto &product : products_) {
		Goods finalProduct = product;
		finalProduct.volume *= limitFactor;
		warehouse_->addItem(finalProduct);
	}
	currentProductivity_ = limitFactor;
}

void Machine::setMaximalProductivity(double maximalProductivity) {
	this->maximalProductivity_ = maximalProductivity;
}

void Machine::setParameters(const MachineSettings &settings) {
	this->maximalProductivity_ = settings.maximalProductivity;
	this->warehouse_ = settings.warehouse;
	this->products_ = settings.products;
	this->materials_ = settings.rawMaterials;
}

