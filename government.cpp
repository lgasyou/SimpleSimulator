#include "government.h"

#include <cstdlib>

Government::Government() :
	Company("Government")
{
	update();
}

Government &Government::instance() {
	static Government governement;
	return governement;
}

void Government::update() {
	this->cash_ = INT_MAX;
	this->totalValue_ = INT_MAX;
}