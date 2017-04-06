#ifndef BASERESIDENCE_H
#define BASERESIDENCE_H

#include "basebuilding.h"
#include <list>

class Person;

class QString;

//	This class should not be instantiated.
class BaseResidence : public BaseBuilding {
public:
    BaseResidence(const QString &name, const QString &type);

	virtual ~BaseResidence();

	// updates data after each turn
	void update() override;

	void checkin(Person *resident);

	void checkout(Person *resident);

	const std::list<Person *> &residentList() const { return residentList_; }

protected:
	std::list<Person *> residentList_;
};

#endif // BASERESIDENCE_H
