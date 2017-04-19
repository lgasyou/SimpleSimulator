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

#include "Source/buildingmanager.h"
#include "Source/companymanager.h"
#include "Source/basebuilding.h"
#include "Source/company.h"
#include "Source/gameconstants.h"

#include "buildingtablewidget.h"
#include "tablewidgetpushbutton.h"
#include "widgethelper.h"

#include <QFile>
#include <QApplication>

BuildingTableWidget::BuildingTableWidget(QWidget *parent) :
    QTableWidget(parent) {
	init();
}

void BuildingTableWidget::init() {
	resize(QSize(800, 600));

	setWindowTitle(tr("Building Information List"));

	this->setColumnCount(6);
	QStringList header{ tr("Name"),tr("Value"),tr("Type"), tr("Ownership"),tr("Option"), tr("Option") };
	this->setHorizontalHeaderLabels(header);
}

void BuildingTableWidget::updateDisplay() {
	auto &buildingManager = BuildingManager::instance();
	int buildingNumber = (int)buildingManager.buildingNumber();
    this->setRowCount(buildingNumber);

	this->clearContents();
	for (int index = 0; index != buildingNumber; ++index) {
		displayBasicInfo(index);
		displayAccordingToVisitor(index);
	}
}

void BuildingTableWidget::displayBasicInfo(int index) {
	BaseBuilding *building = BuildingManager::instance().getById(index);

	const QString &name = building->name();
	const QString &deltaValue = " " + WidgetHelper::toString(building->deltaValue());
	const QString &value = "$" + WidgetHelper::toString(building->value()) + deltaValue;
	const QString &type = building->type();
	const QString &owner = building->owner()->name();
	setItem(index, 0, new QTableWidgetItem(name));
	setItem(index, 1, new QTableWidgetItem(value));
	setItem(index, 2, new QTableWidgetItem(type));
	setItem(index, 3, new QTableWidgetItem(owner));
}

void BuildingTableWidget::displayAccordingToVisitor(int index) {
	BaseBuilding *building = BuildingManager::instance().getById(index);
	Company *playerCompany = CompanyManager::instance().playerCompany();

	using namespace GameConstants;

	bool owned = building->owner() != playerCompany;
	const QString &btnText = owned ? tr("Buy") : tr("Sell");
	TableWidgetPushButton *optionBtn = new TableWidgetPushButton(btnText, owned ? BuyBuilding : SellBuilding);
	optionBtn->setIndex(index);
	connect(optionBtn,	SIGNAL(sendData(int, int)),
			this,		SLOT(receiveCommand(int, int)));
	setCellWidget(index, 4, optionBtn);

	TableWidgetPushButton *detailBtn = new TableWidgetPushButton(tr("Details"), ShowDetail);
	detailBtn->setIndex(index);
	connect(detailBtn,	SIGNAL(sendData(int, int)),
			this,		SLOT(receiveCommand(int, int)));
	setCellWidget(index, 5, detailBtn);
}

void BuildingTableWidget::receiveCommand(int index, int command) {
	BaseBuilding *building = BuildingManager::instance().getById(index);
	emit sendCommand(command, building);
}
