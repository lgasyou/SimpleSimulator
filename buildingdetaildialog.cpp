#include "buildingdetaildialog.h"
#include "basebuilding.h"
#include "baseindustry.h"
#include "goodscontainer.h"
#include "company.h"
#include "companymanager.h"
#include "buildingmanager.h"
#include "industrychainmanager.h"
#include "garage.h"
#include "goods.h"
#include "machine.h"

#include "garagetablewidget.h"
#include "warehousetablewidget.h"
#include "mypushbutton.h"
#include "ui_buildingdetaildialog.h"

BuildingDetailDialog::BuildingDetailDialog(QWidget *parent) :
	QDialog(parent),
    building_(nullptr),
	selectMachine_(nullptr),
    ui(new Ui::BuildingDetailDialog)
{
    ui->setupUi(this);

	signalSlotConfig();

	ui->expandStackedWidget->hide();
}

BuildingDetailDialog::~BuildingDetailDialog() {
    delete ui;
}

void BuildingDetailDialog::updateDisplay() {
	// Returns if this window isn't showing.
    if (this->isHidden() || !building_)	return;

	const QString &name = building_->name();
	const QString &value = toString(building_->value());
	const QString &type = building_->type();
	const QString &owner = building_->owner()->name();
	const QString &position = building_->position().toString();
	setWindowTitle(name);
	ui->nameLabel->setText(tr("Name:  ") + name);
	ui->valueLabel->setText(tr("Value: $") + value);
	ui->typeLabel->setText(tr("Type:  ") + type);
	ui->ownerLabel->setText(tr("Owner: ") + owner);
	ui->positionLabel->setText(tr("Position: ") + position);

	if (ui->machinePage->isVisible()) {
		updateMachineDetail(selectMachine_);
	}

	displayAccordingToVisitor();
}

void BuildingDetailDialog::closeEvent(QCloseEvent *) {
	ui->expandStackedWidget->hide();
}

//void BuildingDetailDialog::deliverGoods(const Goods &goods, BaseIndustry *dest) {
//	BaseIndustry *industry = dynamic_cast<BaseIndustry *>(building_);
//	industry->deliverGoods(goods, dest);
//	emit dataChanged();
//}

void BuildingDetailDialog::addNewMachine(MyPushButton *) {
	BaseIndustry *building = dynamic_cast<BaseIndustry *>(building_);
	std::vector<Goods> products{ Goods("Coal", 1), Goods("Iron", 2) };
	auto materials = IndustryChainManager::instance().precursors(products[0].name);
	MachineSettings settings = MachineSettings(5.0, building->warehouse(), products, materials);
	Machine *machine = new Machine(settings);
	building->addMachine(machine);
	emit dataChanged();
}

void BuildingDetailDialog::setNextMachineProduct(const QString &product) {
	selectMachine_->setCurrentProduct(product);
	emit dataChanged();
}

void BuildingDetailDialog::showMachineDetail(Machine *machine) {
	ui->expandStackedWidget->show();
	selectMachine_ = machine;

	for (const auto &product : machine->products()) {
		ui->selectNextProductComboBox->addItem(product.name);
	}

	updateMachineDetail(machine);
}

void BuildingDetailDialog::updateMachineDetail(Machine *machine) {
	const QString &machineCurrentProductivity = toString(machine->currentProductivity());
	ui->machineCurrentProductivity->setText("Current Productivity: " + machineCurrentProductivity);

	const QString &machineMaximumProductivity = toString(machine->maximalProductivity());
	ui->machineMaximumProductivity->setText("Maximum Productivity: " + machineMaximumProductivity);
}

void BuildingDetailDialog::receiveOrder(MyPushButton *button) {
	emit sendOption(button->text(), building_);
	emit dataChanged();
}

void BuildingDetailDialog::displayAccordingToVisitor() {
	bool isVisitorOwner = (building_->owner() == CompanyManager::instance().playerCompany());
	ui->basicOperationStackedWidget->setCurrentIndex(isVisitorOwner);

	const QString &type = building_->type();
	auto buildingType = BuildingManager::stringToEnum(type);
	ui->detailStackedWidget->setCurrentIndex(buildingType);
	switch (buildingType) {
	case BuildingManager::Bank:
		break;

	case BuildingManager::Factory:
		ui->factoryTableWidget->setIndustry(building_);
		ui->factoryTableWidget->updateDisplay();
		break;

	case BuildingManager::Farm:
		break;

	case BuildingManager::Garage: {
		Garage *garage = dynamic_cast<Garage *>(building_);
		const QString &freeVicleCount = QString::number(garage->freeVihicleCount());
		const QString &vihicleCount = QString::number(garage->vihicleCount());
		const QString &text = QString("%1 / %2 Truck Free").arg(freeVicleCount, vihicleCount);
		ui->garageStateLabel->setText(text);

		ui->garageTableWidget->setGarage(building_);
		ui->garageTableWidget->updateDisplay();
		break;
	}

	case BuildingManager::Mine:
		ui->mineTableWidget->setIndustry(building_);
		ui->mineTableWidget->updateDisplay();
		break;

	case BuildingManager::Supermarket:
		break;

	case BuildingManager::UnusedLand:
		break;

	case BuildingManager::Villa:
		break;

	default:
		break;
	}
}

void BuildingDetailDialog::signalSlotConfig() {
	/* ---------------------------------- Basic Config ---------------------------------------------- */
	connect(ui->buyPushButton,							SIGNAL(sendPointer(MyPushButton*)),
			this,										SLOT(receiveOrder(MyPushButton*)));
	connect(ui->sellPushButton,							SIGNAL(sendPointer(MyPushButton*)),
			this,										SLOT(receiveOrder(MyPushButton*)));
	connect(ui->dismantlePushButton,					SIGNAL(sendPointer(MyPushButton*)),
			this,										SLOT(receiveOrder(MyPushButton*)));
	/* ---------------------------------------------------------------------------------------------- */

	/* ---------------------------------- Garage Config --------------------------------------------- */
	connect(ui->purchaseNewVihiclePushButton,			SIGNAL(sendPointer(MyPushButton *)),
			this,										SLOT(addNewVihicle(MyPushButton *)));
	/* ---------------------------------------------------------------------------------------------- */

	/* --------------------------------- Industry Config -------------------------------------------- */
	connect(ui->purchaseNewMachineInFactoryPushButton,	SIGNAL(sendPointer(MyPushButton*)),
			this,										SLOT(addNewMachine(MyPushButton*)));
	connect(ui->purchaseNewMachineInMinePushButton,		SIGNAL(sendPointer(MyPushButton*)),
			this,										SLOT(addNewMachine(MyPushButton*)));

	connect(ui->factoryTableWidget,						SIGNAL(sendSelectedMachine(Machine *)),
			this,										SLOT(showMachineDetail(Machine *)));
	connect(ui->mineTableWidget,						SIGNAL(sendSelectedMachine(Machine *)),
			this,										SLOT(showMachineDetail(Machine *)));

	connect(ui->selectNextProductComboBox,				SIGNAL(currentIndexChanged(const QString &)),
			this,										SLOT(setNextMachineProduct(const QString &)));
	/* ---------------------------------------------------------------------------------------------- */

	/* -------------------------------- UnusedLand Config ------------------------------------------- */
	connect(ui->buildBankPushButton,					SIGNAL(sendPointer(MyPushButton*)),
			this,										SLOT(receiveOrder(MyPushButton*)));
	connect(ui->buildFactoryPushButton,					SIGNAL(sendPointer(MyPushButton*)),
			this,										SLOT(receiveOrder(MyPushButton*)));
	connect(ui->buildFarmPushButton,					SIGNAL(sendPointer(MyPushButton*)),
			this,										SLOT(receiveOrder(MyPushButton*)));
	connect(ui->buildGaragePushButton,					SIGNAL(sendPointer(MyPushButton*)),
			this,										SLOT(receiveOrder(MyPushButton*)));
	connect(ui->buildMinePushButton,					SIGNAL(sendPointer(MyPushButton*)),
			this,										SLOT(receiveOrder(MyPushButton*)));
	connect(ui->buildSupermarketPushButton,				SIGNAL(sendPointer(MyPushButton*)),
			this,										SLOT(receiveOrder(MyPushButton*)));
	connect(ui->buildVillaPushButton,					SIGNAL(sendPointer(MyPushButton*)),
			this,										SLOT(receiveOrder(MyPushButton*)));
	/* ---------------------------------------------------------------------------------------------- */

	/* ---------------------------------- Display Config -------------------------------------------- */
	connect(this,										SIGNAL(dataChanged()),
			this,										SLOT(updateDisplay()));
	connect(this,										SIGNAL(dataChanged()),
			ui->factoryTableWidget,						SLOT(updateDisplay()));
	connect(this,										SIGNAL(dataChanged()),
			ui->mineTableWidget,						SLOT(updateDisplay()));
	connect(this,										SIGNAL(dataChanged()),
			ui->garageTableWidget,						SLOT(updateDisplay()));
	/* ---------------------------------------------------------------------------------------------- */
}

void BuildingDetailDialog::addNewVihicle(MyPushButton *) {
	Garage *garage = dynamic_cast<Garage *>(building_);
	garage->addNewVihicle("Truck");
	emit dataChanged();
}

QString BuildingDetailDialog::toString(double value) {
	return QString::number(value, 10, 2);
}
