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

#include "helpdialog.h"

#include <QStringList>

#include "Source/Managers/industrychainmanager.h"

#include "ui_helpdialog.h"

HelpDialog::HelpDialog(QDialog *parent) : QDialog(parent) {
    ui = new Ui::HelpDialog;
    ui->setupUi(this); 
    setWindowTitle(tr("Help"));

    init();
}

HelpDialog::~HelpDialog() {
    delete ui;
}

void HelpDialog::init() {
    connect(ui->itemListWidget, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
            this,               SLOT(showIndustryChain(QListWidgetItem *)));

    QStringList items{ "Coal", "Iron", "Log", "Plank", "Steel"  };
    ui->itemListWidget->addItems(items);

    QStringList header{ "Item", "Weight" };

    ui->sourceTableWidget->setColumnCount(2);
    ui->sourceTableWidget->setHorizontalHeaderLabels(header);
    ui->productTableWidget->setColumnCount(2);
    ui->productTableWidget->setHorizontalHeaderLabels(header);
}

void HelpDialog::showIndustryChain(QListWidgetItem *item) {
    auto precursors = IndustryChainManager::instance().precursors(item->text());
    int size = (int)precursors.size();
    ui->sourceTableWidget->setRowCount(size);
    for (int i = 0; i != size; ++i) {
        const QString &itemName = precursors[i].label;
        ui->sourceTableWidget->setItem(i, 0, new QTableWidgetItem(itemName));
        const QString &itemWeight = QString::number(precursors[i].volume, 10, 2);
        ui->sourceTableWidget->setItem(i, 1, new QTableWidgetItem(itemWeight));
    }

    ui->productTableWidget->setRowCount(1);
    const QString &itemName = item->text();
    ui->productTableWidget->setItem(0, 0, new QTableWidgetItem(itemName));
    const QString &itemWeight = QString::number(1);
    ui->productTableWidget->setItem(0, 1, new QTableWidgetItem(itemWeight));
}
