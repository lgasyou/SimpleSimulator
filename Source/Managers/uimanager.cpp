/*
 *	Copyright 2017 Li Zeqing
 *
 *	This file is part of World Simulator.
 *	
 *	World Simulator is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU Lesser General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *	
 *	World Simulator is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *	
 *	You should have received a copy of the GNU Lesser General Public License
 *	along with World Simulator.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "uimanager.h"

UIManager::UIManager() { }

UIManager::~UIManager() { }

UIManager &UIManager::instance() {
    static UIManager uiManager;
    return uiManager;
}

BankDialog *UIManager::bankDialog() {
    if (!bankDialog_)
        bankDialog_ = new BankDialog;
    return bankDialog_;
}

BuildingDetailDialog *UIManager::buildingDetailDialog() {
    if (!buildingDetailDialog_)
        buildingDetailDialog_ = new BuildingDetailDialog;
    return buildingDetailDialog_;
}

CompanyDetailDialog *UIManager::companyDetailDialog() {
    if (!companyDetailDialog_)
        companyDetailDialog_ = new CompanyDetailDialog;
    return companyDetailDialog_;
}

SetRouteDialog *UIManager::setRouteDialog() {
    if (!setRouteDialog_)
        setRouteDialog_ = new SetRouteDialog;
    return setRouteDialog_;
}
