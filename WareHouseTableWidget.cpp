#include "WarehouseTableWidget.h"
#include "Warehouse.h"
#include "MyPushButton.h"

WarehouseTableWidget::WarehouseTableWidget(QWidget *parent, Warehouse *warehouse) :
	QTableWidget(parent),
	warehouse_(warehouse)
{
	init();
}

void WarehouseTableWidget::init() {
	this->setColumnCount(3);
	QStringList header{ tr("Item"), tr("Weight"), tr("Option") };
	this->setHorizontalHeaderLabels(header);
}

void WarehouseTableWidget::updateDisplay() {
	const QMap<QString, double> &warehouse = warehouse_->container();
	this->setRowCount(warehouse.size());

	unsigned int index = 0;
	for (auto &iter = warehouse.constBegin(); iter != warehouse.constEnd(); ++iter, ++index) {
		const QString &item = iter.key();
		const QString &weight = toString(iter.value());
		this->setItem(index, 0, new QTableWidgetItem(item));
		this->setItem(index, 1, new QTableWidgetItem(weight));

		MyPushButton *sellBtn = new MyPushButton(tr("Sell"));
		//connect(sellBtn, SIGNAL(sendPointer(MyPushButton*)),
		//		this, SLOT());
		this->setCellWidget(index, 2, sellBtn);
	}
}

void WarehouseTableWidget::sendSignal(MyPushButton *button) { }

QString WarehouseTableWidget::toString(double value) {
	return QString::number(value, 10, 2);
}
