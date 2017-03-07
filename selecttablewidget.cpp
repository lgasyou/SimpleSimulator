#include "selecttablewidget.h"

#include "basebuilding.h"

#include "buildingmanager.h"

#include "tablewidgetpushbutton.h"

SelectTableWidget::SelectTableWidget(QWidget *parent) :
	QTableWidget(parent) {	
	init();
}

SelectTableWidget::~SelectTableWidget() { }

void SelectTableWidget::init() {
	setColumnCount(3);
	QStringList header{ tr("Name"), tr("Type"), tr("Option") };
	setHorizontalHeaderLabels(header);
	setWindowTitle(tr("Select Building:"));
}

void SelectTableWidget::updateDisplay() {
	auto &buildingList = BuildingManager::instance().buildingList();
	setRowCount((int)buildingList.size());
	clearContents();
	int indexOfBuilding = 0;
	int indexOfChosen = 0;
	for (const auto &item : buildingList) {
		for (const auto &typeName : typeNames_) {
			if (item->type().contains(typeName)) {
				updateEachLine(indexOfChosen, indexOfBuilding, item);
				++indexOfChosen;
			}
		}
		++indexOfBuilding;
	}
	setRowCount(indexOfChosen);
}

void SelectTableWidget::updateEachLine(int indexInWidget, int indexInManager, BaseBuilding *building) {
	const QString &name = building->name();
	const QString &type = building->type();
	setItem(indexInWidget, 0, new QTableWidgetItem(name));
	setItem(indexInWidget, 1, new QTableWidgetItem(type));

	TableWidgetPushButton *selectButton = new TableWidgetPushButton(tr("Select"));
	setCellWidget(indexInWidget, 2, selectButton);
	selectButton->setIndex(indexInManager);
	connect(selectButton, SIGNAL(sendPointer(TableWidgetPushButton*)),
		this, SLOT(getDestAndSendBuilding(TableWidgetPushButton*)));
}

void SelectTableWidget::setSelector(int type) {
	typeNames_.clear();
	if (type) {
		if (type & UnusedLand)
			typeNames_.push_back("Unused Land");
		if (type & Factory)
			typeNames_.push_back("Factory");
		if (type & Mine)
			typeNames_.push_back("Mine");
	}
}

void SelectTableWidget::getDestAndSendBuilding(TableWidgetPushButton *button) {
	int id = button->index();
	BaseBuilding *building = BuildingManager::instance().getBuildingById(id);
	emit sendBuilding(building);
}
