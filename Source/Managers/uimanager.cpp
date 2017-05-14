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

#include "uimanager.h"

#include "Source/GUI/bankdialog.h"
#include "Source/GUI/buildingdetaildialog.h"
#include "Source/GUI/companydetaildialog.h"
#include "Source/GUI/setroutedialog.h"
#include "Source/GUI/buildingtablewidget.h"
#include "Source/GUI/helpdialog.h"

std::map<QString, QWidget *> UIManager::uiMap_;

UIManager::UIManager() {
	init();
}

UIManager::~UIManager() {
	for (auto pair : uiMap_)
		delete pair.second;
}

void UIManager::init() {
	//put("BankDialog", new BankDialog);
	put("BuildingDetailDialog", new BuildingDetailDialog);
	put("BuildingTableWidget", new BuildingTableWidget);
	put("CompanyDetailDialog", new CompanyDetailDialog);
	put("HelpDialog", new HelpDialog);
	put("SetRouteDialog", new SetRouteDialog);
}

void UIManager::put(const QString &key, QWidget *value) {
	uiMap_.emplace(key, value);
}

QWidget *UIManager::get(const QString &key) {
	return uiMap_.at(key);
}
