#include "machinemanager.h"
#include "machinebuilder.h"

MachineManager::MachineManager() { }

MachineManager::~MachineManager() { }

MachineManager &MachineManager::instance() {
	static MachineManager machineManager;
	return machineManager;
}

Machine *MachineManager::machine(MachineBuilder *builder) {
	builder->setMaximumProductivity();
	builder->setProducts();
	return builder->getMachine();
}
