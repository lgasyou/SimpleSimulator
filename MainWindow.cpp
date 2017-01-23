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
    buildingManager(new BuildingManager),
    company(new Company),
    bankDialog(nullptr),
    buildingDetailDialog(nullptr),
    buildingInfoTableWidget(new BuildingInfoTableWidget(this)),
    companyDetailDialog(nullptr),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->BuildingInfoTableWidget->addWidget(buildingInfoTableWidget);
    setWindowTitle(tr("Building Value Simulator"));

    buildingInfoTableWidget->setBuildingManager(buildingManager);
    buildingInfoTableWidget->setCompany(company);

    connect(ui->pushButton_EndTurn, SIGNAL(clicked(bool)),
            this, SLOT(endTurns()));
    connect(ui->pushButton_Bank, SIGNAL(clicked(bool)),
            this, SLOT(goBank()));
    connect(ui->pushButton_Company, SIGNAL(clicked(bool)),
            this, SLOT(showCompanyDetail()));

    connect(buildingInfoTableWidget, SIGNAL(buySignal(BuildingBase*)),
            this, SLOT(buy(BuildingBase*)));
    connect(buildingInfoTableWidget, SIGNAL(sellSignal(BuildingBase*)),
            this, SLOT(sell(BuildingBase*)));
    connect(buildingInfoTableWidget, SIGNAL(showDetailSignal(BuildingBase*)),
            this, SLOT(showBuildingDetail(BuildingBase*)));

    connect(this, SIGNAL(dataChanged(bool)),
            this, SLOT(updateDisplay()));

    updateDisplay();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::goBank() {
    if (!bankDialog)
        bankDialog = new BankDialog(company, this);
    bankDialog->updateDisplay();
    if (bankDialog->exec() == QDialog::Accepted) {
        updateStatusBar("Back.");
        emit dataChanged(true);
    }
}

void MainWindow::endTurns() {
    buildingManager->update();
    company->update();
    GameTimer::increaseTime();
    emit dataChanged(true);
}

void MainWindow::showBuildingDetail(BuildingBase *building) {
    if (!buildingDetailDialog)
        buildingDetailDialog = new BuildingDetailDialog(this);
    buildingDetailDialog->setBuilding(building);
    buildingDetailDialog->setVisitor(company);
    buildingDetailDialog->show();
    buildingDetailDialog->raise();
    buildingDetailDialog->activateWindow();
    buildingDetailDialog->updateDisplay();
}

void MainWindow::showCompanyDetail() {
    if (!companyDetailDialog)
        companyDetailDialog = new CompanyDetailDialog(this);
    companyDetailDialog->setCompany(company);
    companyDetailDialog->show();
    companyDetailDialog->raise();
    companyDetailDialog->activateWindow();
    companyDetailDialog->updateDisplay();
}

void MainWindow::buy(BuildingBase *building) {
    if (company->buy(building)) {
        emit dataChanged(true);
        updateStatusBar(building->type()+ " " + building->name() + " bought.");
    } else
        updateStatusBar("Cannot Afford it.");
}

void MainWindow::sell(BuildingBase *building) {
    if (company->sell(building)) {
        emit dataChanged(true);
        updateStatusBar(building->type()+ " " + building->name() + " sold.");
    }
}

void MainWindow::changeType(BuildingBase *building, const QString &type) {
	BuildingBase *newBuilding = buildingManager->setItemType(building, type);
    buildingDetailDialog->setBuilding(newBuilding);
    updateStatusBar(newBuilding->name() + " has been changed into " + type + ".");
    emit dataChanged(true);
}

void MainWindow::manage(BuildingBase *building, const QString &cmd) {
    buildingManager->manage(building, cmd);
    emit dataChanged(true);
}

void MainWindow::updateDisplay() {
    updateCompanyInfo();
    buildingInfoTableWidget->updateDisplay();
}

void MainWindow::updateCompanyInfo() {
    ui->label_CompanyName->setText(company->name());
    QString cash = toString(company->cash());
    ui->label_CompanyCash->setText(tr("Cash: $") + cash);
    QString totalValue = toString(company->totalValue());
    ui->label_CompanyTotalValue->setText(tr("Total Value: $") + totalValue);
    ui->label_Turns->setText(tr("Turn ") + QString::number(GameTimer::currentTime()));
}

inline void MainWindow::updateStatusBar(const QString &msg) {
    ui->statusBar->showMessage(msg);
}

QString MainWindow::toString(double value) {
	return QString::number(value, 10, 2);
}
