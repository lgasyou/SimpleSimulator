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

#include "basecommerce.h"
#include "factory.h"
#include "person.h"
#include "warehouse.h"

#include <QString>

BaseCommerce::BaseCommerce(const QString &name, const QString &type) :
	BaseBuilding(name, type),
	warehouse_(new Warehouse)
{ }

BaseCommerce::~BaseCommerce() { }

void BaseCommerce::restock(BaseIndustry *factory, const Goods &goods) {
	factory->fetch(goods);
}

void BaseCommerce::sellTo(Person *consumer, const Goods &goods) {

}

void BaseCommerce::update() {
	changeBaseValue();
}
