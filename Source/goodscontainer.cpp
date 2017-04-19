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

#include "goodscontainer.h"
#include "gameconstants.h"
#include "goods.h"

#include <QString>

GoodsContainer::GoodsContainer() :
	maxVolume_(GameConstants::defaultMaxVolOfWarehouse)
{ }

GoodsContainer::~GoodsContainer() { }

double GoodsContainer::query(const QString &goodsName) const {
	for (const auto item : container_) {
		if (item->name == goodsName)
			return item->volume;
	}
	return 0.0;
}

double GoodsContainer::add(const Goods &goods) {
	double finalAddition = (curVolume_ + goods.volume > maxVolume_) ?
		maxVolume_ - curVolume_ : goods.volume;

	getByName(goods.name)->volume += finalAddition;
	curVolume_ += finalAddition;
	return finalAddition;
}

double GoodsContainer::remove(const Goods &goods) {
	Goods *curGoods = getByName(goods.name);
	double finalRemoval = (curGoods->volume - goods.volume >= 0.0) ?
		goods.volume : curGoods->volume;

	if ((curGoods->volume -= finalRemoval) < 0.01)
		container_.removeOne(curGoods);
	curVolume_ -= finalRemoval;
	return finalRemoval;
}

Goods *GoodsContainer::getByName(const QString &stringName) {
	for (auto item : container_) {
		if (item->name == stringName)
			return item;
	}

	Goods *newGoods = new Goods{ stringName, 0.0 };
	container_.push_back(newGoods);
	return newGoods;
}