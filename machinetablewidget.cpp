#include "machinetablewidget.h"
#include "baseindustry.h"
#include "machine.h"
#include "goods.h"

#include "tablewidgetpushbutton.h"

MachineTableWidget::MachineTableWidget(QWidget *parent) : 
	QTableWidget(parent),
	industry_(nullptr) {
	init();
}

MachineTableWidget::~MachineTableWidget() { }

void MachineTableWidget::init() {
	this->setColumnCount(3);

	QStringList header{ tr("Product"), tr("Current Productivity"), tr("Details") };
	this->setHorizontalHeaderLabels(header);
}

void MachineTableWidget::setIndustry(BaseBuilding *industry) {
	this->industry_ = dynamic_cast<BaseIndustry *>(industry);
}

void MachineTableWidget::receiveShowDetailSignal(TableWidgetPushButton *button) {
	int index = button->index();
	Machine *machine = industry_->machines()[index];
	emit sendSelectedMachine(machine);
}

void MachineTableWidget::updateDisplay() {
	if (BaseIndustry *industry = industry_) {
		const auto &machines = industry->machines();
		size_t machineNumber = machines.size();
		setRowCount(static_cast<int>(machineNumber));

		for (int i = 0; i != machineNumber; ++i) {
			const QString &productName = machines[i]->currentProduct();
			setItem(i, 0, new QTableWidgetItem(productName));
			double percentage = machines[i]->currentProductivity() / machines[i]->maximalProductivity() * 100;
			const QString &productivity = QString::number(percentage) + "%";
			setItem(i, 1, new QTableWidgetItem(productivity));

			TableWidgetPushButton *detailButton = new TableWidgetPushButton(tr("Details"));
			setCellWidget(i, 2, detailButton);
			connect(detailButton,	SIGNAL(sendPointer(TableWidgetPushButton *)),
					this,			SLOT(receiveShowDetailSignal(TableWidgetPushButton *)));
			detailButton->setIndex(i);
		}
	}
}
