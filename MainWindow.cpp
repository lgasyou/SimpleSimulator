#include "MainWindow.h"
#include "BuildingManager.h"
#include "Company.h"
#include "GameTimer.h"
#include "BankDialog.h"
#include "BuildingDetailDialog.h"
#include "BuildingInfoTableWidget.h"
#include "CompanyDetailDialog.h"
#include "MyPushButton.h"
#include "ui_MainWindow.h"
#include <QTableWidget>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    company_(new Company),
    bankDialog_(nullptr),
    buildingDetailDialog_(nullptr),
    buildingInfoTableWidget_(new BuildingInfoTableWidget(this)),
    companyDetailDialog_(nullptr),
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

	buildingInfoTableWidget_->setCompany(company_);

	connect(ui->pushButton_EndTurn, SIGNAL(clicked(bool)),
		this, SLOT(endTurns()));
	connect(ui->pushButton_Bank, SIGNAL(clicked(bool)),
		this, SLOT(goBank()));
	connect(ui->pushButton_Company, SIGNAL(clicked(bool)),
		this, SLOT(showCompanyDetail()));

	connect(buildingInfoTableWidget_, SIGNAL(buySignal(BuildingBase*)),
		this, SLOT(buy(BuildingBase*)));
	connect(buildingInfoTableWidget_, SIGNAL(sellSignal(BuildingBase*)),
		this, SLOT(sell(BuildingBase*)));
	connect(buildingInfoTableWidget_, SIGNAL(showDetailSignal(BuildingBase*)),
		this, SLOT(showBuildingDetail(BuildingBase*)));

	connect(this, SIGNAL(dataChanged()),
		this, SLOT(updateDisplay()));

	updateDisplay();
}

void MainWindow::goBank() {
    if (!bankDialog_)
        bankDialog_ = new BankDialog(company_, this);
    bankDialog_->updateDisplay();
    if (bankDialog_->exec() == QDialog::Accepted) {
        updateStatusBar("Back.");
        emit dataChanged();
    }
}

void MainWindow::endTurns() {
	BuildingManager::instance().update();
    company_->update();
	double deltaValue = BuildingManager::instance().deltaValueOfCompanyProperties(company_);
	company_->setTotalValue(company_->totalValue() + deltaValue);
    GameTimer::instance().increaseTime();
    emit dataChanged();
}

void MainWindow::showBuildingDetail(BuildingBase *building) {
    if (!buildingDetailDialog_)
        buildingDetailDialog_ = new BuildingDetailDialog(this);
    buildingDetailDialog_->setBuilding(building);
    buildingDetailDialog_->setVisitor(company_);
	showDialog(buildingDetailDialog_);
    buildingDetailDialog_->updateDisplay();
}

void MainWindow::showCompanyDetail() {
    if (!companyDetailDialog_)
        companyDetailDialog_ = new CompanyDetailDialog(this);
    companyDetailDialog_->setCompany(company_);
	showDialog(companyDetailDialog_);
    companyDetailDialog_->updateDisplay();
}

void MainWindow::buy(BuildingBase *building) {
    if (company_->buy(building)) {
        emit dataChanged();
        updateStatusBar(building->type()+ " " + building->name() + " bought.");
    } else
        updateStatusBar("Cannot Afford it.");
}

void MainWindow::sell(BuildingBase *building) {
    if (company_->sell(building)) {
        emit dataChanged();
        updateStatusBar(building->type()+ " " + building->name() + " sold.");
    }
}

void MainWindow::changeType(BuildingBase *building, const QString &type) {
	BuildingBase *newBuilding = BuildingManager::instance().resetItemType(building, type);
    buildingDetailDialog_->setBuilding(newBuilding);
    updateStatusBar(newBuilding->name() + " has been changed into " + type + ".");
    emit dataChanged();
}

void MainWindow::manage(BuildingBase *building, const QString &cmd) {
    BuildingManager::instance().manage(building, cmd);
    emit dataChanged();
}

void MainWindow::updateDisplay() {
    updateCompanyInfo();
    buildingInfoTableWidget_->updateDisplay();
}

void MainWindow::updateCompanyInfo() {
    ui->label_CompanyName->setText(company_->name());
    QString cash = toString(company_->cash());
    ui->label_CompanyCash->setText(tr("Cash: $") + cash);
    QString totalValue = toString(company_->totalValue());
    ui->label_CompanyTotalValue->setText(tr("Total Value: $") + totalValue);
    ui->label_Turns->setText(tr("Turn ") + QString::number(GameTimer::instance().currentTime()));
}

inline void MainWindow::updateStatusBar(const QString &msg) {
    ui->statusBar->showMessage(msg, 5000);
}

QString MainWindow::toString(double value) {
	return QString::number(value, 10, 2);
}

void MainWindow::showDialog(QDialog *dialog) {
	dialog->show();
	dialog->raise();
	dialog->activateWindow();
}
