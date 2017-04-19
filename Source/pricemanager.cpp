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

#include "pricemanager.h"

PriceManager::PriceManager() { }

PriceManager::~PriceManager() { }

void PriceManager::init() {
	prices_.push_back(PriceItem{ "Coal", "ton", 10 });
	prices_.push_back(PriceItem{ "Iron", "ton", 10 });
	prices_.push_back(PriceItem{ "Steel", "ton", 35 });
}

PriceManager &PriceManager::instance() {
	static PriceManager priceManager;
	return priceManager;
}

double PriceManager::currentPrice(const QString &name) const {
	for (const auto &item : prices_)
		if (item.name == name)
			return item.price;
	return 0.0;
}

void PriceManager::update() {

}