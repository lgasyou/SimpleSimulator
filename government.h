#ifndef GOVERNMENT_H
#define GOVERNMENT_H

#include "company.h"

class Government : public Company {
public:
	static Government &instance();

	void update();

private:
	Government();

	~Government() { }
};

#endif // !GOVERNMENT_H