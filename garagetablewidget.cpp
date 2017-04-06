#include "garagetablewidget.h"
#include "garage.h"
#include "truck.h"
#include "route.h"
#include "baseindustry.h"
#include "goodscontainer.h"

#include "uimanager.h"

#include "setroutedialog.h"
#include "tablewidgetpushbutton.h"

GarageTableWidget::GarageTableWidget(QWidget *parent) : 
	QTableWidget(parent),
	garage_(nullptr)
{
	init();
}

GarageTableWidget::~GarageTableWidget() { }

void GarageTableWidget::init() {
	this->setColumnCount(6);
	QStringList header{ tr("Name"), tr("State"), tr("Destination"), tr("Plan"),  tr("Remain Time"), tr("Option") };
	this->setHorizontalHeaderLabels(header);
}

void GarageTableWidget::updateDisplay() {
	if (garage_ != nullptr) {
		auto &vihicleList = garage_->vihicleList();
		this->setRowCount((int)vihicleList.size());

		int index = 0;
		this->clearContents();
		for (auto vihicle : vihicleList) {
			updateEachRow(index++, vihicle);
		}
	}
}

void GarageTableWidget::updateEachRow(int index, Truck *truck) {
	setItem(index, 0, new QTableWidgetItem(tr("Truck")));
	const QString &curVolume = toString(truck->freightHouse()->curVolume());
	const QString &maxVolume = toString(truck->freightHouse()->maxVolume());
	setItem(index, 1, new QTableWidgetItem(curVolume + " / " + maxVolume));
	if (truck->occupied()) {
		const QString &dest = truck->route()->dest->name();
		const QString &goods = truck->route()->goods.name;
		const QString &volume = toString(truck->route()->goods.volume);
		const QString &remainTime = toString(truck->remainTime());
		setItem(index, 2, new QTableWidgetItem(dest));
		setItem(index, 3, new QTableWidgetItem(goods + " / " + volume));
		setItem(index, 4, new QTableWidgetItem(remainTime));
	}

	const QString &text = truck->occupied() ? tr("Stop") : tr("Route");
	TableWidgetPushButton *routeBtn = new TableWidgetPushButton(text);
	routeBtn->setIndex(index);
	setCellWidget(index, 5, routeBtn);

	connect(routeBtn,	SIGNAL(sendData(int, int)),
			this,		SLOT(buttonClicked(int, int)));
}

void GarageTableWidget::setGarage(BaseBuilding *garage) {
	this->garage_ = dynamic_cast<Garage *>(garage);
}

void GarageTableWidget::buttonClicked(int index, int command) {
	// TODO
	switch (command) {
	case 1:// Show
		showSetRouteDialog(index);
		break;

	case 2: // Stop
		Truck *truck = garage_->getById(index);
		garage_->stopVihicle(truck);
		emit dataChanged();
		break;
	}
}

void GarageTableWidget::showSetRouteDialog(int index) {
	selectedTruckId_ = index;

	SetRouteDialog *setRouteDialog = UIManager::instance().setRouteDialog();
	setRouteDialog->createNewRoute();
	static bool isTheFirstTimeCall = true;
	if (isTheFirstTimeCall) {
		connect(setRouteDialog, SIGNAL(sendRoute(Route*)),
			this, SLOT(setRoute(Route*)));
		setRouteDialog->setParent(this, Qt::Window);
		isTheFirstTimeCall = false;
	}
	setRouteDialog->showUp();
	setRouteDialog->updateDisplay();
}

void GarageTableWidget::setRoute(Route *route) {
	garage_->sendVihicle(route, selectedTruckId_);
	emit dataChanged();
}

QString GarageTableWidget::toString(double value) {
	return QString::number(value, 10, 2);
}
