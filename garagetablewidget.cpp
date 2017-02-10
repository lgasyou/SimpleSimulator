#include "garagetablewidget.h"
#include "garage.h"
#include "truck.h"
#include "route.h"
#include "baseindustry.h"
#include "goodscontainer.h"

#include "uimanager.h"

#include "setroutedialog.h"
#include "mypushbutton.h"

GarageTableWidget::GarageTableWidget(QWidget *parent) : 
	QTableWidget(parent)
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
	if (this->isHidden())	return;

	auto &vihicleList = garage_->vihicleList();
	this->setRowCount(vihicleList.size());

	int index = 0;
	this->clearContents();
	for (auto &iter = vihicleList.constBegin(); iter != vihicleList.constEnd(); ++iter, ++index) {
		updateEachLine(index, *iter);
	}
}

void GarageTableWidget::updateEachLine(int index, Truck *truck) {
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
	MyPushButton *routeBtn = new MyPushButton(text);
	routeBtn->setIndex(index);
	setCellWidget(index, 5, routeBtn);

	connect(routeBtn, SIGNAL(sendPointer(MyPushButton*)),
		this, SLOT(buttonClicked(MyPushButton*)));
}

void GarageTableWidget::buttonClicked(MyPushButton *button) {
	if (button->text() == "Route")
		showSetRouteDialog(button);
	else if (button->text() == "Stop") {
		int id = button->index();
		Truck *truck = garage_->getTruckById(id);
		garage_->stopVihicle(truck);
		emit dataChanged();
	}
}

void GarageTableWidget::showSetRouteDialog(MyPushButton *truckBtn) {
	selectedTruckId_ = truckBtn->index();

	SetRouteDialog *setRouteDialog = UIManager::instance().setRouteDialog();
	setRouteDialog->createNewRoute();
	static bool isTheFirstTimeCall = true;
	if (isTheFirstTimeCall) {
		connect(setRouteDialog, SIGNAL(sendRoute(Route*)),
			this, SLOT(setRoute(Route*)));
		setRouteDialog->setParent(this, Qt::Window);
		isTheFirstTimeCall = false;
	}
	setRouteDialog->showAndRaise();
	setRouteDialog->updateDisplay();
}

void GarageTableWidget::setRoute(Route *route) {
	garage_->sendVihicle(route, selectedTruckId_);
	emit dataChanged();
}

QString GarageTableWidget::toString(double value) {
	return QString::number(value, 10, 2);
}
