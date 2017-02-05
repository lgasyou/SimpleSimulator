#ifndef IRONMINE_H
#define IRONMINE_H

#include "industry.h"

class IronMine : public Industry {
public:
	IronMine();

	~IronMine();

	void manufacture() override;
};
#endif // !IRONMINE_H
