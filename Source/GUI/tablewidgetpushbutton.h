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

#ifndef TABLEWIDGETPUSHBUTTON_H
#define TABLEWIDGETPUSHBUTTON_H

#include "LandParcelDetailDlg.h"
#include "CommandPushButton.h"

// This PushButton is specialized to send index of this button in table widget while clicked.
class TableWidgetPushButton : public CommandPushButton {
    Q_OBJECT

public:
    TableWidgetPushButton(QWidget *parent = nullptr, std::shared_ptr<ICommand> command = nullptr);

    TableWidgetPushButton(const QString &text, std::shared_ptr<ICommand> command = nullptr, QWidget *parent = nullptr);

    void setIndex(int index) { this->index = index; }

public slots:
    void repeater() override;

signals:
    void sendData(int index, std::shared_ptr<ICommand> command);

private:
    int index = -1;
};

#endif // MYPUSHBUTTON_H
