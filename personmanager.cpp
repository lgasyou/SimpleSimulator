#include "personmanager.h"

PersonManager &PersonManager::instance() {
	static PersonManager personManager;
	return personManager;
}

void PersonManager::init() { }

void PersonManager::add(Person *) { }

void PersonManager::remove(Person *) { }

void PersonManager::update() { }

PersonManager::PersonManager() { }

PersonManager::~PersonManager() { }