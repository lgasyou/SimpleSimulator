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

#ifndef WIDGETHELPER_H
#define WIDGETHELPER_H

#include <QString>

#include "Source/Commmand.h"
#include <memory>

class QWidget;

// TODO: create a basic GUI object to contain all of these.
class WidgetHelper {
public:
    static QString toString(double value);

    static void showUp(QWidget *widget);

	static void placeCommand(std::shared_ptr<ICommmand> command);

};

#endif // !WIDGETHELPER_H
