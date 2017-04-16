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

#ifndef COMPANY_H
#define COMPANY_H

#include <QString>

class BaseBuilding;

class Company {
public:
    Company(const QString &name = "Xenon Inc.");

	~Company();

	// Buys building if company's money is enough:
	// Changes building's owner as this company.
	// Deducts company's cash.
    bool phrchase(BaseBuilding *building);

	bool purchase(double cost);

	// Changes building's owner as government's pointer.
	// Adds company's cash.
    bool sell(BaseBuilding *building);

    void update();

    void setCash(const double cash) { this->cash_ = cash; }
    double cash() const { return cash_; }

    void setLiability(const double liability) { this->liability_ = liability; }
    double liability() const { return liability_; }

    void setName(const QString &name) { this->name_ = name; }
    const QString &name() const { return name_; }

	void setTotalValue(const double totalValue) { this->totalValue_ = totalValue; }
	double totalValue() const { return totalValue_; }

protected:
    double cash_ = 1000.0;

    double liability_ = 0.0;

    QString name_;

	// Records the total value of company,
	// includes the value of properties.
    double totalValue_ = 1000.0;
};

#endif // COMPANY_H
