#include "FactoryCargoTableWidget.h"
#include "FactoryCargo.h"
#include <map>

FactoryCargoTableWidget::FactoryCargoTableWidget(QWidget *parent, FactoryCargo *cargo) :
	QTableWidget(parent),
	cargo_(cargo)
{ 
	this->setColumnCount(3);
	QStringList header{ tr("Item"), tr("Weight"), tr("Option") };
	this->setHorizontalHeaderLabels(header);
}

void FactoryCargoTableWidget::updateDisplay() {
	const QMap<QString, double> &cargo = cargo_->cargo();
	this->setRowCount(cargo.size());

	unsigned int i = 0;
	for (auto &iter = cargo.constBegin(); iter != cargo.constEnd(); ++iter, ++i) {
		this->setItem(i, 0, new QTableWidgetItem(iter.key()));
		this->setItem(i, 1, new QTableWidgetItem(toString(iter.value())));
	}
}

QString FactoryCargoTableWidget::toString(double value) {
	return QString::number(value, 10, 2);
}
