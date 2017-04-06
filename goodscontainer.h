#ifndef GOODSCONTAINER_H
#define GOODSCONTAINER_H

#include <QList>

struct Goods;

class QString;

class GoodsContainer {
public:
	GoodsContainer();

	virtual ~GoodsContainer();

	// Queries goods' volume by its name.
	double query(const QString &goodsName) const;

	Goods *getGoodsById(int id);

	// If the goods.volume is smaller or equal to free volume, just adds it.
	// If not, resets addition volume as the free volume of container.
	// Returns final addition.
	double addItem(const Goods &goods);

	// If the goods.volume is smaller or equal to free volume, just removes it.
	// If not, resets removal volume as the current volume of container.
	// Returns final removal.
	double removeItem(const Goods &goods);

	const QList<Goods *> &container() const { return container_; }

	double curVolume() const { return curVolume_; }

	double freeVolume() const { return maxVolume_ - curVolume_; }

	void setMaxVolume(double max) { this->maxVolume_ = max; }
	double maxVolume() const { return maxVolume_; }

protected:
	// Gets goods' pointer if goods has already existed.
	// Otherwise creates a new goods object.
	Goods *getGoodsByName(const QString &goods);

protected:
	QList<Goods *> container_;

	double curVolume_ = 0.0;

	double maxVolume_;
};

#endif // !GOODSCONTAINER_H
