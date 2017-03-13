#include "defaultmachinebuilder.h"
#include "machine.h"
#include "goods.h"

DefaultMachineBuilder::DefaultMachineBuilder() {
	machine = new Machine;
}

void DefaultMachineBuilder::setMaximumProductivity() {
	machine->setMaximalProductivity(1.0);
}

void DefaultMachineBuilder::setProducts() {
	machine->setProducts({ Goods("Steel", 1) });
}

Machine *DefaultMachineBuilder::getMachine() {
	return machine;
}
