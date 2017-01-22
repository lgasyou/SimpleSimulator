#ifndef FACTORYCARGO_H
#define FACTORYCARGO_H

#include <QMap>

class FactoryCargo {
public:
    FactoryCargo();

    bool add(const QString &, double);
    void remove(const QString &, double);

    const double curVolume() const { return this->curVolume_; }

    void setMaxVolume(double max) { this->maxVolume_ = max; }
    const double maxVolume() const { return this->maxVolume_; }

private:
    QMap<QString, double> cargo_;
    double maxVolume_;
    double curVolume_;
};

#endif // FACTORYCARGO_H
