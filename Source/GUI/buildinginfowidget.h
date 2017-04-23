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

#ifndef BUILDINGINFOWIDGET_H
#define BUILDINGINFOWIDGET_H

#include <QString>
#include <QWidget>

#include "Source/Objects/basebuilding.h"

namespace Ui { 
class BuildingInfoWidget; 
}

class BuildingInfoWidget : public QWidget {
    Q_OBJECT

public:
    BuildingInfoWidget(QWidget *parent = nullptr);

    ~BuildingInfoWidget();

    void setTarget(BaseBuilding *building);

signals:
    void sendCommand(int command, BaseBuilding *building);

public slots:
    void receiveCommand(int);

    void showBuildingInfo(BaseBuilding *building);

    void updateDisplay();

private:
    BaseBuilding *displayedBuilding_ = nullptr;

    Ui::BuildingInfoWidget *ui;
};

#endif // !BUILDINGINFOWIDGET_H
