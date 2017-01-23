#include "BuildingDetailDialog.h"
#include "BuildingBase.h"
#include "Industry.h"
#include "IndustryWarehouse.h"
#include "Company.h"
#include "IndustryWarehouseTableWidget.h"
#include "ui_BuildingDetailDialog.h"

BuildingDetailDialog::BuildingDetailDialog(QWidget *parent) :
    QDialog(parent),
    building_(nullptr),
    visitor_(nullptr),
	industryWarehouseTableWidget(new IndustryWarehouseTableWidget(this)),
    ui(new Ui::BuildingDetailDialog)
{
    ui->setupUi(this);
	ui->verticalLayout_Warehouse->addWidget(industryWarehouseTableWidget);

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

    industryWarehouseTableWidget->hide();
	ui->label_WarehouseSum->hide();
}

BuildingDetailDialog::~BuildingDetailDialog() {
    delete ui;
}

void BuildingDetailDialog::updateDisplay() {
    if (this->isHidden())
        return;

    ui->pushButton_Build_IronMine->hide();
	ui->pushButton_Build_CoalMine->hide();
	ui->pushButton_Build_SteelIndustry->hide();
	ui->pushButton_Build_Commerce->hide();
    ui->pushButton_Build_residence->hide();
	industryWarehouseTableWidget->hide();
	ui->label_WarehouseSum->hide();

    setWindowTitle(building_->name());
    ui->label_Name->setText(tr("Name:  ") + building_->name());
    ui->label_Value->setText(tr("Value: $") + toString(building_->value()));
    ui->label_Type->setText(tr("Type:  ") + building_->type());
    QString owner = building_->owner() ? building_->owner()->name() : tr("Government");
    ui->label_Owner->setText(tr("Owner: ") + owner);

    bool isVisitorOwner = (building_->owner() == visitor_);
    if (!isVisitorOwner) {
        ui->pushButton_Buy->show();
        ui->pushButton_Sell->hide();
        ui->pushButton_Manage->hide();
        ui->pushButton_Build->hide();
        ui->pushButton_Dismantle->hide();
        return;
    }

    ui->pushButton_Sell->show();
    ui->pushButton_Buy->hide();
    if (building_->type() == "Foundation") {
        ui->pushButton_Build->show();
        ui->pushButton_Manage->hide();
        ui->pushButton_Dismantle->hide();
    } else {
		if (building_->type().contains("Factory")) {
			Industry *industry = dynamic_cast<Industry *>(building_);
			ui->label_WarehouseSum->setText(toString(industry->warehouse()->curVolume()) + "t / " + toString(industry->warehouse()->maxVolume()) + "t");
			industryWarehouseTableWidget->setWarehouse(industry->warehouse());
			industryWarehouseTableWidget->updateDisplay();

			industryWarehouseTableWidget->show();
			ui->label_WarehouseSum->show();
		} else {
			industryWarehouseTableWidget->hide();
			ui->label_WarehouseSum->hide();
		}

        ui->pushButton_Build->hide();
        ui->pushButton_Manage->show();
        ui->pushButton_Dismantle->show();
    }
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
