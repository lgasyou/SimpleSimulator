#ifndef MACHINEMANAGER_H
#define MACHINEMANAGER_H

class Machine;

#include "machinebuilder.h"

class MachineManager {
public:
	static MachineManager &instance();

	Machine *machine(MachineBuilder *builder);

private:
	MachineManager();

	~MachineManager();

	MachineManager(const MachineManager &) = delete;

	MachineManager &operator=(const MachineManager &) = delete;
};

#endif // !MACHINEMANAGER_H
