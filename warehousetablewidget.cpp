#include "warehousetablewidget.h"
#include "Warehouse.h"
#include "buildingmanager.h"
#include "industry.h"
#include "mypushbutton.h"
#include "selectindustrydialog.h"

WarehouseTableWidget::WarehouseTableWidget(QWidget *parent, Warehouse *warehouse) :
	QTableWidget(parent),
	warehouse_(warehouse),
	selectIndustryDialog_(nullptr),
	goods_(nullptr)
{
	init();
}

void WarehouseTableWidget::init() {
	this->setColumnCount(3);
	QStringList header{ tr("Item"), tr("Weight"), tr("Option") };
	this->setHorizontalHeaderLabels(header);
}

void WarehouseTableWidget::updateDisplay() {
	if (this->isHidden())	return;

	const QList<Goods *> &warehouse = warehouse_->container();
	this->setRowCount(warehouse.size());

	unsigned int index = 0;
	for (auto &iter = warehouse.constBegin(); iter != warehouse.constEnd(); ++iter, ++index) {
		const QString &item = (*iter)->goods;
		const QString &weight = toString((*iter)->weight);
		this->setItem(index, 0, new QTableWidgetItem(item));
		this->setItem(index, 1, new QTableWidgetItem(weight));

		MyPushButton *sellBtn = new MyPushButton(tr("Sell"));
		sellBtn->setIndex(index);
		connect(sellBtn, SIGNAL(clicked()),
			this, SLOT(goSelectIndustry()));
		connect(sellBtn, SIGNAL(sendPointer(MyPushButton*)),
				this, SLOT(getGoods(MyPushButton*)));
		this->setCellWidget(index, 2, sellBtn);
	}
}

void WarehouseTableWidget::goSelectIndustry() {
	if (!selectIndustryDialog_)
		selectIndustryDialog_ = new SelectIndustryDialog(this);
	selectIndustryDialog_->show();
	selectIndustryDialog_->raise();
	selectIndustryDialog_->activateWindow();
	selectIndustryDialog_->updateDisplay();
}

void WarehouseTableWidget::getGoods(MyPushButton *button) {
	int id = button->index();
	goods_ = warehouse_->getGoodsById(id);
}

void WarehouseTableWidget::getDestAndSendSignal(MyPushButton *destButton) {
	int id = destButton->index();
	BaseBuilding *building = BuildingManager::instance().getBuildingById(id);
	Industry *industry = dynamic_cast<Industry *>(building);

	selectIndustryDialog_->hide();
	emit sendPreorder(*goods_, industry);
}

QString WarehouseTableWidget::toString(double value) {
	return QString::number(value, 10, 2);
}
