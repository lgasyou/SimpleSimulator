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

#ifndef BUILDING_INFO_WIDGET_H
#define BUILDING_INFO_WIDGET_H

#include <QWidget>

#include "Source/Objects/LandParcel.h"

namespace Ui { 
class BuildingInfoWidget; 
}

class BuildingInfoWidget : public QWidget {
    Q_OBJECT

public:
    BuildingInfoWidget(QWidget *parent = nullptr);

    ~BuildingInfoWidget();

    void setTarget(LandParcel *building);

    void updateDisplay() ;

public slots:
    void showBuildingInfo(LandParcel *building);

private:
    LandParcel *displayingObject_ = nullptr;

    Ui::BuildingInfoWidget *ui;
};

#endif // !BUILDING_INFO_WIDGET_H
