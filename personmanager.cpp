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

std::list<Person*>::iterator PersonManager::iteratorOf(Person *person) {
	auto &iterator = personList_.begin();
	while (iterator != personList_.end() && *iterator != person)
		++iterator;
	return iterator;
}
