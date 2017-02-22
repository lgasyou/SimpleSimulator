#include "buildinginfolist.h"
#include "buildingmanager.h"
#include "companymanager.h"
#include "basebuilding.h"
#include "company.h"
#include "gameconstants.h"
#include "mypushbutton.h"
#include <QFile>
#include <QApplication>

BuildingInfoList::BuildingInfoList(QWidget *parent) :
    QTableWidget(parent)
{
	init();
}

void BuildingInfoList::init() {
	setWindowTitle(tr("Building Information List"));

	this->setColumnCount(GameConstants::colOfBuildingInfoList);
	QStringList header{ tr("Name"),tr("Value"),tr("Type"), tr("Ownership"),tr("Option"), tr("Option") };
	this->setHorizontalHeaderLabels(header);
}

void BuildingInfoList::updateDisplay() {
	auto &buildingManager = BuildingManager::instance();
	size_t buildingNumber = buildingManager.buildingNumber();
    this->setRowCount((int)buildingNumber);

	this->clearContents();
	for (int index = 0; index != buildingNumber; ++index) {
		displayBasicInfo(index);
		displayAccordingToVisitor(index);
	}
}

void BuildingInfoList::displayBasicInfo(int index) {
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

void BuildingInfoList::displayAccordingToVisitor(int index) {
	BaseBuilding *building = BuildingManager::instance().getBuildingById(index);
	Company *playerCompany = CompanyManager::instance().playerCompany();

	const QString &btnText = (building->owner() != playerCompany) ? tr("Buy") : tr("Sell");
	MyPushButton *optionBtn = new MyPushButton(btnText);
	optionBtn->setIndex(index);
	connect(optionBtn, SIGNAL(sendPointer(MyPushButton*)),
		this, SLOT(getBuildingAndSendSignal(MyPushButton*)));
	setCellWidget(index, 4, optionBtn);

	MyPushButton *detailBtn = new MyPushButton(tr("Details"));
	detailBtn->setIndex(index);
	connect(detailBtn, SIGNAL(sendPointer(MyPushButton*)),
		this, SLOT(getBuildingAndSendSignal(MyPushButton*)));
	setCellWidget(index, 5, detailBtn);
}

QString BuildingInfoList::toString(double value) {
	return QString::number(value, 10, 2);
}

void BuildingInfoList::getBuildingAndSendSignal(MyPushButton *button) {
    int id = button->index();
    BaseBuilding *building = BuildingManager::instance().getBuildingById(id);

    if (button->text() == "Details") {
        emit showDetailSignal(building);
    } else {
        emit sendOption(button->text(), building);
    }
}
