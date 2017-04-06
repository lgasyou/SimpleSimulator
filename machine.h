#ifndef MACHINE_H
#define MACHINE_H

#include <vector>
#include <QString>

class Warehouse;
struct Goods;

class Machine {
public:
	Machine();

	~Machine();

	double currentProductivity() const { return currentProductivity_; }

	void produce();

	void setMaximalProductivity(double maximalProductivity);
	double maximalProductivity() const { return maximalProductivity_; }

	void setCurrentProduct(const QString &product);
	const QString &currentProduct() const { return currentProduct_; }

	void setWarehouse(Warehouse *warehouse) { this->warehouse_ = warehouse; }

	void setProducts(const std::vector<Goods> &products);
	const std::vector<Goods> &products() const { return products_; }

	const std::vector<Goods> &materials() const { return materials_; }

private:
	double currentProductivity_ = 0.0;

	double maximalProductivity_ = 1.0;

	QString currentProduct_;

	Warehouse *warehouse_ = nullptr;

	std::vector<Goods> products_;

	std::vector<Goods> materials_;
};

#endif // !MACHINE_H
