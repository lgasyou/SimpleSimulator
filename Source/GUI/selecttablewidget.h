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

#ifndef SELECTTABLEWIDGET_H
#define SELECTTABLEWIDGET_H

#include <QTableWidget>
#include <QString>
#include <vector>

#include "Source/Objects/basebuilding.h"

#include "tablewidgetpushbutton.h"

class SelectTableWidget : public QTableWidget {
    Q_OBJECT

public:
    enum { 
        None = 0, 
        UnusedLand = 1, 
        Factory = 2, Mine = 4 };

    SelectTableWidget(QWidget *parent = nullptr);

    ~SelectTableWidget();

    void init();

    void updateDisplay();

    void updateEachLine(int indexInWidget, int indexInManager, BaseBuilding *);

    // Sets type(s) which will be displayed later.
    // Uses '|' to store multiple objects.
    void setSelector(int type);

public slots:
    void getDestAndSendBuilding(int index);

signals:
    void sendBuilding(BaseBuilding *);

private:
    std::vector<QString> typeNames_;
};

#endif // !SELECTTABLEWIDGET_H