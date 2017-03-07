#include "mainwindow.h"

#include "government.h"

#include "buildingmanager.h"
#include "companymanager.h"
#include "industrychainmanager.h"
#include "mapmanager.h"
#include "pricemanager.h"
#include "timemanager.h"
#include "uimanager.h"
#include "gameconstants.h"

#include "basebuilding.h"
#include "company.h"

#include "bankdialog.h"
#include "buildinginfowidget.h"
#include "buildingtablewidget.h"
#include "buildingdetaildialog.h"
#include "companydetaildialog.h"
#include "helpdialog.h"
#include "mainui.h"
#include "tablewidgetpushbutton.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QStatusBar>
#include <QSplitter>
#include <QString>
#include <map>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	buildingDetailDialog_(nullptr),
	buildingInfoList_(new BuildingTableWidget),
	companyDetailDialog_(new CompanyDetailDialog),
	helpDialog_(new HelpDialog),
    ui(new Ui::MainWindow) {
	init();
}

MainWindow::~MainWindow() {
	delete buildingInfoList_;
	delete helpDialog_;
    delete ui;
}

void MainWindow::init() {
	MapManager::instance().init();
	BuildingManager::instance().init();
	CompanyManager::instance().init();
	IndustryChainManager::instance().init();
	PriceManager::instance().init();
	TimeManager::instance().init();

	ui->setupUi(this);
	ui->userInterface->init();

	playerCompany_ = CompanyManager::instance().playerCompany();

	buildingDetailDialog_ = UIManager::instance().buildingDetailDialog();

	signalSlotConfig();

	updateDisplay();
}

//void MainWindow::goBank() {
//	BankDialog *bankDialog_ = UIManager::instance().bankDialog();
//	bankDialog_->setClient(playerCompany_);
//    bankDialog_->updateDisplay();
//    if (bankDialog_->exec() == QDialog::Accepted) {
//        updateStatusBar("Back.");
//        emit dataChanged();
//    }
//}

void MainWindow::endTurns() {
	BuildingManager::instance().update();
	CompanyManager::instance().update();
	Government::instance().update();

    TimeManager::instance().increaseTime();
    emit dataChanged();
}

void MainWindow::showBuildingTableWidget() {
	buildingInfoList_->show();
}

void MainWindow::showHelp() {
	helpDialog_->show();
}

void MainWindow::showCompanyDetail() {
    companyDetailDialog_->setCompany(playerCompany_);
	companyDetailDialog_->showAndRaise();
    companyDetailDialog_->updateDisplay();
}

void MainWindow::getBuildingByPos(int x, int y) {
	BaseBuilding *building = BuildingManager::instance().getBuildingByPos(x, y);
	emit sendSelectedBuilding(building);
}

void MainWindow::updateDisplay() {
	const QString &turnText = tr("Turn ") + QString::number(TimeManager::instance().currentTime());
	ui->label_Turns->setText(turnText);
	const QString &cashText = tr("Cash: $") + toString(playerCompany_->cash());
	ui->label_CompanyCash->setText(cashText);

    buildingInfoList_->updateDisplay();
}

void MainWindow::processCommand(int command, BaseBuilding *building) {
	using namespace GameConstants;
	QString msg;
	switch (command) {
	case BuildBank: {
		BaseBuilding *newBuilding = BuildingManager::instance().resetItemType(building, "Bank");
		ui->buildingInfoWidget->setTarget(newBuilding);
		buildingDetailDialog_->setBuilding(newBuilding);
		emit dataChanged();
		break;
	}

	case BuildFactory: {
		BaseBuilding *newBuilding = BuildingManager::instance().resetItemType(building, "Factory");
		ui->buildingInfoWidget->setTarget(newBuilding);
		buildingDetailDialog_->setBuilding(newBuilding);
		emit dataChanged();
		break;
	}

	case BuildFarm: {
		BaseBuilding *newBuilding = BuildingManager::instance().resetItemType(building, "Farm");
		ui->buildingInfoWidget->setTarget(newBuilding);
		buildingDetailDialog_->setBuilding(newBuilding);
		emit dataChanged();
		break;
	}


	case BuildGarage: {
		BaseBuilding *newBuilding = BuildingManager::instance().resetItemType(building, "Garage");
		ui->buildingInfoWidget->setTarget(newBuilding);
		buildingDetailDialog_->setBuilding(newBuilding);
		emit dataChanged();
		break;
	}

	case BuildMine: {
		BaseBuilding *newBuilding = BuildingManager::instance().resetItemType(building, "Mine");
		ui->buildingInfoWidget->setTarget(newBuilding);
		buildingDetailDialog_->setBuilding(newBuilding);
		emit dataChanged();
		break;
	}

	case BuildSupermarket: {
		BaseBuilding *newBuilding = BuildingManager::instance().resetItemType(building, "Supermarket");
		ui->buildingInfoWidget->setTarget(newBuilding);
		buildingDetailDialog_->setBuilding(newBuilding);
		emit dataChanged();
		break;
	}

	case BuildVilla: {
		BaseBuilding *newBuilding = BuildingManager::instance().resetItemType(building, "Villa");
		ui->buildingInfoWidget->setTarget(newBuilding);
		buildingDetailDialog_->setBuilding(newBuilding);
		emit dataChanged();
		break;
	}

	case BuyBuilding:
		if (playerCompany_->buy(building)) {
			emit dataChanged();
			msg = QString("%1 %2 bought.").arg(building->type(), building->name());
		} else {
			msg = "Cannot Afford it.";
		}
		break;

	case CloseAnAccount:
		break;

	case Deposit:
		break;

	case DismantleBuilding: {
		BaseBuilding *newBuilding = BuildingManager::instance().resetItemType(building, "Unused Land");
		ui->buildingInfoWidget->setTarget(newBuilding);
		buildingDetailDialog_->setBuilding(newBuilding);
		msg = newBuilding->name() + " has been dismantled.";
		emit dataChanged();
		break;
	}

	case Loan:
		break;

	case OpenAnAccount:
		break;

	case Repay:
		break;

	case SellBuilding:
		playerCompany_->sell(building);
		emit dataChanged();
		msg = QString("%1 %2 sold.").arg(building->type(), building->name());
		break;

	case ShowDetail:
		buildingDetailDialog_->setBuilding(building);
		buildingDetailDialog_->showAndRaise();
		buildingDetailDialog_->updateDisplay();
		break;

	case Withdraw:
		break;

	default:
		break;
	}
	updateStatusBar(msg);
}

void MainWindow::updateStatusBar(const QString &msg) {
    ui->statusBar->showMessage(msg, 5000);
}

QString MainWindow::toString(double value) {
	return QString::number(value, 10, 2);
}

void MainWindow::signalSlotConfig() {
	/* ------------------------------ Main Functions Config ----------------------------------------- */
	connect(ui->buildingListPushButton, SIGNAL(clicked()),
			this,						SLOT(showBuildingTableWidget()));
	connect(ui->companyPushButton,		SIGNAL(clicked()),
			this,						SLOT(showCompanyDetail()));
	connect(ui->endTurnPushButton,		SIGNAL(clicked()),
			this,						SLOT(endTurns()));
	connect(ui->helpPushButton,			SIGNAL(clicked()),
			this,						SLOT(showHelp()));
	/* ---------------------------------------------------------------------------------------------- */

	/* ---------------------------------- Orders Config --------------------------------------------- */
	connect(ui->buildingInfoWidget,		SIGNAL(sendCommand(int, BaseBuilding *)),
			this,						SLOT(processCommand(int, BaseBuilding *)));
	connect(buildingInfoList_,			SIGNAL(sendCommand(int, BaseBuilding *)),
			this,						SLOT(processCommand(int, BaseBuilding *)));
	connect(buildingDetailDialog_,		SIGNAL(sendCommand(int, BaseBuilding *)),
			this,						SLOT(processCommand(int, BaseBuilding *)));
	/* ---------------------------------------------------------------------------------------------- */

	/* ---------------------------------- Display Config -------------------------------------------- */
	connect(ui->userInterface,			SIGNAL(sendPosition(int, int)),	
			this,						SLOT(getBuildingByPos(int, int)));
	connect(this,						SIGNAL(sendSelectedBuilding(BaseBuilding *)),
			ui->buildingInfoWidget,		SLOT(showBuildingInfo(BaseBuilding *)));
	/* ---------------------------------------------------------------------------------------------- */

	/* ------------------------------- Update Display Config ---------------------------------------- */
	connect(this,						SIGNAL(dataChanged()),
			this,						SLOT(updateDisplay()));
	connect(this,						SIGNAL(dataChanged()),
			ui->buildingInfoWidget,		SLOT(updateDisplay()));
	connect(this,						SIGNAL(dataChanged()),
			buildingDetailDialog_,		SLOT(updateDisplay()));
	connect(this,						SIGNAL(dataChanged()),
			companyDetailDialog_,		SLOT(updateDisplay()));
	/* ---------------------------------------------------------------------------------------------- */
}
