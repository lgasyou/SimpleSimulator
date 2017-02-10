#include "garagetablewidget.h"
#include "garage.h"
#include "truck.h"
#include "order.h"
#include "baseindustry.h"

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
	QStringList header{ tr("Name"), tr("Destination"), tr("Goods"), tr("Weight"), tr("Remain Time"), tr("Option") };
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
	if (truck->occupied()) {
		const QString &dest = truck->order()->dest->name();
		const QString &goods = truck->order()->goods.goods;
		const QString &weight = toString(truck->order()->goods.weight);
		const QString &remainTime = toString(truck->remainTime());
		setItem(index, 1, new QTableWidgetItem(dest));
		setItem(index, 2, new QTableWidgetItem(goods));
		setItem(index, 3, new QTableWidgetItem(weight));
		setItem(index, 4, new QTableWidgetItem(remainTime));
	} else {
		MyPushButton *routeBtn = new MyPushButton(tr("Route"));
		routeBtn->setIndex(index);
		setCellWidget(index, 5, routeBtn);

		connect(routeBtn, SIGNAL(sendPointer(MyPushButton*)),
			this, SLOT(showSetRouteDialog(MyPushButton*)));
	}
}

void GarageTableWidget::showSetRouteDialog(MyPushButton *truckBtn) {
	int truckId = truckBtn->index();

	SetRouteDialog *setRouteDialog = UIManager::instance().setRouteDialog();
	setRouteDialog->setParent(this, Qt::Window);
	setRouteDialog->showAndRaise();
	setRouteDialog->updateDisplay();
}

void GarageTableWidget::setRoute(BaseBuilding *building) {

}

QString GarageTableWidget::toString(double value) {
	return QString::number(value, 10, 2);
}
