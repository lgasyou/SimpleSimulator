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

	QWidget *widget_warehouse = new QWidget;
	QVBoxLayout *layout_warehouse = new QVBoxLayout;
	layout_warehouse->addWidget(ui->label_WarehouseSum);
	layout_warehouse->addWidget(warehouseTableWidget_);
	widget_warehouse->setLayout(layout_warehouse);
	ui->tabWidget_industry->addTab(widget_warehouse, "Warehouse");

	QWidget *widget_garage = new QWidget;
	QGridLayout *layout_garage = new QGridLayout;
	layout_garage->addWidget(ui->label_GarageState, 0, 0);
	layout_garage->addWidget(ui->pushButtonAddVihicle, 0, 1);
	layout_garage->addWidget(garageTableWidget_, 1, 0);
	widget_garage->setLayout(layout_garage);
	ui->tabWidget_industry->addTab(widget_garage, "Garage");

	connect(this, SIGNAL(dataChanged()),
		warehouseTableWidget_, SLOT(updateDisplay()));
	connect(this, SIGNAL(dataChanged()),
		garageTableWidget_, SLOT(updateDisplay()));

	connect(garageTableWidget_, SIGNAL(dataChanged()),
		this, SLOT(updateDisplay()));
	connect(warehouseTableWidget_, SIGNAL(dataChanged()),
		this, SLOT(updateDisplay()));

	// In route to change building's type by button's text
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

	connect(warehouseTableWidget_, SIGNAL(sendPreroute(const Goods &, BaseIndustry*)),
		this, SLOT(deliverGoods(const Goods &, BaseIndustry*)));

	connect(ui->pushButtonAddVihicle, SIGNAL(clicked()),
		this, SLOT(addNewVihicle()));
}

BuildingDetailDialog::~BuildingDetailDialog() {
    delete ui;
}

void BuildingDetailDialog::updateDisplay() {
	// Returns if this window isn't showing.
    if (this->isHidden())	return;

	hideVariableWidget();

	displayBasicInfo();

	displayAccordingToVisitor();
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
	ui->pushButton_Sell->hide();
	ui->tabWidget_industry->hide();
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
	const QString &position = building_->position().toString();
	setWindowTitle(name);
	ui->label_Name->setText(tr("Name:  ") + name);
	ui->label_Value->setText(tr("Value: $") + value);
	ui->label_Type->setText(tr("Type:  ") + type);
	ui->label_Owner->setText(tr("Owner: ") + owner);
	ui->label_Position->setText(tr("Position: ") + position);
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
		typeIsIndustry();
	else if (type.contains("Commerce"))
		typeIsCommerce();
	else
		typeIsResidence();
}

void BuildingDetailDialog::typeIsFoundation() {
	ui->pushButton_Build->show();
}

void BuildingDetailDialog::typeIsIndustry() {
	BaseIndustry *industry = dynamic_cast<BaseIndustry *>(building_);
	warehouseTableWidget_->setWarehouse(industry->warehouse());
	garageTableWidget_->setGarage(industry->garage());

	showWarehouse(industry);
	showGarage(industry);

	ui->pushButton_Dismantle->show();
	ui->tabWidget_industry->show();
}

void BuildingDetailDialog::typeIsCommerce() {
	ui->pushButton_Dismantle->show();
}

void BuildingDetailDialog::typeIsResidence() {
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
}

void BuildingDetailDialog::showWarehouse(BaseIndustry *industry) {
	const QString &curVolume = toString(industry->warehouse()->curVolume());
	const QString &maxVolume = toString(industry->warehouse()->maxVolume());
	ui->label_WarehouseSum->setText(curVolume + "t / " + maxVolume + "t");

	warehouseTableWidget_->show();
	ui->label_WarehouseSum->show();
	warehouseTableWidget_->updateDisplay();
}

void BuildingDetailDialog::addNewVihicle() {
	BaseIndustry *industry = dynamic_cast<BaseIndustry *>(building_);
	industry->garage()->addNewVihicle("Truck");
	emit dataChanged();
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
