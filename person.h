#ifndef PERSON_H
#define PERSON_H

#include <QString>

class Person {
public:
	Person(const QString &name = "Hello World");

	~Person();

private:
	QString name_;
};
#endif // !PERSON_H
