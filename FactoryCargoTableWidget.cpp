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

}
