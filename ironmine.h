#ifndef IRONMINE_H
#define IRONMINE_H

#include "baseindustry.h"

class IronMine : public BaseIndustry {
public:
	IronMine();

	~IronMine();

	void manufacture() override;
};
#endif // !IRONMINE_H
