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

#include "industrychainmanager.h"

IndustryChainManager::IndustryChainManager() { }

IndustryChainManager::~IndustryChainManager() { }

void IndustryChainManager::init() {
    // TODO: Move this into a file like .xml
    // then just read file.
    industryChain_.addPath("Coal", "Steel", 2);
    industryChain_.addPath("Iron", "Steel", 1);
    industryChain_.addPath("Log", "Plank", 0.5);
    industryChain_.addPath("Plank", "Product", 1);
    industryChain_.addPath("Steel", "Product", 0.5);
}

IndustryChainManager &IndustryChainManager::instance() {
    static IndustryChainManager industryChainManager;
    return industryChainManager;
}

double IndustryChainManager::cost(const QString &orig, const QString &dest) const {
    return industryChain_.weight(orig, dest);
}

std::vector<Goods> IndustryChainManager::precursors(const QString &item) const {
    return industryChain_.precursors(item);
}

std::vector<Goods> IndustryChainManager::successors(const QString &item) const {
    return industryChain_.successors(item);
}
