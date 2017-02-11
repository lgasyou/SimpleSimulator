#ifndef GOODSCONTAINER_H
#define GOODSCONTAINER_H

#include <QList>

struct Goods;

class QString;

class GoodsContainer {
public:
	GoodsContainer();

	virtual ~GoodsContainer();

	const double query(const QString &goodsName) const;

	Goods *getGoodsById(int id);

	// If the goods.volume is smaller or equal to free volume, just adds it.
	// If not, resets addition volume as the free volume of container.
	double addItem(const Goods &goods);

	// If the goods.volume is smaller or equal to free volume, just removes it.
	// If not, resets removal volume as the current volume of container.
	double removeItem(const Goods &goods);

	inline const QList<Goods *> &container() const { return this->container_; }

	inline const double curVolume() const { return this->curVolume_; }

	inline const double freeVolume() const { return maxVolume_ - curVolume_; }

	inline void setMaxVolume(double max) { this->maxVolume_ = max; }
	inline const double maxVolume() const { return this->maxVolume_; }

protected:
	// Gets goods' pointer if goods has already exsited.
	// Otherwise creates a new goods object.
	Goods *getGoodsByName(const QString &goods);

	QList<Goods *> container_;
	double curVolume_;
	double maxVolume_;
};

#endif // !GOODSCONTAINER_H
