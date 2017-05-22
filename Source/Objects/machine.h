/*
 *  Copyright 2017 Li Zeqing
 *
 *  This file is part of World Simulator.
 *  
 *  World Simulator is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  World Simulator is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with World Simulator. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MACHINE_H
#define MACHINE_H

#include <vector>

#include "Warehouse.h"
#include "Goods.h"

class Machine {
public:
    Machine();

    ~Machine();

    double currentProductivity() const { return currentProductivity_; }

    void produce();

public:
    void setMaximalProductivity(double maximalProductivity);
    double maximalProductivity() const { return maximalProductivity_; }

    void setCurrentProduct(const GoodsLabel &product);
    const GoodsLabel &currentProduct() const { return currentProduct_; }

    void setWarehouse(Warehouse *warehouse) { this->warehouse_ = warehouse; }

    void setProducts(const std::vector<Goods> &products);
    const std::vector<Goods> &products() const { return products_; }

    const std::vector<Goods> &materials() const { return materials_; }

private:
    double getProduceLimitFactor() const;

    void fetchMaterialByLimitFactor(double limitFactor);

private:
    double currentProductivity_ = 0.0;

    double maximalProductivity_ = 1.0;

    GoodsLabel currentProduct_;

    Warehouse *warehouse_ = nullptr;

    std::vector<Goods> products_;

    std::vector<Goods> materials_;
};

inline void Machine::setMaximalProductivity(double maximalProductivity) {
    this->maximalProductivity_ = maximalProductivity;
}

#endif // !MACHINE_H
