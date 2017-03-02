#include "buildingdetaildialog.h"
#include "basebuilding.h"
#include "baseindustry.h"
#include "warehouse.h"
#include "goodscontainer.h"
#include "company.h"
#include "companymanager.h"
#include "buildingmanager.h"
#include "garage.h"
#include "goods.h"

#include "garagetablewidget.h"
#include "warehousetablewidget.h"
#include "mypushbutton.h"
#include "ui_buildingdetaildialog.h"

BuildingDetailDialog::BuildingDetailDialog(QWidget *parent) :
	QDialog(parent),
    building_(nullptr),
	garageTableWidget_(new GarageTableWidget),
	warehouseTableWidget_(new WarehouseTableWidget),
    ui(new Ui::BuildingDetailDialog)
{
    ui->setupUi(this);

	ui->detailStackedWidget->insertWidget(3, garageTableWidget_);

	//connect(this, SIGNAL(dataChanged()),
	//	warehouseTableWidget_, SLOT(updateDisplay()));
	//connect(this, SIGNAL(dataChanged()),
	//	garageTableWidget_, SLOT(updateDisplay()));

	//connect(garageTableWidget_, SIGNAL(dataChanged()),
	//	this, SLOT(updateDisplay()));
	//connect(warehouseTableWidget_, SIGNAL(dataChanged()),
	//	this, SLOT(updateDisplay()));

	//// In route to change building's type by button's text
	//connect(ui->pushButton_Build_CoalMine, SIGNAL(sendPointer(MyPushButton*)),
	//	this, SLOT(changeType(MyPushButton*)));
	//connect(ui->pushButton_Build_BaseCommerce, SIGNAL(sendPointer(MyPushButton*)),
	//	this, SLOT(changeType(MyPushButton*)));
	//connect(ui->pushButton_Build_IronMine, SIGNAL(sendPointer(MyPushButton*)),
	//	this, SLOT(changeType(MyPushButton*)));
	//connect(ui->pushButton_Build_residence, SIGNAL(sendPointer(MyPushButton*)),
	//	this, SLOT(changeType(MyPushButton*)));
	//connect(ui->pushButton_Build_SteelBaseIndustry, SIGNAL(sendPointer(MyPushButton*)),
	//	this, SLOT(changeType(MyPushButton*)));

	connect(ui->buyPushButton, SIGNAL(sendPointer(MyPushButton*)),
		this, SLOT(receiveOrder(MyPushButton*)));
	connect(ui->sellPushButton, SIGNAL(sendPointer(MyPushButton*)),
		this, SLOT(receiveOrder(MyPushButton*)));
	connect(ui->dismantlePushButton, SIGNAL(sendPointer(MyPushButton*)),
		this, SLOT(receiveOrder(MyPushButton*)));
}

BuildingDetailDialog::~BuildingDetailDialog() {
    delete ui;
}

void BuildingDetailDialog::changeType(MyPushButton *button) {
	const QString &newType = button->text();
	emit changeTypeSignal(building_, newType);
}

void BuildingDetailDialog::updateDisplay() {
	// Returns if this window isn't showing.
    if (this->isHidden() || !building_)	return;

	hideVariableWidget();

	displayBasicInfo();

	displayAccordingToVisitor();
}

//void BuildingDetailDialog::deliverGoods(const Goods &goods, BaseIndustry *dest) {
//	BaseIndustry *industry = dynamic_cast<BaseIndustry *>(building_);
//	industry->deliverGoods(goods, dest);
//	emit dataChanged();
//}

void BuildingDetailDialog::hideVariableWidget() {
	//ui->pushButton_Build->hide();
	//ui->pushButton_Build_IronMine->hide();
	//ui->pushButton_Build_CoalMine->hide();
	//ui->pushButton_Build_SteelBaseIndustry->hide();
	//ui->pushButton_Build_BaseCommerce->hide();
	//ui->pushButton_Build_residence->hide();
	//ui->buyPushButton->hide();
	//ui->dismantlePushButton->hide();
	//ui->sellPushButton->hide();
	//garageTableWidget_->hide();
	//warehouseTableWidget_->hide();
	//ui->warehouseSumLabel->hide();
}

void BuildingDetailDialog::displayBasicInfo() {
	const QString &name = building_->name();
	const QString &value = toString(building_->value());
	const QString &type = building_->type();
	const QString &owner = building_->owner()->name();
	const QString &position = building_->position().toString();
	setWindowTitle(name);
	ui->label_Name->setText(tr("Name:  ") + name);
	ui->label_Value->setText(tr("Value: $") + value);
	ui->label_Type->setText(tr("Type:  ") + type);
	ui->label_Owner->setText(tr("Owner: ") + owner);
	ui->label_Position->setText(tr("Position: ") + position);
}

void BuildingDetailDialog::displayAccordingToVisitor() {
	bool isVisitorOwner = (building_->owner() == CompanyManager::instance().playerCompany());
	if (isVisitorOwner == false) {
		ui->buyPushButton->show();
		return;
	}
	ui->sellPushButton->show();

	const QString &type = building_->type();
	int indexOfPage = BuildingManager::stringToEnum(type);
	ui->detailStackedWidget->setCurrentIndex(indexOfPage);
}

//void BuildingDetailDialog::typeIsFoundation() {
//	ui->pushButton_Build->show();
//	ui->detailStackedWidget->setCurrentIndex(BuildingManager::UnusedLand);
//}
//
//void BuildingDetailDialog::typeIsIndustry() {
//	BaseIndustry *industry = dynamic_cast<BaseIndustry *>(building_);
//	warehouseTableWidget_->setWarehouse(industry->warehouse());
//
//	showWarehouse(industry);
//	//showGarage(industry);
//
//	ui->detailStackedWidget->setCurrentIndex(BuildingManager::Factory);
//	ui->pushButton_Dismantle->show();
//}
//
//void BuildingDetailDialog::typeIsCommerce() {
//	ui->pushButton_Dismantle->show();
//}
//
//void BuildingDetailDialog::typeIsResidence() {
//	ui->pushButton_Dismantle->show();
//}

//void BuildingDetailDialog::showGarage(BaseIndustry *industry) {
//	const QString &freeVicleCount = QString::number(industry->garage()->freeVihicleCount());
//	const QString &vihicleCount = QString::number(industry->garage()->vihicleCount());
//	const QString &text = freeVicleCount + " / " + vihicleCount + tr(" Truck Free");
//	ui->label_GarageState->setText(text);
//
//	garageTableWidget_->show();
//	ui->label_GarageState->show();
//	garageTableWidget_->updateDisplay();
//}

//void BuildingDetailDialog::showWarehouse(BaseIndustry *industry) {
//	const QString &curVolume = toString(industry->warehouse()->curVolume());
//	const QString &maxVolume = toString(industry->warehouse()->maxVolume());
//	ui->warehouseSumLabel->setText(curVolume + "t / " + maxVolume + "t");
//
//	warehouseTableWidget_->show();
//	ui->warehouseSumLabel->show();
//	warehouseTableWidget_->updateDisplay();
//}

//void BuildingDetailDialog::addNewVihicle() {
//	BaseIndustry *industry = dynamic_cast<BaseIndustry *>(building_);
//	Company *owner = industry->owner();
//	owner->purchase(50);
//	industry->garage()->addNewVihicle("Truck");
//	emit dataChanged();
//}

void BuildingDetailDialog::receiveOrder(MyPushButton *button) {
	emit sendOption(button->text(), building_);
}

QString BuildingDetailDialog::toString(double value) {
	return QString::number(value, 10, 2);
}
