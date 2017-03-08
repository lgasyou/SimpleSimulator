#include "buildingtablewidget.h"
#include "buildingmanager.h"
#include "companymanager.h"
#include "basebuilding.h"
#include "company.h"
#include "gameconstants.h"

#include "tablewidgetpushbutton.h"
#include <QFile>
#include <QApplication>

BuildingTableWidget::BuildingTableWidget(QWidget *parent) :
    QTableWidget(parent) {
	init();
}

void BuildingTableWidget::init() {
	resize(QSize(800, 600));

	setWindowTitle(tr("Building Information List"));

	this->setColumnCount(GameConstants::colOfBuildingTableWidget);
	QStringList header{ tr("Name"),tr("Value"),tr("Type"), tr("Ownership"),tr("Option"), tr("Option") };
	this->setHorizontalHeaderLabels(header);
}

void BuildingTableWidget::updateDisplay() {
	auto &buildingManager = BuildingManager::instance();
	std::size_t buildingNumber = buildingManager.buildingNumber();
    this->setRowCount((int)buildingNumber);

	this->clearContents();
	for (int index = 0; index != buildingNumber; ++index) {
		displayBasicInfo(index);
		displayAccordingToVisitor(index);
	}
}

void BuildingTableWidget::displayBasicInfo(int index) {
	BaseBuilding *building = BuildingManager::instance().getBuildingById(index);

	const QString &name = building->name();
	const QString &deltaValue = " " + toString(building->deltaValue());
	const QString &value = "$" + toString(building->value()) + deltaValue;
	const QString &type = building->type();
	const QString &owner = building->owner()->name();
	setItem(index, 0, new QTableWidgetItem(name));
	setItem(index, 1, new QTableWidgetItem(value));
	setItem(index, 2, new QTableWidgetItem(type));
	setItem(index, 3, new QTableWidgetItem(owner));
}

void BuildingTableWidget::displayAccordingToVisitor(int index) {
	BaseBuilding *building = BuildingManager::instance().getBuildingById(index);
	Company *playerCompany = CompanyManager::instance().playerCompany();

	using namespace GameConstants;

	bool owned = building->owner() != playerCompany;
	const QString &btnText = owned ? tr("Buy") : tr("Sell");
	TableWidgetPushButton *optionBtn = new TableWidgetPushButton(btnText, owned ? BuyBuilding : SellBuilding);
	optionBtn->setIndex(index);
	connect(optionBtn,	SIGNAL(sendCommand(int, int)),
			this,		SLOT(receiveCommand(int, int)));
	setCellWidget(index, 4, optionBtn);

	TableWidgetPushButton *detailBtn = new TableWidgetPushButton(tr("Details"), ShowDetail);
	detailBtn->setIndex(index);
	connect(detailBtn,	SIGNAL(sendCommand(int, int)),
			this,		SLOT(receiveCommand(int, int)));
	setCellWidget(index, 5, detailBtn);
}

void BuildingTableWidget::receiveCommand(int command, int index) {
	BaseBuilding *building = BuildingManager::instance().getBuildingById(index);
	emit sendCommand(command, building);
}

QString BuildingTableWidget::toString(double value) {
	return QString::number(value, 10, 2);
}