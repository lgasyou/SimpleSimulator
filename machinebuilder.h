#ifndef MACHINEBUILDER_H
#define MACHINEBUILDER_H

class Machine;

class MachineBuilder {
public:
	virtual void setMaximumProductivity() = 0;

	virtual void setProducts() = 0;

	virtual Machine *getMachine() = 0;

protected:
	Machine *machine;
};

#endif // !MACHINEBUILDER_H
