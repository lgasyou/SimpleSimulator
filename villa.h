#ifndef VILLA_H
#define VILLA_H

#include "baseresidence.h"

class QString;

class Villa : public BaseResidence {
public:
	Villa(const QString &name = "Villa");

	~Villa();
};

#endif // !VILLA_H
