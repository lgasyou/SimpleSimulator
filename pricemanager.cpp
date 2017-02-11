#include "pricemanager.h"

PriceManager::PriceManager() { }

PriceManager::~PriceManager() { }

PriceManager &PriceManager::instance() {
	static PriceManager priceManager;
	return priceManager;
}

void PriceManager::readFile(const QString &fileName) {
	// TODO
	// Read File.
	fileName;
}

void PriceManager::update() {

}
