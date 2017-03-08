#ifndef PERSON_H
#define PERSON_H

#include <QString>

class Person {
public:
	Person(const QString &name = "Hello World");

	~Person();

	void setCash(const double cash) { this->cash_ = cash; }
	double cash() const { return this->cash_; }

	void setName(const QString &name) { this->name_ = name; }
	const QString &name() const { return this->name_; }

private:
	double cash_;

	QString name_;
};

#endif // !PERSON_H
