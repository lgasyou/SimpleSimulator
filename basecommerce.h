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

#ifndef BASECOMMERCE_H
#define BASECOMMERCE_H

#include "basebuilding.h"

class BaseIndustry;
struct Goods;
class Person;
class QString;
class Warehouse;

//	This class should not be instantiated.
class BaseCommerce : public BaseBuilding {
public:
	BaseCommerce(const QString &name, const QString &type);

	virtual ~BaseCommerce();

	void purchaseCommodity(BaseIndustry *factory, const Goods &goods);

	void sellCommodity(Person *consumer, const Goods &goods);

	// update data after each turn
	void update() override;

private:
	Warehouse *warehouse_;
};

#endif // BASECOMMERCE_H
