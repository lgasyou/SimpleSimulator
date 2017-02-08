#ifndef GRAPH_H
#define GRAPH_H

#include "goods.h"
#include <vector>
#include <QString>

struct Arc {
	Arc(double weight_, int headVertex_, int tailVertex_, Arc *headArc_, Arc *tailArc_) :
		weight(weight_),
		headVertex(headVertex_),
		tailVertex(tailVertex_),
		headArc(headArc_),
		tailArc(tailArc_)
	{ }

	double weight;
	int headVertex;
	int tailVertex;
	Arc *headArc;
	Arc *tailArc;
};

struct Vertex {
	Vertex(const QString &item_, Arc *firstIn_, Arc *firstOut_) :
		item(item_),
		firstIn(firstIn_),
		firstOut(firstOut_)
	{ }

	QString item;
	Arc *firstIn;
	Arc *firstOut;
};

class Graph {
public:
	void addVertex(const QString &item);

	void addPath(const QString &begin, const QString &end, double weight);

	double weight(const QString &begin, const QString &end) const;

	std::vector<Goods> precursors(const QString &item) const;

	std::vector<Goods> successors(const QString &item) const;

	int indexOf(const QString &) const;

private:
	std::vector<Vertex> graph_;
};

#endif // !GRAPH_H
