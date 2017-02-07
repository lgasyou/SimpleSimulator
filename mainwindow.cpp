#include "mainwindow.h"
#include "buildingmanager.h"
#include "companymanager.h"
#include "timemanager.h"
#include "uimanager.h"

#include "basebuilding.h"
#include "company.h"
#include "bankdialog.h"
#include "buildingdetaildialog.h"
#include "buildinginfotablewidget.h"
#include "companydetaildialog.h"

#include "mypushbutton.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    buildingInfoTableWidget_(new BuildingInfoTableWidget(this)),
    ui(new Ui::MainWindow)
{
	init();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::init() {
	ui->setupUi(this);
	ui->BuildingInfoTableWidget->addWidget(buildingInfoTableWidget_);
	setWindowTitle(tr("Building Value Simulator"));

	playerCompany_ = CompanyManager::instance().playerCompany();

	connect(ui->pushButton_EndTurn, SIGNAL(clicked(bool)),
		this, SLOT(endTurns()));
	connect(ui->pushButton_Bank, SIGNAL(clicked(bool)),
		this, SLOT(goBank()));
	connect(ui->pushButton_Company, SIGNAL(clicked(bool)),
		this, SLOT(showCompanyDetail()));

	setupBuildingInfoTableWidget();

	connect(this, SIGNAL(dataChanged()),
		this, SLOT(updateDisplay()));

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
	double deltaValue = BuildingManager::instance().deltaValueOfCompanyProperties(playerCompany_);
	playerCompany_->setTotalValue(playerCompany_->totalValue() + deltaValue);
    TimeManager::instance().increaseTime();
    emit dataChanged();
}

void MainWindow::showBuildingDetail(BaseBuilding *building) {
	BuildingDetailDialog *buildingDetailDialog = UIManager::instance().buildingDetailDialog();
	setupBuildingDetailDialog(buildingDetailDialog);

    buildingDetailDialog->setBuilding(building);
    buildingDetailDialog->setVisitor(playerCompany_);
	buildingDetailDialog->showAndRaise();
    buildingDetailDialog->updateDisplay();
}

void MainWindow::showCompanyDetail() {
	CompanyDetailDialog *companyDetailDialog = UIManager::instance().companyDetailDialog();
	setupCompanyDetailDialog(companyDetailDialog);

    companyDetailDialog->setCompany(playerCompany_);
	companyDetailDialog->showAndRaise();
    companyDetailDialog->updateDisplay();
}

void MainWindow::buy(BaseBuilding *building) {
    if (playerCompany_->buy(building)) {
        emit dataChanged();
        updateStatusBar(building->type()+ " " + building->name() + " bought.");
    } else
        updateStatusBar("Cannot Afford it.");
}

void MainWindow::sell(BaseBuilding *building) {
    if (playerCompany_->sell(building)) {
        emit dataChanged();
        updateStatusBar(building->type()+ " " + building->name() + " sold.");
    }
}

void MainWindow::changeType(BaseBuilding *building, const QString &type) {
	BaseBuilding *newBuilding = BuildingManager::instance().resetItemType(building, type);
    UIManager::instance().buildingDetailDialog()->setBuilding(newBuilding);
    updateStatusBar(newBuilding->name() + " has been changed into " + type + ".");
    emit dataChanged();
}

void MainWindow::updateDisplay() {
    updateCompanyInfo();
    buildingInfoTableWidget_->updateDisplay();
}

void MainWindow::updateCompanyInfo() {
    ui->label_CompanyName->setText(playerCompany_->name());
    QString cash = toString(playerCompany_->cash());
    ui->label_CompanyCash->setText(tr("Cash: $") + cash);
    QString totalValue = toString(playerCompany_->totalValue());
    ui->label_CompanyTotalValue->setText(tr("Total Value: $") + totalValue);
    ui->label_Turns->setText(tr("Turn ") + QString::number(TimeManager::instance().currentTime()));
}

inline void MainWindow::updateStatusBar(const QString &msg) {
    ui->statusBar->showMessage(msg, 5000);
}

QString MainWindow::toString(double value) {
	return QString::number(value, 10, 2);
}

void MainWindow::setupBuildingInfoTableWidget() {
	connect(buildingInfoTableWidget_, SIGNAL(buySignal(BaseBuilding*)),
		this, SLOT(buy(BaseBuilding*)));
	connect(buildingInfoTableWidget_, SIGNAL(sellSignal(BaseBuilding*)),
		this, SLOT(sell(BaseBuilding*)));
	connect(buildingInfoTableWidget_, SIGNAL(showDetailSignal(BaseBuilding*)),
		this, SLOT(showBuildingDetail(BaseBuilding*)));
}

void MainWindow::setupBuildingDetailDialog(BuildingDetailDialog *buildingDetailDialog) {
	static bool isFirstTimeCallThisFunction = true;
	if (isFirstTimeCallThisFunction == false)	return;

	connect(buildingDetailDialog, SIGNAL(buySignal(BaseBuilding*)),
		this, SLOT(buy(BaseBuilding*)));
	connect(buildingDetailDialog, SIGNAL(sellSignal(BaseBuilding*)),
		this, SLOT(sell(BaseBuilding*)));
	connect(buildingDetailDialog, SIGNAL(changeTypeSignal(BaseBuilding*, QString)),
		this, SLOT(changeType(BaseBuilding*, QString)));

	connect(this, SIGNAL(dataChanged()),
		buildingDetailDialog, SLOT(updateDisplay()));

	isFirstTimeCallThisFunction = false;
}

void MainWindow::setupCompanyDetailDialog(CompanyDetailDialog *companyDetailDialog) {
	static bool isFirstTimeCallThisFunction = true;
	if (isFirstTimeCallThisFunction == false)	return;

	connect(this, SIGNAL(dataChanged()),
		companyDetailDialog, SLOT(updateDisplay()));

	isFirstTimeCallThisFunction = false;
}
