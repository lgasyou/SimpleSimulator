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

#ifndef BUILDINGDETAILDIALOG_H
#define BUILDINGDETAILDIALOG_H

#include <QDialog>

#include "Source/Objects/land.h"
#include "Source/Objects/machine.h"

namespace Ui {
class BuildingDetailDialog;
}

class BuildingDetailDialog : public QDialog {
    Q_OBJECT

public:
    BuildingDetailDialog(Land *object = nullptr, QWidget *parent = nullptr);

    ~BuildingDetailDialog();

public:
	void setBuilding(Land *building);

public slots:
    void updateDisplay();

    // Receives the data comes from WarehouseTableWidget or GarageTableWidget.
    // Send information to model BaseIndustry.
    //void deliverGoods(const Goods &goods, BaseIndustry *dest);

protected:
    void closeEvent(QCloseEvent *) override;

signals:
    void dataChanged();

    void sendCommand(int command, Land *building);

private slots:
    void addNewMachine();

    void addNewVihicle();

    void setNextMachineProduct(const QString &);

    void showMachineDetail(Machine *);

    void updateMachineDetail(Machine *);

    void receiveCommand(int);

private:
    // Displays according to the type of building.
    void displayAccordingToBuildingType();

    void signalSlotConfig();

private:
    Land *building_ = nullptr;

    Machine *selectedMachine_ = nullptr;

    Ui::BuildingDetailDialog *ui;
};

#endif // !BUILDINGDETAILDIALOG_H
