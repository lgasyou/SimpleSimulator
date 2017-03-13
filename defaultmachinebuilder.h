#ifndef DEFAULTMACHINEBUILDER_H
#define DEFAULTMACHINEBUILDER_H

#include "machinebuilder.h"

class DefaultMachineBuilder : public MachineBuilder {
public:
	DefaultMachineBuilder();

	void setMaximumProductivity();

	void setProducts();

	Machine *getMachine();
};

#endif // !DEFAULTMACHINEBUILDER_H