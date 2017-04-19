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

#ifndef BUILDINGINFOLIST_H
#define BUILDINGINFOLIST_H

#include <QTableWidget>

class BaseBuilding;

// This class is used for showing information of Buildings.
// Set Company before use it.
class BuildingTableWidget : public QTableWidget {
    Q_OBJECT

public:
    BuildingTableWidget(QWidget *parent = nullptr);

	void init();

    void updateDisplay();

	void displayBasicInfo(int index);

	void displayAccordingToVisitor(int index);

signals:
	void sendCommand(int command, BaseBuilding *building);

private slots:
	// Gets command and index of building,
	// sends command and pointer of building.
	void receiveCommand(int command, int index);


private:
	// transforms double into QString
	static QString toString(double value);
};

#endif // BUILDINGINFOLIST_H