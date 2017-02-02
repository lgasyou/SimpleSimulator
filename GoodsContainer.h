#ifndef GOODSCONTAINER_H
#define GOODSCONTAINER_H

#include <QMap>
#include <QString>

class GoodsContainer {
public:
	GoodsContainer();

	virtual ~GoodsContainer();

	const double query(const QString &item);

	bool addItem(const QString &, double);
	void removeItem(const QString &, double);

	inline const double curVolume() const { return this->curVolume_; }

	inline void setMaxVolume(double max) { this->maxVolume_ = max; }
	inline const double maxVolume() const { return this->maxVolume_; }

	inline const QMap<QString, double> &container() const { return this->container_; }

protected:
	QMap<QString, double> container_;
	double maxVolume_;
	double curVolume_;
};

#endif // !GOODSCONTAINER_H