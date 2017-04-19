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

#include "Source/baseindustry.h"
#include "Source/goods.h"
#include "Source/warehouse.h"

#include "Source/buildingmanager.h"
#include "Source/uimanager.h"

#include "warehousetablewidget.h"
#include "tablewidgetpushbutton.h"
#include "selecttablewidget.h"
#include "widgethelper.h"

WarehouseTableWidget::WarehouseTableWidget(QWidget *parent, Warehouse *warehouse) :
	QTableWidget(parent),
	warehouse_(warehouse) {
	init();
}

void WarehouseTableWidget::init() {
	this->setColumnCount(3);
	QStringList header{ tr("Item"), tr("Volume"), tr("Option") };
	this->setHorizontalHeaderLabels(header);
}

void WarehouseTableWidget::updateDisplay() {
	if (this->isHidden())	return;

	const QList<Goods *> &warehouse = warehouse_->container();
	this->setRowCount(warehouse.size());

	unsigned int index = 0;
	this->clearContents();
	for (auto iter = warehouse.constBegin(); iter != warehouse.constEnd(); ++iter, ++index) {
		const QString &item = (*iter)->label;
		const QString &volume = WidgetHelper::toString((*iter)->volume);
		this->setItem(index, 0, new QTableWidgetItem(item));
		this->setItem(index, 1, new QTableWidgetItem(volume));

		TableWidgetPushButton *sellBtn = new TableWidgetPushButton(tr("Sell"));
		sellBtn->setIndex(index);
		connect(sellBtn,			SIGNAL(clicked()),
				this,				SLOT(goSelectIndustry()));
		connect(sellBtn,			SIGNAL(sendData(int, int)),
				this,				SLOT(getGoods(int)));
		this->setCellWidget(index, 2, sellBtn);
	}
}

void WarehouseTableWidget::goSelectIndustry() {
	if (!selectTableWidget_) {
		selectTableWidget_ = new SelectTableWidget;
		selectTableWidget_->setParent(this, Qt::Window);
		selectTableWidget_->setSelector(SelectTableWidget::Factory | SelectTableWidget::Mine);
		connect(selectTableWidget_,	SIGNAL(sendBuilding(BaseBuilding*)),
				this,				SLOT(getDestAndSendPreroute(BaseBuilding*)));
	}
	selectTableWidget_->show();
	selectTableWidget_->updateDisplay();
}

void WarehouseTableWidget::getGoods(int index) {
	goods_ = warehouse_->getById(index);
}

void WarehouseTableWidget::getDestAndSendPreroute(BaseBuilding *building) {
	selectTableWidget_->hide();

	BaseIndustry *industry = dynamic_cast<BaseIndustry *>(building);
	emit sendPreroute(*goods_, industry);
	emit dataChanged();
}
