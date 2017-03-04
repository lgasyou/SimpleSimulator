#include "machinetablewidget.h"
#include "baseindustry.h"
#include "machine.h"
#include "goods.h"

MachineTableWidget::MachineTableWidget(QWidget *parent) : 
	QTableWidget(parent),
	industry_(nullptr) {
	init();
}

MachineTableWidget::~MachineTableWidget() { }

void MachineTableWidget::init() {
	this->setColumnCount(2);

	QStringList header{ tr("Machine Type"), tr("Option") };
	this->setHorizontalHeaderLabels(header);
}

void MachineTableWidget::setIndustry(BaseBuilding *industry) {
	this->industry_ = dynamic_cast<BaseIndustry *>(industry);
}

void MachineTableWidget::updateDisplay() {
	if (BaseIndustry *industry = industry_) {
		const auto &machines = industry->machines();
		size_t machineNumber = machines.size();
		setRowCount(static_cast<int>(machineNumber));

		for (int i = 0; i != machineNumber; ++i) {
			setItem(i, 0, new QTableWidgetItem("Machine"));
			setItem(i, 1, new QTableWidgetItem("Option"));
		}
	}
}
