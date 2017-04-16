/*
 *	Copyright 2017 Li Zeqing
 *
 *	This file is part of World Simulator.
 *	
 *	World Simulator is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU Lesser General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *	
 *	World Simulator is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *	
 *	You should have received a copy of the GNU Lesser General Public License
 *	along with World Simulator.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PERSON_H
#define PERSON_H

#include <QString>

class Person {
public:
	Person(const QString &name = "Hello World");

	~Person();

	void setCash(const double cash) { this->cash_ = cash; }
	double cash() const { return cash_; }

	void setName(const QString &name) { this->name_ = name; }
	const QString &name() const { return name_; }

private:
	double cash_;

	QString name_;
};

#endif // !PERSON_H
