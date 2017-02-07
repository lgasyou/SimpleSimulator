#include "garagetablewidget.h"
#include "garage.h"
#include "truck.h"
#include "order.h"
#include "baseindustry.h"

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
		if (truck->occupied()) {
			const QString &dest = truck->order()->dest->name();
			const QString &goods = truck->order()->goods.goods;
			const QString &weight = toString(truck->order()->goods.weight);
			setItem(index, 1, new QTableWidgetItem(dest));
			setItem(index, 2, new QTableWidgetItem(goods));
			setItem(index, 3, new QTableWidgetItem(weight));
		} else {
			setItem(index, 1, new QTableWidgetItem);
			setItem(index, 2, new QTableWidgetItem);
			setItem(index, 3, new QTableWidgetItem);
		}
	}
}

QString GarageTableWidget::toString(double value) {
	return QString::number(value, 10, 2);
}
