#ifndef STEELFACTORY_H
#define STEELFACTORY_H

#include "baseindustry.h"

class SteelFactory : public BaseIndustry {
public:
	SteelFactory();

	~SteelFactory();

	void manufacture() override;
};
#endif // !STEELFACTORY_H
