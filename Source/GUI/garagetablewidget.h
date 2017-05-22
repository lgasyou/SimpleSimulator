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

#ifndef GARAGE_TABLE_WIDGET_H
#define GARAGE_TABLE_WIDGET_H

#include <QTableWidget>

#include "Source/Objects/LandParcel.h"
#include "Source/Objects/Garage.h"
#include "Source/Objects/Route.h"

#include "TableWidgetPushButton.h"

class GarageTableWidget : public QTableWidget {
    Q_OBJECT

public:
    GarageTableWidget(QWidget * parent = nullptr);

    ~GarageTableWidget();

    void init();

    void updateEachRow(int index, Truck *);

    void setGarage(LandParcel *garage);

public slots:
    void updateDisplay();

    void buttonClicked(int index, int command);

    void showSetRouteDialog(int index);

    void setRoute(Route *);

signals:
    void dataChanged();

private:
    Garage *garage_ = nullptr;

    int selectedTruckId_ = -1;
};

#endif // !GARAGE_TABLE_WIDGET_H
