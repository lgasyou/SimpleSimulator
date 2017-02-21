#ifndef MACHINE_H
#define MACHINE_H

#include <vector>

class Warehouse;
struct Goods;

struct MachineSettings {
	MachineSettings(double maximalProductivity_, Warehouse *warehouse_,
		const std::vector<Goods> &products_, const std::vector<Goods> &materials_) :
		maximalProductivity(maximalProductivity_),
		warehouse(warehouse_),
		products(products_),
		rawMaterials(materials_) { }

	double maximalProductivity;
	Warehouse *warehouse;
	std::vector<Goods> products;
	std::vector<Goods> rawMaterials;
};

class Machine {
public:
	Machine();

	~Machine();

	void init();

	double currentProductivity() const { return this->currentProductivity_; }

	void produce();

	void setMaximalProductivity(double maximalProductivity);
	double maximalProductivity() const { return this->maximalProductivity_; }

	void setWarehouse(Warehouse *warehouse) { this->warehouse_ = warehouse; }

	void setParameters(const MachineSettings &settings);

	const std::vector<Goods> &products() const { return this->products_; }

	const std::vector<Goods> &materials() const { return this->materials_; }

private:
	double currentProductivity_;

	double maximalProductivity_;

	Warehouse *warehouse_;

	std::vector<Goods> products_;

	std::vector<Goods> materials_;
};

#endif // !MACHINE_H
