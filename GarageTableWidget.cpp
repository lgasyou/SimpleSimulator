﻿#include "GarageTableWidget.h"
#include "Garage.h"
#include "Truck.h"
#include "Order.h"
#include "Industry.h"

GarageTableWidget::GarageTableWidget(QWidget *parent) : 
	QTableWidget(parent)
{
	init();
}

GarageTableWidget::~GarageTableWidget() { }

void GarageTableWidget::init() {
	this->setColumnCount(4);
	QStringList header{ tr("Name"), tr("Destination"), tr("Goods"), tr("Weight") };
	this->setHorizontalHeaderLabels(header);
}

void GarageTableWidget::updateDisplay() {
	if (this->isHidden())	return;

	auto &vihicleList = garage_->vihicleList();
	this->setRowCount(vihicleList.size());

	int index = 0;
	for (auto &iter = vihicleList.constBegin(); iter != vihicleList.constEnd(); ++iter, ++index) {
		auto &truck = *iter;
		setItem(index, 0, new QTableWidgetItem(tr("Truck")));
		if (truck->order()) {
			const QString &dest = truck->order()->dest->name();
			const QString &goods = truck->order()->goods;
			const QString &weight = toString(truck->order()->weight);
			setItem(index, 1, new QTableWidgetItem(dest));
			setItem(index, 2, new QTableWidgetItem(goods));
			setItem(index, 3, new QTableWidgetItem(weight));
		}
	}
}

QString GarageTableWidget::toString(double value) {
	return QString::number(value, 10, 2);
}