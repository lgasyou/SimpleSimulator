#ifndef GOODSCONTAINER_H
#define GOODSCONTAINER_H

#include <QList>
#include <QString>
#include "goods.h"

class GoodsContainer {
public:
	GoodsContainer();

	virtual ~GoodsContainer();

	const double query(const QString &goodsName) const;

	Goods *getGoodsById(int id);

	bool addItem(const Goods &goods);
	void removeItem(const Goods &goods);

	inline const QList<Goods *> &container() const { return this->container_; }

	inline const double curVolume() const { return this->curVolume_; }

	inline void setMaxVolume(double max) { this->maxVolume_ = max; }
	inline const double maxVolume() const { return this->maxVolume_; }

protected:
	Goods *getGoodsByName(const QString &goods);

	QList<Goods *> container_;
	double curVolume_;
	double maxVolume_;
};

#endif // !GOODSCONTAINER_H