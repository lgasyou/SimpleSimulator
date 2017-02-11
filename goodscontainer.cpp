#include "goodscontainer.h"
#include "gameconstants.h"
#include "goods.h"

#include <QString>

GoodsContainer::GoodsContainer() :
	maxVolume_(GameConstants::defaultMaxVolOfWarehouse),
	curVolume_(0.0)
{ }

GoodsContainer::~GoodsContainer() { }

double GoodsContainer::query(const QString &goodsName) const {
	for (const auto &item : container_) {
		if (item->name == goodsName)
			return item->volume;
	}
	return 0.0;
}

Goods *GoodsContainer::getGoodsById(int id) {
	return container_[id];
}

double GoodsContainer::addItem(const Goods &goods) {
	double finalAddition = (curVolume_ + goods.volume > maxVolume_) ?
		maxVolume_ - curVolume_ : goods.volume;

	getGoodsByName(goods.name)->volume += finalAddition;
	curVolume_ += finalAddition;
	return finalAddition;
}

double GoodsContainer::removeItem(const Goods &goods) {
	Goods *curGoods = getGoodsByName(goods.name);
	double finalRemoval = (curGoods->volume - goods.volume >= 0.0) ?
		goods.volume : curGoods->volume;

	if ((curGoods->volume -= finalRemoval) == 0.0)
		container_.removeOne(curGoods);
	curVolume_ -= finalRemoval;
	return finalRemoval;
}

Goods *GoodsContainer::getGoodsByName(const QString &goods) {
	for (auto &item : container_) {
		if (item->name == goods)
			return item;
	}

	Goods *newGoods = new Goods(goods, 0.0);
	container_.push_back(newGoods);
	return newGoods;
}
