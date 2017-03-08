#include "government.h"
#include "gameconstants.h"

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
	this->cash_ = GameConstants::integerMaximum;
	this->totalValue_ = GameConstants::integerMaximum;
}