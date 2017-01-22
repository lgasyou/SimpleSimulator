#include "BuildingDetailDialog.h"
#include "BaseBuilding.h"
#include "Factory.h"
#include "FactoryCargo.h"
#include "Company.h"
#include "FactoryCargoTableWidget.h"
#include "ui_BuildingDetailDialog.h"

BuildingDetailDialog::BuildingDetailDialog(QWidget *parent) :
    QDialog(parent),
    building_(nullptr),
    visitor_(nullptr),
	factoryCargoTableWidget(new FactoryCargoTableWidget(this)),
    ui(new Ui::BuildingDetailDialog)
{
    ui->setupUi(this);
	ui->verticalLayout_Cargo->addWidget(factoryCargoTableWidget);

    connect(this, SIGNAL(buySignal(BaseBuilding*)),
            parent, SLOT(buy(BaseBuilding*)));
    connect(this, SIGNAL(sellSignal(BaseBuilding*)),
            parent, SLOT(sell(BaseBuilding*)));
    connect(this, SIGNAL(changeTypeSignal(BaseBuilding*,QString)),
            parent, SLOT(changeType(BaseBuilding*,QString)));
    connect(this, SIGNAL(manageSignal(BaseBuilding*,QString)),
            parent, SLOT(manage(BaseBuilding*,QString)));

    connect(parent, SIGNAL(dataChanged(bool)),
            this, SLOT(updateDisplay()));

    factoryCargoTableWidget->hide();
	ui->label_CargoSum->hide();
}

BuildingDetailDialog::~BuildingDetailDialog() {
    delete ui;
}

void BuildingDetailDialog::updateDisplay() {
    if (this->isHidden())
        return;

    ui->pushButton_Build_IronMine->hide();
	ui->pushButton_Build_CoalMine->hide();
	ui->pushButton_Build_SteelFactory->hide();
    ui->pushButton_Build_residence->hide();
	factoryCargoTableWidget->hide();
	ui->label_CargoSum->hide();

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
			Factory *factory = dynamic_cast<Factory *>(building_);
			ui->label_CargoSum->setText(toString(factory->cargo()->curVolume()) + "t / " + toString(factory->cargo()->maxVolume()) + "t");
			factoryCargoTableWidget->setCargo(factory->cargo());
			factoryCargoTableWidget->updateDisplay();

			factoryCargoTableWidget->show();
			ui->label_CargoSum->show();
		} else {
			factoryCargoTableWidget->hide();
			ui->label_CargoSum->hide();
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
	ui->pushButton_Build_SteelFactory->show();
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

void BuildingDetailDialog::on_pushButton_Build_SteelFactory_clicked() {
	emit changeTypeSignal(building_, "Steel Factory");
}

void BuildingDetailDialog::on_pushButton_Build_residence_clicked() {
    emit changeTypeSignal(building_, "Residence");
}

QString BuildingDetailDialog::toString(double value) {
	return QString::number(value, 10, 2);
}
