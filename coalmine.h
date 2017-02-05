#ifndef COALMINE_H
#define COALMINE_H

#include "industry.h"

class CoalMine : public Industry {
public:
	CoalMine();

	~CoalMine();

	void manufacture() override;
};

#endif // !COALMINE_H
