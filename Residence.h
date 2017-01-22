#ifndef RESIDENCE_H
#define RESIDENCE_H

#include "BaseBuilding.h"

class Residence : public BaseBuilding {
public:
    Residence(double value);

    Residence(const BaseBuilding &);

    void manage(const QString &) override;
};

#endif // RESIDENCE_H
