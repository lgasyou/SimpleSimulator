#include "FactoryCargoTableWidget.h"

FactoryCargoTableWidget::FactoryCargoTableWidget(QWidget *parent, FactoryCargo *cargo) :
	QTableWidget(parent),
	cargo_(cargo)
{ }
