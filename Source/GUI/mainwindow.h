/*
 *    Copyright 2017 Li Zeqing
 *
 *    This file is part of World Simulator.
 *    
 *    World Simulator is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *    
 *    World Simulator is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *    
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with World Simulator. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QString>

#include "Source/Objects/LandParcel.h"
#include "Source/Objects/Company.h"

class ICommand;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    static MainWindow &instance();

    void init();

    void redirectData(LandParcel *);

    void setDirty();

signals:
    void dataChanged();

    void sendSelectedBuilding(LandParcel *);

private slots:
    // Calls function update() of every variable objects.
    void endTurns();

    void showBuildingTableWidget();

    void showCompanyDetail() const ;

    void showHelp();

    void getBuildingByPos(int x, int y);

    void updateDisplay() const;

private:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void signalSlotConfig();

private:
    Company *playerCompany_;

    Ui::MainWindow *ui;
};

#endif // !MAIN_WINDOW_H
