#ifndef BASETRANSPORTATION_H
#define BASETRANSPORTATION_H

#include "basebuilding.h"

class QString;

class BaseTransportation : public BaseBuilding {
public:
	BaseTransportation(const QString &name, const QString &type);

	virtual ~BaseTransportation();

private:

};

#endif // !BASETRANSPORTATION_H
