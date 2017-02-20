#include "buildinginfotablewidget.h"
#include "buildingmanager.h"
#include "companymanager.h"
#include "basebuilding.h"
#include "company.h"
#include "gameconstants.h"
#include "mypushbutton.h"
#include <QFile>
#include <QApplication>

BuildingInfoTableWidget::BuildingInfoTableWidget(QWidget *parent) :
    QTableWidget(parent)
{ 
	init();
}

void BuildingInfoTableWidget::init() {
	this->setColumnCount(GameConstants::colOfBuildingInfoTableWidget);
	QStringList header{ tr("Name"),tr("Value"),tr("Type"), tr("Ownership"),tr("Option"), tr("Option") };
	this->setHorizontalHeaderLabels(header);
}

bool BuildingInfoTableWidget::writeFile(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_3);

    QApplication::setOverrideCursor(Qt::WaitCursor);
//    for (int row = 0; row != BuildingManager::instance().buildingNumber(); ++row) {
//        for (int col = 0; col != BaseBuilding::numberOfPropertiesOfBuilding; ++ col) {
//            QString str;

//        }
//    }
    QApplication::restoreOverrideCursor();
    return true;
}

bool BuildingInfoTableWidget::readFile(const QString &fileName) {
    QFile file(fileName);
    return true;
}

void BuildingInfoTableWidget::updateDisplay() {
	auto &buildingManager = BuildingManager::instance();
	size_t buildingNumber = buildingManager.buildingNumber();;
    this->setRowCount((int)buildingNumber);

	this->clearContents();
	for (int index = 0; index != buildingNumber; ++index) {
		displayBasicInfo(index);
		displayAccordingToVisitor(index);
	}
}

void BuildingInfoTableWidget::displayBasicInfo(int index) {
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

void BuildingInfoTableWidget::displayAccordingToVisitor(int index) {
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

QString BuildingInfoTableWidget::toString(double value) {
	return QString::number(value, 10, 2);
}

void BuildingInfoTableWidget::getBuildingAndSendSignal(MyPushButton *button) {
    int id = button->index();
    BaseBuilding *building = BuildingManager::instance().getBuildingById(id);

    if (button->text() == "Buy") {
        emit buySignal(building);
    } else if (button->text() == "Sell") {
        emit sellSignal(building);
    } else {
        emit showDetailSignal(building);
    }
}
