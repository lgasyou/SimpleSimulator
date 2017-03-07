#include "warehousetablewidget.h"
#include "warehouse.h"
#include "baseindustry.h"
#include "goods.h"

#include "buildingmanager.h"
#include "uimanager.h"

#include "tablewidgetpushbutton.h"
#include "selecttablewidget.h"

WarehouseTableWidget::WarehouseTableWidget(QWidget *parent, Warehouse *warehouse) :
	QTableWidget(parent),
	warehouse_(warehouse),
	selectTableWidget_(nullptr),
	goods_(nullptr)
{
	init();
}

void WarehouseTableWidget::init() {
	this->setColumnCount(3);
	QStringList header{ tr("Item"), tr("Volume"), tr("Option") };
	this->setHorizontalHeaderLabels(header);
}

void WarehouseTableWidget::updateDisplay() {
	if (this->isHidden())	return;

	const QList<Goods *> &warehouse = warehouse_->container();
	this->setRowCount(warehouse.size());

	unsigned int index = 0;
	this->clearContents();
	for (auto &iter = warehouse.constBegin(); iter != warehouse.constEnd(); ++iter, ++index) {
		const QString &item = (*iter)->name;
		const QString &volume = toString((*iter)->volume);
		this->setItem(index, 0, new QTableWidgetItem(item));
		this->setItem(index, 1, new QTableWidgetItem(volume));

		TableWidgetPushButton *sellBtn = new TableWidgetPushButton(tr("Sell"));
		sellBtn->setIndex(index);
		connect(sellBtn, SIGNAL(clicked()),
			this, SLOT(goSelectIndustry()));
		connect(sellBtn, SIGNAL(sendPointer(TableWidgetPushButton*)),
				this, SLOT(getGoods(TableWidgetPushButton*)));
		this->setCellWidget(index, 2, sellBtn);
	}
}

void WarehouseTableWidget::goSelectIndustry() {
	if (!selectTableWidget_) {
		selectTableWidget_ = new SelectTableWidget;
		selectTableWidget_->setParent(this, Qt::Window);
		selectTableWidget_->setSelector(SelectTableWidget::Factory | SelectTableWidget::Mine);
		connect(selectTableWidget_, SIGNAL(sendBuilding(BaseBuilding*)),
			this, SLOT(getDestAndSendPreroute(BaseBuilding*)));
	}
	selectTableWidget_->show();
	selectTableWidget_->updateDisplay();
}

void WarehouseTableWidget::getGoods(TableWidgetPushButton *button) {
	int id = button->index();
	goods_ = warehouse_->getGoodsById(id);
}

void WarehouseTableWidget::getDestAndSendPreroute(BaseBuilding *building) {
	selectTableWidget_->hide();

	BaseIndustry *industry = dynamic_cast<BaseIndustry *>(building);
	emit sendPreroute(*goods_, industry);
	emit dataChanged();
}

QString WarehouseTableWidget::toString(double value) {
	return QString::number(value, 10, 2);
}
