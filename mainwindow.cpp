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
	buildingDetailDialog_(new BuildingDetailDialog),
	buildingInfoList_(new BuildingInfoList),
	buildingInfoWidget_(new BuildingInfoWidget),
	helpDialog_(new HelpDialog),
	mainUi_(new MainUI),
    ui(new Ui::MainWindow)
{
	init();
}

MainWindow::~MainWindow() {
	delete buildingInfoList_;
	delete buildingInfoWidget_;
	delete helpDialog_;
	delete mainUi_;
    delete ui;
}

void MainWindow::init() {
	MapManager::instance().init();
	BuildingManager::instance().init();
	CompanyManager::instance().init();
	IndustryChainManager::instance().init();
	PriceManager::instance().init();
	TimeManager::instance().init();
	mainUi_->init();

	playerCompany_ = CompanyManager::instance().playerCompany();

	setWindowTitle(tr("Building Value Simulator"));

	ui->setupUi(this);

	ui->mainLayout->addWidget(mainUi_);
	ui->mainLayout->addWidget(buildingInfoWidget_);

	connect(mainUi_, SIGNAL(sendPosition(int, int)),
		this, SLOT(getBuildingByPos(int, int)));
	connect(this, SIGNAL(sendSelectedBuilding(BaseBuilding*)),
		buildingInfoWidget_, SLOT(showBuildingInfo(BaseBuilding*)));
	connect(buildingInfoWidget_, SIGNAL(sendOption(const QString &, BaseBuilding *)),
		this, SLOT(processOrders(const QString &, BaseBuilding *)));
	setupBuildingInfoList();

	connect(ui->bankPushButton, SIGNAL(clicked()),
		this, SLOT(goBank()));
	connect(ui->buildingListPushButton, SIGNAL(clicked()),
		this, SLOT(showBuildingInfoList()));
	connect(ui->companyPushButton, SIGNAL(clicked()),
		this, SLOT(showCompanyDetail()));
	connect(ui->pushButton_EndTurn, SIGNAL(clicked()),
		this, SLOT(endTurns()));
	connect(ui->helpPushButton, SIGNAL(clicked()),
		this, SLOT(showHelp()));

	connect(this, SIGNAL(dataChanged()),
		this, SLOT(updateDisplay()));
	connect(this, SIGNAL(dataChanged()),
		buildingInfoWidget_, SLOT(updateDisplay()));

	updateDisplay();
}

void MainWindow::goBank() {
	BankDialog *bankDialog_ = UIManager::instance().bankDialog();
	bankDialog_->setClient(playerCompany_);
    bankDialog_->updateDisplay();
    if (bankDialog_->exec() == QDialog::Accepted) {
        updateStatusBar("Back.");
        emit dataChanged();
    }
}

void MainWindow::endTurns() {
	BuildingManager::instance().update();
	CompanyManager::instance().update();
	Government::instance().update();

	double deltaValue = BuildingManager::instance().deltaValueOfCompanyProperties(playerCompany_);
	playerCompany_->setTotalValue(playerCompany_->totalValue() + deltaValue);
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
	CompanyDetailDialog *companyDetailDialog = UIManager::instance().companyDetailDialog();
	setupCompanyDetailDialog(companyDetailDialog);

    companyDetailDialog->setCompany(playerCompany_);
	companyDetailDialog->showAndRaise();
    companyDetailDialog->updateDisplay();
}

void MainWindow::getBuildingByPos(int x, int y) {
	BaseBuilding *building = BuildingManager::instance().getBuildingByPos(x, y);
	emit sendSelectedBuilding(building);
}

void MainWindow::changeType(BaseBuilding *building, const QString &type) {
	BaseBuilding *newBuilding = BuildingManager::instance().resetItemType(building, type);
	buildingInfoWidget_->setTarget(newBuilding);
    updateStatusBar(newBuilding->name() + " has been changed into " + type + ".");
    emit dataChanged();
}

void MainWindow::updateDisplay() {
    updateCompanyInfo();
    buildingInfoList_->updateDisplay();
}

void MainWindow::processOrders(const QString &order, BaseBuilding *building) {
	if (order == "Buy") {
		if (playerCompany_->buy(building)) {
			emit dataChanged();
			updateStatusBar(building->type()+ " " + building->name() + " bought.");
		} else
			updateStatusBar("Cannot Afford it.");
	} else if (order == "Sell") {
		if (playerCompany_->sell(building)) {
			emit dataChanged();
			updateStatusBar(building->type() + " " + building->name() + " sold.");
		}
	} else if (order == "Dismantle") {
		BuildingManager::instance().resetItemType(building, "Unused Land");
	} else if (order == "Details") {
		// TODO
	}
}

void MainWindow::updateCompanyInfo() {
    ui->label_Turns->setText(tr("Turn ") + QString::number(TimeManager::instance().currentTime()));
    const QString &cash = toString(playerCompany_->cash());
    ui->label_CompanyCash->setText(tr("Cash: $") + cash);
}

inline void MainWindow::updateStatusBar(const QString &msg) {
    ui->statusBar->showMessage(msg, 5000);
}

QString MainWindow::toString(double value) {
	return QString::number(value, 10, 2);
}

void MainWindow::setupBuildingInfoList() {
	connect(buildingInfoList_, SIGNAL(sendOption(const QString &, BaseBuilding *)),
		this, SLOT(processOrders(const QString &, BaseBuilding *)));
}

void MainWindow::setupCompanyDetailDialog(CompanyDetailDialog *companyDetailDialog) {
	static bool isTheFirstTimeCall = true;
	if (isTheFirstTimeCall == false)	return;

	companyDetailDialog->setParent(this, Qt::Window);

	connect(this, SIGNAL(dataChanged()),
		companyDetailDialog, SLOT(updateDisplay()));

	isTheFirstTimeCall = false;
}
