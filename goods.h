#ifndef GOODS_H
#define GOODS_H

#include <QString>

struct Goods {
	Goods(const QString &name_, double volume_);

	QString name;
	double volume;
};

#endif // !GOODS_H

