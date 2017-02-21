#ifndef GOODS_H
#define GOODS_H

#include <QString>

struct Goods {
	Goods(const QString &name_ = QString(), double volume_ = 0.0);

	QString name;

	double volume;
};

#endif // !GOODS_H

