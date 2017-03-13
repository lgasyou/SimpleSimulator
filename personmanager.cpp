#include "personmanager.h"

PersonManager &PersonManager::instance() {
	static PersonManager personManager;
	return personManager;
}

void PersonManager::init() { }

void PersonManager::addItem(Person *) { }

void PersonManager::removeItem(Person *) { }

void PersonManager::update() { }

PersonManager::PersonManager() { }

PersonManager::~PersonManager() { }