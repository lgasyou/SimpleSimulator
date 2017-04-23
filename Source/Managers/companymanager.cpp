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
 *  along with World Simulator.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "companymanager.h"

CompanyManager::CompanyManager() { }

CompanyManager::~CompanyManager() {
    delete playerCompany_;
    for (Company *AICompany : AICompanies_) {
        delete AICompany;
    }
}

CompanyManager &CompanyManager::instance() {
    static CompanyManager companyManager;
    return companyManager;
}

void CompanyManager::init() {
    playerCompany_ = new Company;
}

void CompanyManager::update() {
    playerCompany_->update();
    std::for_each(AICompanies_.begin(), AICompanies_.end(), [](Company *company) { company->update(); });
}