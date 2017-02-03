#include "BuildingInfoTableWidget.h"
#include "BuildingManager.h"
#include "Company.h"
#include "GameConstants.h"
#include "MyPushButton.h"
#include <QFile>
#include <QApplication>

BuildingInfoTableWidget::BuildingInfoTableWidget(QWidget *parent) :
    QTableWidget(parent),
    company_(nullptr)
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
	auto &buildingList = BuildingManager::instance().buildingList();
    this->setRowCount(buildingList.size());

	int index = 0;
	for (auto &iter = buildingList.constBegin(); iter != buildingList.constEnd(); ++iter, ++index) {
		displayBasicInfo(index, *iter);
		displayAccordingToVisitor(index, *iter);
	}
}

void BuildingInfoTableWidget::displayBasicInfo(int index, BuildingBase *building) {
	const QString &name = building->name();
	const QString &deltaValue = " " + toString(building->deltaValue());
	const QString &value = "$" + toString(building->value()) + deltaValue;
	const QString &type = building->type();
	const QString &owner = building->owner() ? building->owner()->name() : tr("Government");
	setItem(index, 0, new QTableWidgetItem(name));
	setItem(index, 1, new QTableWidgetItem(value));
	setItem(index, 2, new QTableWidgetItem(type));
	setItem(index, 3, new QTableWidgetItem(owner));
}

void BuildingInfoTableWidget::displayAccordingToVisitor(int index, BuildingBase *building) {
	const QString &btnText = (building->owner() != company_) ? tr("Buy") : tr("Sell");
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
    BuildingBase *building = BuildingManager::instance().getBuildingById(id);

    if (button->text() == "Buy") {
        emit buySignal(building);
    } else if (button->text() == "Sell") {
        emit sellSignal(building);
    } else {
        emit showDetailSignal(building);
    }
}
