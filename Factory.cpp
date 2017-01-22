#include "Factory.h"
#include "FactoryCargo.h"

Factory::Factory(double value) :
    BaseBuilding("Factory", value, "Factory", nullptr),
    cargo_(new FactoryCargo)
{ }

Factory::Factory(const BaseBuilding &rhs) :
    BaseBuilding(rhs.name(), rhs.value(), "Factory", rhs.owner(), rhs.deltaValue()),
    cargo_(new FactoryCargo)
{ }

void Factory::manage(const QString &cmd) {
}

void Factory::update() { 
	manufacture();
}

void Factory::manufacture() {
	if (this->type() == "Iron Mine") {
		cargo_->add("Iron", 1);
	} else if (this->type() == "Coal Mine") {
		cargo_->add("Coal", 2);
	} else if (this->type() == "Steel Factory") {
		cargo_->add("Stell", 1);
		cargo_->remove("Iron", 1);
		cargo_->remove("Coal", 2);
	}
}
