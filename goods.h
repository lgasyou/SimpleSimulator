#ifndef GOODS_H
#define GOODS_H

#include <QString>

struct Goods {
	bool operator==(const Goods &rhs) {
		return name == rhs.name && volume == rhs.volume;
	}

	QString name;

	double volume;
};

#endif // !GOODS_H

