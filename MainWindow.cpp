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

    connect(buildingInfoTableWidget, SIGNAL(buySignal(BaseBuilding*)),
            this, SLOT(buy(BaseBuilding*)));
    connect(buildingInfoTableWidget, SIGNAL(sellSignal(BaseBuilding*)),
            this, SLOT(sell(BaseBuilding*)));
    connect(buildingInfoTableWidget, SIGNAL(showDetailSignal(BaseBuilding*)),
            this, SLOT(showBuildingDetail(BaseBuilding*)));

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

void MainWindow::showBuildingDetail(BaseBuilding *building) {
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

void MainWindow::buy(BaseBuilding *building) {
    if (company->buy(building)) {
        emit dataChanged(true);
        updateStatusBar(building->type()+ " " + building->name() + " bought.");
    } else
        updateStatusBar("Cannot Afford it.");
}

void MainWindow::sell(BaseBuilding *building) {
    if (company->sell(building)) {
        emit dataChanged(true);
        updateStatusBar(building->type()+ " " + building->name() + " sold.");
    }
}

void MainWindow::changeType(BaseBuilding *building, const QString &type) {
    BaseBuilding *newBuilding = buildingManager->setItemType(building, type);
    buildingDetailDialog->setBuilding(newBuilding);
    updateStatusBar(newBuilding->name() + " has been changed into " + type + ".");
    emit dataChanged(true);
}

void MainWindow::manage(BaseBuilding *building, const QString &cmd) {
    buildingManager->manage(building, cmd);
    emit dataChanged(true);
}

void MainWindow::updateDisplay() {
    updateCompanyInfo();
    buildingInfoTableWidget->updateDisplay();
}

void MainWindow::updateCompanyInfo() {
    ui->label_CompanyName->setText(company->name());
    QString cash = QString::number(company->cash(), 10, 2);
    ui->label_CompanyCash->setText(tr("Cash: $") + cash);
    QString totalValue = QString::number(company->totalValue(), 10, 2);
    ui->label_CompanyTotalValue->setText(tr("Total Value: $") + totalValue);
    ui->label_Turns->setText(tr("Turn ") + QString::number(GameTimer::currentTime()));
}

inline void MainWindow::updateStatusBar(const QString &msg) {
    ui->statusBar->showMessage(msg);
}
