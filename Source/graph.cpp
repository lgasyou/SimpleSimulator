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

#include "graph.h"
#include "goods.h"

#include <QString>

using namespace DataStructure;

void Graph::addVertex(const QString &item) {
	graph_.push_back(Vertex{ item, nullptr, nullptr });
}

void Graph::addPath(const QString &orig, const QString &dest, double volume) {
	int indexOfOrig = indexOf(orig);
	if (indexOfOrig == -1) {
		addVertex(orig);
		indexOfOrig = (int)graph_.size() - 1;
	}
	int indexOfDest = indexOf(dest);
	if (indexOfDest == -1) {
		addVertex(dest);
		indexOfDest = (int)graph_.size() - 1;
	}

	Arc *originalOut = graph_[indexOfOrig].firstOut;
	Arc *originalIn = graph_[indexOfDest].firstIn;
	Arc *newArc = new Arc{ volume, indexOfOrig, indexOfDest, originalOut, originalIn };
	graph_[indexOfOrig].firstOut = newArc;
	graph_[indexOfDest].firstIn = newArc;
}

double Graph::weight(const QString &orig, const QString &dest) const {
	int indexOfOrig = indexOf(orig);
	if (indexOfOrig == -1)
		return -1;

	Arc *arc = graph_[indexOfOrig].firstOut;
	while (arc) {
		int indexOfDest = arc->tailVertex;
		if (graph_[indexOfDest].item == dest)
			return arc->volume;
		arc = arc->headArc;
	}
	return -1;
}

std::vector<Goods> Graph::precursors(const QString &item) const {
	int indexOfItem = indexOf(item);
	if (indexOfItem == -1)
		return std::vector<Goods>();

	std::vector<Goods> ret;
	Arc *arc = graph_[indexOfItem].firstIn;
	while (arc) {
		const QString &name = graph_[arc->headVertex].item;
		double volume = arc->volume;
		ret.push_back(Goods{ name, volume });
		arc = arc->tailArc;
	}
	return ret;
}

std::vector<Goods> Graph::successors(const QString &item) const {
	int indexOfItem = indexOf(item);
	if (indexOfItem == -1)
		return std::vector<Goods>();

	std::vector<Goods> ret;
	Arc *arc = graph_[indexOfItem].firstOut;
	while (arc) {
		const QString &name = graph_[arc->tailVertex].item;
		double volume = arc->volume;
		ret.push_back(Goods{ name, volume });
		arc = arc->headArc;
	}
	return ret;
}

int Graph::indexOf(const QString &item) const {
	int i = (int)graph_.size() - 1;
	while (i != -1 && graph_[i].item != item)
		--i;
	return i;
}
