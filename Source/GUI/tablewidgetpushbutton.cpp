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

#include "tablewidgetpushbutton.h"

TableWidgetPushButton::TableWidgetPushButton(QWidget *parent, std::shared_ptr<ICommmand> command) :
    CommandPushButton(parent, command) { }

TableWidgetPushButton::TableWidgetPushButton(const QString &text, std::shared_ptr<ICommmand> command, QWidget *parent) :
    CommandPushButton(text, command, parent) { }

void TableWidgetPushButton::repeater() {
    emit sendData(this->index, this->command);
}
