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

private:
    FactoryCargo *cargo_;
};

#endif // FACTORY_H
