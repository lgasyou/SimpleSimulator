#ifndef GOODS_H
#define GOODS_H

#include <QString>

struct Goods {
	Goods(const QString &goods_, double weight_);

	QString goods;
	double weight;
};

#endif // !GOODS_H

