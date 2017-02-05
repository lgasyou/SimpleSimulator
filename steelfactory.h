#ifndef STEELFACTORY_H
#define STEELFACTORY_H

#include "industry.h"

class SteelFactory : public Industry {
public:
	SteelFactory();

	~SteelFactory();

	void manufacture() override;
};
#endif // !STEELFACTORY_H
