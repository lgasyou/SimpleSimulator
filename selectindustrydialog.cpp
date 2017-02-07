#include "selectindustrydialog.h"
#include "buildingmanager.h"
#include "baseindustry.h"
#include "mypushbutton.h"
#include "ui_selectindustrydialog.h"

SelectIndustryDialog::SelectIndustryDialog(QWidget *parent) : 
	QDialog(parent),
	ui(new Ui::SelectIndustryDialog)
{
	init();
}

SelectIndustryDialog::~SelectIndustryDialog() {
	delete ui;
}

void SelectIndustryDialog::init() {
	ui->setupUi(this);
	ui->tableWidget_industry->setColumnCount(3);
	QStringList header{ tr("Name"), tr("Type"), tr("Option") };
	ui->tableWidget_industry->setHorizontalHeaderLabels(header);
	setWindowTitle(tr("Select Industrial Building:"));
}

void SelectIndustryDialog::updateDisplay() {
	auto &buildingList = BuildingManager::instance().buildingList();
	ui->tableWidget_industry->setRowCount(buildingList.size());
	int indexOfBuilding = 0;
	int indexOfBaseIndustry = 0;
	for (const auto &item : buildingList) {
		if (item->type().contains("Factory")) {
			BaseIndustry *industry = dynamic_cast<BaseIndustry *>(item);
			displayTableWidget(indexOfBaseIndustry, indexOfBuilding, industry);
			++indexOfBaseIndustry;
		}
		++indexOfBuilding;
	}
	ui->tableWidget_industry->setRowCount(indexOfBaseIndustry);
}

void SelectIndustryDialog::displayTableWidget(int indexInWidget, int indexInManager, BaseIndustry *industry) {
	auto tableWidget = ui->tableWidget_industry;
	const QString &name = industry->name();
	const QString &type = industry->type();
	tableWidget->setItem(indexInWidget, 0, new QTableWidgetItem(name));
	tableWidget->setItem(indexInWidget, 1, new QTableWidgetItem(type));

	MyPushButton *selectButton = new MyPushButton(tr("Select"));
	tableWidget->setCellWidget(indexInWidget, 2, selectButton);
	selectButton->setIndex(indexInManager);
	connect(selectButton, SIGNAL(sendPointer(MyPushButton*)),
		parent(), SLOT(getDestAndSendSignal(MyPushButton*)));
}
