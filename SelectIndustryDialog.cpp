#include "SelectIndustryDialog.h"
#include "BuildingManager.h"
#include "Industry.h"
#include "MyPushButton.h"
#include "ui_selectindustrydialog.h"

SelectIndustryDialog::SelectIndustryDialog(QWidget *parent) : 
	QDialog(parent),
	ui(new Ui::SelectIndustryDialog)
{
	init();
}

SelectIndustryDialog::~SelectIndustryDialog() {
	
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
	int indexOfIndustry = 0;
	for (const auto &item : buildingList) {
		if (item->type().contains("Factory")) {
			Industry *industry = dynamic_cast<Industry *>(item);
			displayTableWidget(indexOfIndustry, indexOfBuilding, industry);
			++indexOfIndustry;
		}
		++indexOfBuilding;
	}
	ui->tableWidget_industry->setRowCount(indexOfIndustry);
}

void SelectIndustryDialog::displayTableWidget(int indexInWidget, int indexInManager, Industry *industry) {
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
