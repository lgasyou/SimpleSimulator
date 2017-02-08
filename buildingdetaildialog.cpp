#include "buildingdetaildialog.h"
#include "basebuilding.h"
#include "baseindustry.h"
#include "warehouse.h"
#include "goodscontainer.h"
#include "company.h"
#include "garage.h"
#include "goods.h"

#include "garagetablewidget.h"
#include "warehousetablewidget.h"
#include "mypushbutton.h"
#include "ui_buildingdetaildialog.h"

BuildingDetailDialog::BuildingDetailDialog(QWidget *parent) :
    QDialog(parent),
    building_(nullptr),
    visitor_(nullptr),
	garageTableWidget_(new GarageTableWidget(this)),
	warehouseTableWidget_(new WarehouseTableWidget(this)),
    ui(new Ui::BuildingDetailDialog)
{
    ui->setupUi(this);
	ui->verticalLayout_ProperitiesOfBaseIndustry->addWidget(warehouseTableWidget_);
	ui->verticalLayout_ProperitiesOfBaseIndustry->addWidget(garageTableWidget_);

	connect(ui->pushButton_BaseIndustry_SwitchInfo, SIGNAL(toggled(bool)),
		this, SLOT(switchBaseIndustryDisplay(bool)));

	connect(this, SIGNAL(dataChanged()),
		warehouseTableWidget_, SLOT(updateDisplay()));
	connect(this, SIGNAL(dataChanged()),
		garageTableWidget_, SLOT(updateDisplay()));

	// In order to change building's type by button's text
	connect(ui->pushButton_Build_CoalMine, SIGNAL(sendPointer(MyPushButton*)),
		this, SLOT(changeType(MyPushButton*)));
	connect(ui->pushButton_Build_BaseCommerce, SIGNAL(sendPointer(MyPushButton*)),
		this, SLOT(changeType(MyPushButton*)));
	connect(ui->pushButton_Build_IronMine, SIGNAL(sendPointer(MyPushButton*)),
		this, SLOT(changeType(MyPushButton*)));
	connect(ui->pushButton_Build_residence, SIGNAL(sendPointer(MyPushButton*)),
		this, SLOT(changeType(MyPushButton*)));
	connect(ui->pushButton_Build_SteelBaseIndustry, SIGNAL(sendPointer(MyPushButton*)),
		this, SLOT(changeType(MyPushButton*)));

	connect(warehouseTableWidget_, SIGNAL(sendPreorder(const Goods &, BaseIndustry*)),
		this, SLOT(deliverGoods(const Goods &, BaseIndustry*)));
}

BuildingDetailDialog::~BuildingDetailDialog() {
    delete ui;
}

void BuildingDetailDialog::updateDisplay() {
	// Return if this window isn't showing.
    if (this->isHidden())	return;

	hideVariableWidget();

	displayBasicInfo();

	displayAccordingToVisitor();
}

void BuildingDetailDialog::switchBaseIndustryDisplay(bool toggled) {
	QString text;
	BaseIndustry *industry = dynamic_cast<BaseIndustry *>(building_);
	if (toggled) {
		showWarehouse(industry);
		text = tr("Warehouse");
	} else {
		showGarage(industry);
		text = tr("Garage");
	}
	ui->pushButton_BaseIndustry_SwitchInfo->setText(text);
}

void BuildingDetailDialog::changeType(MyPushButton *button) {
	const QString &newType = button->text();
	emit changeTypeSignal(building_, newType);
}

void BuildingDetailDialog::deliverGoods(const Goods &goods, BaseIndustry *dest) {
	BaseIndustry *industry = dynamic_cast<BaseIndustry *>(building_);
	industry->deliverGoods(goods, dest);
	emit dataChanged();
}

void BuildingDetailDialog::hideVariableWidget() {
	ui->pushButton_Build->hide();
	ui->pushButton_Build_IronMine->hide();
	ui->pushButton_Build_CoalMine->hide();
	ui->pushButton_Build_SteelBaseIndustry->hide();
	ui->pushButton_Build_BaseCommerce->hide();
	ui->pushButton_Build_residence->hide();
	ui->pushButton_Buy->hide();
	ui->pushButton_Dismantle->hide();
	ui->pushButton_BaseIndustry_SwitchInfo->hide();
	ui->pushButton_Sell->hide();
	garageTableWidget_->hide();
	ui->label_GarageState->hide();
	warehouseTableWidget_->hide();
	ui->label_WarehouseSum->hide();
}

void BuildingDetailDialog::displayBasicInfo() {
	const QString &name = building_->name();
	const QString &value = toString(building_->value());
	const QString &type = building_->type();
	const QString &owner = building_->owner() ? building_->owner()->name() : tr("Government");
	const QString &pos = building_->pos().toString();
	setWindowTitle(name);
	ui->label_Name->setText(tr("Name:  ") + name);
	ui->label_Value->setText(tr("Value: $") + value);
	ui->label_Type->setText(tr("Type:  ") + type);
	ui->label_Owner->setText(tr("Owner: ") + owner);
	ui->label_Position->setText(tr("Position: ") + pos);
}

void BuildingDetailDialog::displayAccordingToVisitor() {
	bool isVisitorOwner = (building_->owner() == visitor_);
	if (isVisitorOwner == false) {
		ui->pushButton_Buy->show();
		return;
	}
	ui->pushButton_Sell->show();

	const QString &type = building_->type();
	if (type == "Foundation")
		typeIsFoundation();
	else if (type.contains("Factory") || type.contains("Mine"))
		typeIsBaseIndustry();
	else if (type.contains("BaseCommerce"))
		typeIsBaseCommerce();
	else
		typeIsBaseResidence();
}

void BuildingDetailDialog::typeIsFoundation() {
	ui->pushButton_Build->show();
}

void BuildingDetailDialog::typeIsBaseIndustry() {
	BaseIndustry *industry = dynamic_cast<BaseIndustry *>(building_);
	warehouseTableWidget_->setWarehouse(industry->warehouse());
	garageTableWidget_->setGarage(industry->garage());

	if (ui->pushButton_BaseIndustry_SwitchInfo->isChecked())
		showWarehouse(industry);
	else
		showGarage(industry);

	ui->pushButton_Dismantle->show();
	ui->pushButton_BaseIndustry_SwitchInfo->show();
}

void BuildingDetailDialog::typeIsBaseCommerce() {
	ui->pushButton_Dismantle->show();
}

void BuildingDetailDialog::typeIsBaseResidence() {
	ui->pushButton_Dismantle->show();
}

void BuildingDetailDialog::showGarage(BaseIndustry *industry) {
	const QString &freeVicleCount = QString::number(industry->garage()->freeVihicleCount());
	const QString &vihicleCount = QString::number(industry->garage()->vihicleCount());
	const QString &text = freeVicleCount + " / " + vihicleCount + tr(" Truck Free");
	ui->label_GarageState->setText(text);

	garageTableWidget_->show();
	ui->label_GarageState->show();
	garageTableWidget_->updateDisplay();
	warehouseTableWidget_->hide();
	ui->label_WarehouseSum->hide();
}

void BuildingDetailDialog::showWarehouse(BaseIndustry *industry) {
	const QString &curVolume = toString(industry->warehouse()->curVolume());
	const QString &maxVolume = toString(industry->warehouse()->maxVolume());
	ui->label_WarehouseSum->setText(curVolume + "t / " + maxVolume + "t");

	warehouseTableWidget_->show();
	ui->label_WarehouseSum->show();
	warehouseTableWidget_->updateDisplay();
	garageTableWidget_->hide();
	ui->label_GarageState->hide();
}

void BuildingDetailDialog::on_pushButton_Buy_clicked() {
    emit buySignal(building_);
}

void BuildingDetailDialog::on_pushButton_Sell_clicked() {
    emit sellSignal(building_);
}

void BuildingDetailDialog::on_pushButton_Build_clicked() {
	ui->pushButton_Build_IronMine->show();
	ui->pushButton_Build_CoalMine->show();
	ui->pushButton_Build_SteelBaseIndustry->show();
	ui->pushButton_Build_BaseCommerce->show();
    ui->pushButton_Build_residence->show();
}

void BuildingDetailDialog::on_pushButton_Dismantle_clicked() {
    emit changeTypeSignal(building_, "Foundation");
}

QString BuildingDetailDialog::toString(double value) {
	return QString::number(value, 10, 2);
}
