#include "pricemanager.h"

PriceManager::PriceManager() {
	init();
}

PriceManager::~PriceManager() { }

void PriceManager::init() {
	prices_.push_back(PriceItem("Coal", "ton", 10));
	prices_.push_back(PriceItem("Iron", "ton", 10));
	prices_.push_back(PriceItem("Steel", "ton", 35));
}

PriceManager &PriceManager::instance() {
	static PriceManager priceManager;
	return priceManager;
}

double PriceManager::price(const QString &name) const {
	for (const auto &item : prices_)
		if (item.name == name)
			return item.price;
	return 0.0;
}

void PriceManager::update() {

}