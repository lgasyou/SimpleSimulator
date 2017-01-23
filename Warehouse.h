#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "GoodsContainer.h"
#include <QMap>

class Warehouse : public GoodsContainer {
public:
	Warehouse();

	const QMap<QString, double> &warehouse() const { return this->container_; }
};

#endif // WAREHOUSE_H
