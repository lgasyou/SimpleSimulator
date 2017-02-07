#include "goodscontainer.h"
#include "gameconstants.h"
#include "goods.h"

GoodsContainer::GoodsContainer() :
	maxVolume_(GameConstants::defaultMaxVolOfWarehouse),
	curVolume_(0.0)
{ }

GoodsContainer::~GoodsContainer() { }

const double GoodsContainer::query(const QString &goodsName) const {
	for (const auto &item : container_) {
		if (item->goods == goodsName)
			return item->weight;
	}
	return 0.0;
}

Goods *GoodsContainer::getGoodsById(int id) {
	return container_[id];
}

bool GoodsContainer::addItem(const Goods &goods) {
	// The space is full
	if (curVolume_ + goods.weight > maxVolume_)
		return false;
	
	getGoodsByName(goods.goods)->weight += goods.weight;
	curVolume_ += goods.weight;
	return true;
}

void GoodsContainer::removeItem(const Goods &goods) {
	Goods *curGoods = getGoodsByName(goods.goods);
	if ((curGoods->weight -= goods.weight) == 0.0)
		container_.removeOne(curGoods);
	curVolume_ -= goods.weight;
}

Goods *GoodsContainer::getGoodsByName(const QString &goods) {
	for (auto &item : container_) {
		if (item->goods == goods)
			return item;
	}

	Goods *newGoods = new Goods(goods, 0.0);
	container_.push_back(newGoods);
	return newGoods;
}
