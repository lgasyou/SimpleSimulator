#ifndef GRAPH_H
#define GRAPH_H

#include "goods.h"
#include <vector>

class QString;

namespace DataStructure {


struct Arc {
	double volume;

	int headVertex;

	int tailVertex;

	Arc *headArc;

	Arc *tailArc;
};



struct Vertex {
	QString item;

	Arc *firstIn;

	Arc *firstOut;
};


}



class Graph {
public:
	void addVertex(const QString &item);

	void addPath(const QString &orig, const QString &dest, double volume);

	double weight(const QString &orig, const QString &dest) const;

	std::vector<Goods> precursors(const QString &item) const;

	std::vector<Goods> successors(const QString &item) const;

	int indexOf(const QString &) const;

private:
	std::vector<DataStructure::Vertex> graph_;
};

#endif // !GRAPH_H
