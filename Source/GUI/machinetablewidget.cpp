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

#include "machinetablewidget.h"

MachineTableWidget::MachineTableWidget(QWidget *parent) : 
    QTableWidget(parent) {
    init();
}

MachineTableWidget::~MachineTableWidget() { }

void MachineTableWidget::init() {
    this->setColumnCount(3);

    QStringList header{ tr("Product"), tr("Current Productivity"), tr("Details") };
    this->setHorizontalHeaderLabels(header);
}

void MachineTableWidget::setIndustry(Land *industry) {
    this->industry_ = dynamic_cast<BaseIndustry *>(industry);
}

void MachineTableWidget::receiveShowDetailSignal(int index) {
    Machine *machine = industry_->machines()[index];
    emit sendSelectedMachine(machine);
}

void MachineTableWidget::updateDisplay() {
    if (BaseIndustry *industry = industry_) {
        const auto &machines = industry->machines();
        int machineNumber = (int)machines.size();
        setRowCount(static_cast<int>(machineNumber));

        for (int i = 0; i != machineNumber; ++i) {
            const QString &productName = machines[i]->currentProduct();
            setItem(i, 0, new QTableWidgetItem(productName));
            double percentage = machines[i]->currentProductivity() / machines[i]->maximalProductivity() * 100;
            const QString &productivity = QString::number(percentage) + "%";
            setItem(i, 1, new QTableWidgetItem(productivity));

            TableWidgetPushButton *detailButton = new TableWidgetPushButton(tr("Details"));
            setCellWidget(i, 2, detailButton);
            connect(detailButton,    SIGNAL(sendData(int, int)),
                    this,            SLOT(receiveShowDetailSignal(int)));
            detailButton->setIndex(i);
        }
    }
}
