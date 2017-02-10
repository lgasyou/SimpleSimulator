#include "graph.h"

#include "goods.h"

void Graph::addVertex(const QString &item) {
	graph_.push_back(Vertex(item, nullptr, nullptr));
}

void Graph::addPath(const QString &begin, const QString &end, double volume) {
	int indexOfBegin = indexOf(begin);
	if (indexOfBegin == -1) {
		addVertex(begin);
		indexOfBegin = (int)graph_.size() - 1;
	}
	int indexOfEnd = indexOf(end);
	if (indexOfEnd == -1) {
		addVertex(end);
		indexOfEnd = (int)graph_.size() - 1;
	}

	Arc *originalOut = graph_[indexOfBegin].firstOut;
	Arc *originalIn = graph_[indexOfEnd].firstIn;
	Arc *newArc = new Arc(volume, indexOfBegin, indexOfEnd, originalOut, originalIn);
	graph_[indexOfBegin].firstOut = newArc;
	graph_[indexOfEnd].firstIn = newArc;
}

double Graph::volume(const QString &begin, const QString &end) const {
	int indexOfBegin = indexOf(begin);
	if (indexOfBegin == -1)
		return -1;

	Arc *arc = graph_[indexOfBegin].firstOut;
	while (arc) {
		int indexOfEnd = arc->tailVertex;
		if (graph_[indexOfEnd].item == end)
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
		ret.push_back(Goods(name, volume));
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
		ret.push_back(Goods(name, volume));
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
