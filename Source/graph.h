/*
 *  Copyright 2017 Li Zeqing
 *  
 *  This file is part of World Simulator.
 *  
 *  World Simulator is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  World Simulator is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with World Simulator.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <QString>

#include "Source/Objects/goods.h"

/* Arc of Graph */
struct Arc {
    double volume;
    
    int headVertex;
    
    int tailVertex;
    
    Arc *headArc;
    
    Arc *tailArc;
};


/* Vertex of Graph */
struct Vertex {
    QString item;
    
    Arc *firstIn;
    
    Arc *firstOut;
};



class Graph {
public:
    void addVertex(const QString &item);
    
    void addPath(const QString &orig, const QString &dest, double volume);
    
    double weight(const QString &orig, const QString &dest) const;
    
    std::vector<Goods> precursors(const QString &item) const;
    
    std::vector<Goods> successors(const QString &item) const;
    
    int indexOf(const QString &) const;

private:
    std::vector<Vertex> graph_;
};

#endif // !GRAPH_H
