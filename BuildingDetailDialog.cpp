#include "BuildingDetailDialog.h"
#include "BuildingBase.h"
#include "Industry.h"
#include "Warehouse.h"
#include "GoodsContainer.h"
#include "Company.h"
#include "GarageTableWidget.h"
#include "WarehouseTableWidget.h"
#include "ui_BuildingDetailDialog.h"

BuildingDetailDialog::BuildingDetailDialog(QWidget *parent) :
    QDialog(parent),
    building_(nullptr),
    visitor_(nullptr),
	garageTableWidget_(new GarageTableWidget(this)),
	warehouseTableWidget_(new WarehouseTableWidget(this)),
    ui(new Ui::BuildingDetailDialog)
{
    ui->setupUi(this);
	ui->verticalLayout_Warehouse->addWidget(warehouseTableWidget_);
	ui->verticalLayout_Garage->addWidget(garageTableWidget_);

    connect(this, SIGNAL(buySignal(BuildingBase*)),
            parent, SLOT(buy(BuildingBase*)));
    connect(this, SIGNAL(sellSignal(BuildingBase*)),
            parent, SLOT(sell(BuildingBase*)));
    connect(this, SIGNAL(changeTypeSignal(BuildingBase*,QString)),
            parent, SLOT(changeType(BuildingBase*,QString)));
    connect(this, SIGNAL(manageSignal(BuildingBase*,QString)),
            parent, SLOT(manage(BuildingBase*,QString)));

    connect(parent, SIGNAL(dataChanged(bool)),
            this, SLOT(updateDisplay()));
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

void BuildingDetailDialog::hideVariableWidget() {
	ui->pushButton_Build->hide();
	ui->pushButton_Build_IronMine->hide();
	ui->pushButton_Build_CoalMine->hide();
	ui->pushButton_Build_SteelIndustry->hide();
	ui->pushButton_Build_Commerce->hide();
	ui->pushButton_Build_residence->hide();
	ui->pushButton_Buy->hide();
	ui->pushButton_Dismantle->hide();
	ui->pushButton_Manage->hide();
	ui->pushButton_Sell->hide();
	garageTableWidget_->hide();
	warehouseTableWidget_->hide();
	ui->label_WarehouseSum->hide();
}

void BuildingDetailDialog::displayBasicInfo() {
	const QString &name = building_->name();
	const QString &value = toString(building_->value());
	const QString &type = building_->type();
	const QString &owner = building_->owner() ? building_->owner()->name() : tr("Government");
	setWindowTitle(name);
	ui->label_Name->setText(tr("Name:  ") + name);
	ui->label_Value->setText(tr("Value: $") + value);
	ui->label_Type->setText(tr("Type:  ") + type);
	ui->label_Owner->setText(tr("Owner: ") + owner);
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
	else if (type.contains("Factory"))
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
	Industry *industry = dynamic_cast<Industry *>(building_);
	garageTableWidget_->setGarage(industry->garage());
	garageTableWidget_->updateDisplay();

	const QString &curVolume = toString(industry->warehouse()->curVolume());
	const QString &maxVolume = toString(industry->warehouse()->maxVolume());
	ui->label_WarehouseSum->setText(curVolume + "t / " + maxVolume + "t");
	warehouseTableWidget_->setWarehouse(industry->warehouse());
	warehouseTableWidget_->updateDisplay();

	garageTableWidget_->show();
	warehouseTableWidget_->show();
	ui->label_WarehouseSum->show();
	ui->pushButton_Manage->show();
	ui->pushButton_Dismantle->show();
}

void BuildingDetailDialog::typeIsCommerce() {
	ui->pushButton_Manage->show();
	ui->pushButton_Dismantle->show();
}

void BuildingDetailDialog::typeIsResidence() {
	ui->pushButton_Manage->show();
	ui->pushButton_Dismantle->show();
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
	ui->pushButton_Build_SteelIndustry->show();
	ui->pushButton_Build_Commerce->show();
    ui->pushButton_Build_residence->show();
}

void BuildingDetailDialog::on_pushButton_Manage_clicked() {
    //emit manageSignal(building_, order);
}

void BuildingDetailDialog::on_pushButton_Dismantle_clicked() {
    emit changeTypeSignal(building_, "Foundation");
}

void BuildingDetailDialog::on_pushButton_Build_IronMine_clicked() {
    emit changeTypeSignal(building_, "Iron Mine Factory");
}

void BuildingDetailDialog::on_pushButton_Build_CoalMine_clicked() {
	emit changeTypeSignal(building_, "Coal Mine Factory");
}

void BuildingDetailDialog::on_pushButton_Build_SteelIndustry_clicked() {
	emit changeTypeSignal(building_, "Steel Factory");
}

void BuildingDetailDialog::on_pushButton_Build_Commerce_clicked() {
	emit changeTypeSignal(building_, "Commerce");
}

void BuildingDetailDialog::on_pushButton_Build_residence_clicked() {
    emit changeTypeSignal(building_, "Residence");
}

QString BuildingDetailDialog::toString(double value) {
	return QString::number(value, 10, 2);
}
