#ifndef FACTORY_H
#define FACTORY_H

#include "baseindustry.h"

class QString;

class Factory : public BaseIndustry {
public:
	Factory(const QString &name = "Factory");
};

#endif // !FACTORY_H
