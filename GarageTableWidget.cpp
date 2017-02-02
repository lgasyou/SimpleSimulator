#include "GarageTableWidget.h"

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
	
}
