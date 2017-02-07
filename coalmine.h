#ifndef COALMINE_H
#define COALMINE_H

#include "baseindustry.h"

class CoalMine : public BaseIndustry {
public:
	CoalMine();

	~CoalMine();

	void manufacture() override;
};

#endif // !COALMINE_H
