#pragma once

#include <QMap>
#include <QString>

class GoodsContainer {
public:
	GoodsContainer();

	virtual ~GoodsContainer();

	bool addItem(const QString &, double);
	void removeItem(const QString &, double);

	const double curVolume() const { return this->curVolume_; }

	void setMaxVolume(double max) { this->maxVolume_ = max; }
	const double maxVolume() const { return this->maxVolume_; }

protected:
	QMap<QString, double> container_;
	double maxVolume_;
	double curVolume_;
};