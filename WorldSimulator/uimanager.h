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

#ifndef UIMANAGER_H
#define UIMANAGER_H

class BankDialog;
class BuildingDetailDialog;
class CompanyDetailDialog;
class SetRouteDialog;

// For now this class is only the prototype of UIManager.
// It returns the UI components by its methods.
// But in fact, I don't understand what should it be used for.
// deprecated.
class UIManager {
public:
	// Use singleton pattern.
	static UIManager &instance();

	BankDialog *bankDialog();

	BuildingDetailDialog *buildingDetailDialog();

	CompanyDetailDialog *companyDetailDialog();

	SetRouteDialog *setRouteDialog();

private:
	// Hide constructor and destructor.
	UIManager();

	~UIManager();

private:
	BankDialog *bankDialog_ = nullptr;

	BuildingDetailDialog *buildingDetailDialog_ = nullptr;

	CompanyDetailDialog *companyDetailDialog_ = nullptr;

	SetRouteDialog *setRouteDialog_ = nullptr;
};

#endif // !UIMANAGER_H
