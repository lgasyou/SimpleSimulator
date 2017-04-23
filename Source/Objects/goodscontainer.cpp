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

GoodsContainer::GoodsContainer() { }

GoodsContainer::~GoodsContainer() { }

double GoodsContainer::volumeOf(const GoodsLabel &label) const {
    for (const auto item : container_) {
        if (item->label == label)
            return item->volume;
    }
    return 0.0;
}

double GoodsContainer::store(const Goods &goods) {
    double finalAddition = (curVolume_ + goods.volume > maxVolume_) ?
        maxVolume_ - curVolume_ : goods.volume;

    Goods *finalGoods = getByLabel(goods.label);
    finalGoods->label += finalAddition;
    curVolume_ += finalAddition;
    return finalAddition;
}

double GoodsContainer::fetch(const Goods &goods) {
    Goods *curGoods = getByLabel(goods.label);
    double finalRemoval = (curGoods->volume - goods.volume >= 0.0) ?
        goods.volume : curGoods->volume;

    if ((curGoods->volume -= finalRemoval) < 0.01)
        container_.removeOne(curGoods);
    curVolume_ -= finalRemoval;
    return finalRemoval;
}

Goods *GoodsContainer::getByLabel(const GoodsLabel &label) {
    for (auto item : container_) {
        if (item->label == label)
            return item;
    }

    Goods *newGoods = new Goods{ label, 0.0 };
    container_.push_back(newGoods);
    return newGoods;
}
