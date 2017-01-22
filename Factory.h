#ifndef FACTORY_H
#define FACTORY_H

class FactoryCargo;
#include "BaseBuilding.h"
#include <QMap>

class Factory : public BaseBuilding {
public:
    Factory(double value);

    Factory(const BaseBuilding &);

    void manage(const QString &) override;

	FactoryCargo *cargo() const { return this->cargo_; }

private:
    FactoryCargo *cargo_;
};

#endif // FACTORY_H
