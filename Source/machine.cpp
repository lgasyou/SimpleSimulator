/*
 *	Copyright 2017 Li Zeqing
 *
 *	This file is part of World Simulator.
 *	
 *	World Simulator is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU Lesser General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *	
 *	World Simulator is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *	
 *	You should have received a copy of the GNU Lesser General Public License
 *	along with World Simulator.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "machine.h"
#include "goods.h"
#include "warehouse.h"
#include "gameconstants.h"
#include "industrychainmanager.h"

Machine::Machine() { }

Machine::~Machine() { }

void Machine::produce() {
	double limitFactor = getProduceLimitFactor();
	fetchMaterialByLimitFactor(limitFactor);
	Goods finalProduct = { currentProduct_, 1.0 };
	finalProduct.volume *= limitFactor;
	warehouse_->store(finalProduct);
	currentProductivity_ = limitFactor;
}

void Machine::setCurrentProduct(const QString &product) {
	materials_ = IndustryChainManager::instance().precursors(product);
	this->currentProduct_ = product;
}

void Machine::setProducts(const std::vector<Goods> &products) {
	this->products_ = products;
	this->currentProduct_ = products[0].label;
}

double Machine::getProduceLimitFactor() const {
	int limitFactor = maximalProductivity();
	for (const auto &rawMaterial : materials_) {
		double stock = warehouse_->volumeOf(rawMaterial.label);
		int ratio = static_cast<int>(stock / rawMaterial.volume);
		if (ratio < limitFactor)
			limitFactor = ratio;
	}
	return limitFactor;
}

void Machine::fetchMaterialByLimitFactor(double limitFactor) {
	for (const auto &material : materials_) {
		Goods finalMaterial = material;
		finalMaterial.volume *= limitFactor;
		warehouse_->fetch(finalMaterial);
	}
}
