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

#ifndef GOODSCONTAINER_H
#define GOODSCONTAINER_H

#include <QList>

struct Goods;

class QString;

using GoodsLabel = QString;

class GoodsContainer {
public:
	GoodsContainer();

	virtual ~GoodsContainer();

	// Queries goods' volume by its label.
	double volumeOf(const QString &goodsName) const;

	Goods *getById(int id);

	// If the goods.volume is smaller or equal to free volume, just adds it.
	// If not, resets addition volume as the free volume of container.
	// Returns final addition.
	double store(const Goods &goods);

	// If the goods.volume is smaller or equal to free volume, just removes it.
	// If not, resets removal volume as the current volume of container.
	// Returns final removal.
	double fetch(const Goods &goods);

	const QList<Goods *> &container() const { return container_; }

	bool isEmpty() const { return container_.isEmpty(); }

	double curVolume() const { return curVolume_; }

	double freeVolume() const { return maxVolume_ - curVolume_; }

	void setMaxVolume(double max) { this->maxVolume_ = max; }
	double maxVolume() const { return maxVolume_; }

protected:
	// Gets pointer of goods if it has been already existed.
	// Otherwise creates a new goods object.
	Goods *getByLabel(const GoodsLabel &label);

protected:
	QList<Goods *> container_;

	double curVolume_ = 0.0;

	double maxVolume_ = 60.0;
};

inline Goods *GoodsContainer::getById(int id) {
	return container_[id];
}

#endif // !GOODSCONTAINER_H
