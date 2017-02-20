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

	inline const QList<Goods *> &container() const { return this->container_; }

	inline double curVolume() const { return this->curVolume_; }

	inline double freeVolume() const { return maxVolume_ - curVolume_; }

	inline void setMaxVolume(double max) { this->maxVolume_ = max; }
	inline double maxVolume() const { return this->maxVolume_; }

protected:
	// Gets goods' pointer if goods has already exsited.
	// Otherwise creates a new goods object.
	Goods *getGoodsByName(const QString &goods);

protected:
	QList<Goods *> container_;

	double curVolume_;

	double maxVolume_;
};

#endif // !GOODSCONTAINER_H
