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

#ifndef PRICE_MANAGER_H
#define PRICE_MANAGER_H

#include <map>

#include "Source/Objects/Goods.h"

// Item of Price
struct PriceItem {
    QString unit;

    double price;
};

// Controls the Price of goods in the game.
// It adjusts the prices dynamically according to the supply-demand relationship.
class PriceManager {
public:
    // Gets single instance.
    static PriceManager &instance();

    void init();
    
    double currentPrice(const GoodsLabel &label) const;

    // Updates the prices of all goods.
    void update();

private:
    // Hides constructor and destructor.
    PriceManager();

    ~PriceManager();

private:
    std::map<GoodsLabel, PriceItem> priceMap_;
};

inline double PriceManager::currentPrice(const GoodsLabel &label) const {
    return priceMap_.find(label)->second.price;
}

#endif // !PRICE_MANAGER_H

