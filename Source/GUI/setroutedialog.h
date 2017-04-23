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
 *  along with World Simulator.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SETROUTEDIALOG_H
#define SETROUTEDIALOG_H

#include <QDialog>
#include <QString>

#include "Source/Objects/basebuilding.h"
#include "Source/Objects/route.h"

#include "selecttablewidget.h"

namespace Ui {
class SetRouteDialog;
}

class SetRouteDialog : public QDialog {
    Q_OBJECT

public:
    SetRouteDialog(QWidget *parent = nullptr);

    ~SetRouteDialog();

    // Creates a new object if the former one has been used.
    void createNewRoute();

public slots:
    void updateDisplay();

private slots:
    void getGoodsName(const QString &);

    void getGoodsVolume(double);

    void getOrig(BaseBuilding *);
    
    void getDest(BaseBuilding *);

    // Summarizes all informations and sends Route to Garage.
    void finishSetting();

signals:
    void sendRoute(Route *);

    void dataChanged();

private:
    Route *route_;

    SelectTableWidget *selectOrigTableWidget_;

    SelectTableWidget *selectDestTableWidget_;

    Ui::SetRouteDialog *ui;
};

#endif // !SETROUTEDIALOG_H