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
#include "mine.h"
#include "factory.h"
#include "gameconstants.h"

#include "garagetablewidget.h"
#include "warehousetablewidget.h"
#include "TableWidgetPushButton.h"
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

	displayAccordingToBuildingType();
}

void BuildingDetailDialog::closeEvent(QCloseEvent *) {
	ui->expandStackedWidget->hide();
}

//void BuildingDetailDialog::deliverGoods(const Goods &goods, BaseIndustry *dest) {
//	BaseIndustry *industry = dynamic_cast<BaseIndustry *>(building_);
//	industry->deliverGoods(goods, dest);
//	emit dataChanged();
//}

void BuildingDetailDialog::addNewMachine() {
	auto industryType = BuildingManager::stringToEnum(building_->type());
	switch (industryType) {
	case BuildingManager::Factory: {
		Factory *factory = dynamic_cast<Factory *>(building_);
		MachineSettings settings;
		settings.maximalProductivity = 1.0;
		settings.products = { Goods("Steel", 1) };
		settings.currentProduct = settings.products[0].name;
		settings.warehouse = factory->warehouse();

		Machine *machine = new Machine(settings);
		factory->addMachine(machine);
		emit dataChanged();
		break;
	}

	case BuildingManager::Mine: {
		Mine *mine = dynamic_cast<Mine *>(building_);
		MachineSettings settings;
		settings.maximalProductivity = 1.0;
		settings.products = { Goods(mine->resource(), 1) };
		settings.currentProduct = mine->resource();
		settings.warehouse = mine->warehouse();

		Machine *machine = new Machine(settings);
		mine->addMachine(machine);
		emit dataChanged();
		break;
	}

	default:
		break;
	}

}

void BuildingDetailDialog::addNewVihicle() {
	Garage *garage = dynamic_cast<Garage *>(building_);
	garage->addNewVihicle("Truck");
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

void BuildingDetailDialog::receiveCommand(int command) {
	emit sendCommand(command, building_);
	emit dataChanged();
}

void BuildingDetailDialog::displayAccordingToBuildingType() {
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

	case BuildingManager::Mine: {
		Mine *mine = dynamic_cast<Mine *>(building_);
		const QString &typeText = QString("Type:  %1 Mine").arg(mine->resource());
		ui->typeLabel->setText(typeText);

		ui->mineTableWidget->setIndustry(building_);
		ui->mineTableWidget->updateDisplay();
		break;
	}

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
	using namespace GameConstants;

	/* ---------------------------------- Basic Config ---------------------------------------------- */
	connect(ui->buyPushButton,							SIGNAL(sendCommand(int)),
			this,										SLOT(receiveCommand(int)));
	ui->buyPushButton->setCommand(Command::BuyBuilding);

	connect(ui->sellPushButton,							SIGNAL(sendCommand(int)),
			this,										SLOT(receiveCommand(int)));
	ui->sellPushButton->setCommand(Command::SellBuilding);

	connect(ui->dismantlePushButton,					SIGNAL(sendCommand(int)),
			this,										SLOT(receiveCommand(int)));
	ui->dismantlePushButton->setCommand(Command::DismantleBuilding);
	/* ---------------------------------------------------------------------------------------------- */

	/* ----------------------------------- Bank Config ---------------------------------------------- */
	connect(ui->closeAnAccountPushButton,				SIGNAL(sendCommand(int)),
			this,										SLOT(receiveCommand(int)));
	ui->closeAnAccountPushButton->setCommand(Command::CloseAnAccount);

	connect(ui->depositPushButton,						SIGNAL(sendCommand(int)),
			this,										SLOT(receiveCommand(int)));
	ui->depositPushButton->setCommand(Command::Deposit);

	connect(ui->loanPushButton,							SIGNAL(sendCommand(int)),
			this,										SLOT(receiveCommand(int)));
	ui->loanPushButton->setCommand(Command::Loan);

	connect(ui->openAnAccountPushButton,				SIGNAL(sendCommand(int)),
			this,										SLOT(receiveCommand(int)));
	ui->openAnAccountPushButton->setCommand(Command::OpenAnAccount);

	connect(ui->repayPushButton,						SIGNAL(sendCommand(int)),
			this,										SLOT(receiveCommand(int)));
	ui->repayPushButton->setCommand(Command::Repay);

	connect(ui->withdrawPushButton,						SIGNAL(sendCommand(int)),
			this,										SLOT(receiveCommand(int)));
	ui->withdrawPushButton->setCommand(Command::Withdraw);
	/* ---------------------------------------------------------------------------------------------- */

	/* ---------------------------------- Garage Config --------------------------------------------- */
	connect(ui->purchaseNewVihiclePushButton,			SIGNAL(clicked()),
			this,										SLOT(addNewVihicle()));
	/* ---------------------------------------------------------------------------------------------- */

	/* --------------------------------- Industry Config -------------------------------------------- */
	connect(ui->purchaseNewMachineInFactoryPushButton,	SIGNAL(clicked()),
			this,										SLOT(addNewMachine()));
	connect(ui->purchaseNewMachineInMinePushButton,		SIGNAL(clicked()),
			this,										SLOT(addNewMachine()));

	connect(ui->factoryTableWidget,						SIGNAL(sendSelectedMachine(Machine *)),
			this,										SLOT(showMachineDetail(Machine *)));
	connect(ui->mineTableWidget,						SIGNAL(sendSelectedMachine(Machine *)),
			this,										SLOT(showMachineDetail(Machine *)));

	connect(ui->selectNextProductComboBox,				SIGNAL(currentIndexChanged(const QString &)),
			this,										SLOT(setNextMachineProduct(const QString &)));
	/* ---------------------------------------------------------------------------------------------- */

	/* -------------------------------- UnusedLand Config ------------------------------------------- */
	connect(ui->buildBankPushButton,					SIGNAL(sendCommand(int)),
			this,										SLOT(receiveCommand(int)));
	ui->buildBankPushButton->setCommand(Command::BuildBank);

	connect(ui->buildFactoryPushButton,					SIGNAL(sendCommand(int)),
			this,										SLOT(receiveCommand(int)));
	ui->buildFactoryPushButton->setCommand(Command::BuildFactory);

	connect(ui->buildFarmPushButton,					SIGNAL(sendCommand(int)),
			this,										SLOT(receiveCommand(int)));
	ui->buildFarmPushButton->setCommand(Command::BuildFarm);

	connect(ui->buildGaragePushButton,					SIGNAL(sendCommand(int)),
			this,										SLOT(receiveCommand(int)));
	ui->buildGaragePushButton->setCommand(Command::BuildGarage);

	connect(ui->buildMinePushButton,					SIGNAL(sendCommand(int)),
			this,										SLOT(receiveCommand(int)));
	ui->buildMinePushButton->setCommand(Command::BuildMine);

	connect(ui->buildSupermarketPushButton,				SIGNAL(sendCommand(int)),
			this,										SLOT(receiveCommand(int)));
	ui->buildSupermarketPushButton->setCommand(Command::BuildSupermarket);

	connect(ui->buildVillaPushButton,					SIGNAL(sendCommand(int)),
			this,										SLOT(receiveCommand(int)));
	ui->buildVillaPushButton->setCommand(Command::BuildVilla);
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

QString BuildingDetailDialog::toString(double value) {
	return QString::number(value, 10, 2);
}
