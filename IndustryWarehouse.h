#ifndef INDUSTRYWAREHOUSE_H
#define INDUSTRYWAREHOUSE_H

#include <QMap>

class IndustryWarehouse {
public:
    IndustryWarehouse();

    bool addItem(const QString &, double);
    void removeItem(const QString &, double);

	const QMap<QString, double> &warehouse() const { return this->warehouse_; }

    const double curVolume() const { return this->curVolume_; }

    void setMaxVolume(double max) { this->maxVolume_ = max; }
    const double maxVolume() const { return this->maxVolume_; }

private:
    QMap<QString, double> warehouse_;
    double maxVolume_;
    double curVolume_;
};

#endif // INDUSTRYWAREHOUSE_H
