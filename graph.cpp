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
