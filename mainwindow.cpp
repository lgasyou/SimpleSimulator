#include "mainwindow.h"

#include "government.h"

#include "buildingmanager.h"
#include "companymanager.h"
#include "industrychainmanager.h"
#include "mapmanager.h"
#include "pricemanager.h"
#include "timemanager.h"
#include "uimanager.h"

#include "basebuilding.h"
#include "company.h"

#include "bankdialog.h"
#include "buildinginfowidget.h"
#include "buildinginfolist.h"
#include "buildingdetaildialog.h"
#include "companydetaildialog.h"
#include "helpdialog.h"
#include "mainui.h"
#include "mypushbutton.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QStatusBar>
#include <QSplitter>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	buildingDetailDialog_(nullptr),
	buildingInfoList_(new BuildingInfoList),
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

	QIcon icon = QIcon("Sources/MainIcon.png");
	setWindowIcon(icon);
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

void MainWindow::showBuildingInfoList() {
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

void MainWindow::changeType(BaseBuilding *building, const QString &type) {
	BaseBuilding *newBuilding = BuildingManager::instance().resetItemType(building, type);
	ui->buildingInfoWidget->setTarget(newBuilding);
    updateStatusBar(newBuilding->name() + " has been changed into " + type + ".");
    emit dataChanged();
}

void MainWindow::updateDisplay() {
	const QString &turnText = tr("Turn ") + QString::number(TimeManager::instance().currentTime());
	ui->label_Turns->setText(turnText);
	const QString &cashText = tr("Cash: $") + toString(playerCompany_->cash());
	ui->label_CompanyCash->setText(cashText);

    buildingInfoList_->updateDisplay();
}

void MainWindow::processOrders(const QString &order, BaseBuilding *building) {
	QString msg;
	if (order == "Buy") {
		if (playerCompany_->buy(building)) {
			emit dataChanged();
			msg = building->type() + " " + building->name() + " bought.";
			updateStatusBar(msg);
		} else
			msg = "Cannot Afford it.";
			updateStatusBar(msg);
	} else if (order == "Sell") {
		if (playerCompany_->sell(building)) {
			emit dataChanged();
			msg = building->type() + " " + building->name() + " sold.";
			updateStatusBar(msg);
		}
	} else if (order == "Dismantle") {
		BuildingManager::instance().resetItemType(building, "Unused Land");
	} else if (order == "Details") {
		buildingDetailDialog_ = UIManager::instance().buildingDetailDialog();
		buildingDetailDialog_->setBuilding(building);

		buildingDetailDialog_->showAndRaise();
		buildingDetailDialog_->updateDisplay();
	}
}

inline void MainWindow::updateStatusBar(const QString &msg) {
    ui->statusBar->showMessage(msg, 5000);
}

QString MainWindow::toString(double value) {
	return QString::number(value, 10, 2);
}

void MainWindow::signalSlotConfig() {
	// Main functions of MainWindow
	connect(ui->buildingListPushButton, SIGNAL(clicked()),
			this,						SLOT(showBuildingInfoList()));
	connect(ui->companyPushButton,		SIGNAL(clicked()),
			this,						SLOT(showCompanyDetail()));
	connect(ui->pushButton_EndTurn,		SIGNAL(clicked()),
			this,						SLOT(endTurns()));
	connect(ui->helpPushButton,			SIGNAL(clicked()),
			this,						SLOT(showHelp()));

	// Processes the order which comes from other dialogs.
	connect(ui->buildingInfoWidget,		SIGNAL(sendOption(const QString &, BaseBuilding *)),
			this,						SLOT(processOrders(const QString &, BaseBuilding *)));
	connect(buildingInfoList_,			SIGNAL(sendOption(const QString &, BaseBuilding *)),
			this,						SLOT(processOrders(const QString &, BaseBuilding *)));
	connect(buildingDetailDialog_,		SIGNAL(sendOption(const QString &, BaseBuilding *)),
			this,						SLOT(processOrders(const QString &, BaseBuilding *)));

	// Configurates display.
	connect(ui->userInterface,			SIGNAL(sendPosition(int, int)),	
			this,						SLOT(getBuildingByPos(int, int)));
	connect(this,						SIGNAL(sendSelectedBuilding(BaseBuilding*)),
			ui->buildingInfoWidget,		SLOT(showBuildingInfo(BaseBuilding*)));

	// Updates display if it's neccessary.
	connect(this,						SIGNAL(dataChanged()),
			this,						SLOT(updateDisplay()));
	connect(this,						SIGNAL(dataChanged()),
			ui->buildingInfoWidget,		SLOT(updateDisplay()));
	connect(this,						SIGNAL(dataChanged()),
			buildingDetailDialog_,		SLOT(updateDisplay()));
	connect(this,						SIGNAL(dataChanged()),
			companyDetailDialog_,		SLOT(updateDisplay()));
}
