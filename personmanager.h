#ifndef PERSONMANAGER_H
#define PERSONMANAGER_H

#include <list>

class Person;

class PersonManager {
public:
	static PersonManager &instance();

	void init();

	void addItem(Person *);

	void removeItem(Person *);

	void update();

private:
	PersonManager();

	~PersonManager();

	PersonManager(const PersonManager &) = delete;

	PersonManager &operator=(const PersonManager &) = delete;

private:
	std::list<Person *> personList_;
};

#endif // !PERSONMANAGER_H
