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

#ifndef COMMANDPUSHBUTTON_H
#define COMMANDPUSHBUTTON_H

#include <QPushButton>
#include "Source/Commmand.h"

// The PushButton is specialized to send command when clicked.
class CommandPushButton : public QPushButton {
    Q_OBJECT

public:
    CommandPushButton(QWidget *parent = nullptr, ICommmand *command = nullptr);

    CommandPushButton(const QString &text, ICommmand *command = nullptr, QWidget *parent = nullptr);

    ~CommandPushButton();

    void init();

    void setCommand(ICommmand *command) { this->command = command; }

public slots:
    virtual void repeater();

signals:
    void sendCommand(ICommmand *);

protected:
	ICommmand *command;
};

#endif // COMMANDPUSHBUTTON_H
