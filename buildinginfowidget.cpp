#include "buildinginfowidget.h"
#include "ui_buildinginfowidget.h"
#include "basebuilding.h"
#include "company.h"
#include "companymanager.h"
#include "gameconstants.h"

#include "tablewidgetpushbutton.h"

#include <QString>

BuildingInfoWidget::BuildingInfoWidget(QWidget *parent) : QWidget(parent) {
	displayedBuilding_ = nullptr;
	ui = new Ui::BuildingInfoWidget;
	ui->setupUi(this); 

	connect(ui->detailsPushButton,		SIGNAL(sendCommand(int)),
			this,						SLOT(receiveCommand(int)));
	ui->detailsPushButton->setCommand(GameConstants::ShowDetail);
	ui->detailsPushButton->hide();

	connect(ui->buyOrSellpushButton,	SIGNAL(sendCommand(int)),
			this,						SLOT(receiveCommand(int)));
	ui->buyOrSellpushButton->hide();
}

BuildingInfoWidget::~BuildingInfoWidget() {
	delete ui;
}

void BuildingInfoWidget::setTarget(BaseBuilding *building) {
	this->displayedBuilding_ = building;
}

void BuildingInfoWidget::receiveCommand(int command) {
	emit sendCommand(command, displayedBuilding_);
}

void BuildingInfoWidget::showBuildingInfo(BaseBuilding *building) {
	if (building != displayedBuilding_) {
		setTarget(building);

		if (building) {
			updateDisplay();
		} else {
			ui->buildingNameLabel->clear();
			ui->buildingOwnerLabel->clear();
		}
		ui->buyOrSellpushButton->setVisible(building);
		ui->detailsPushButton->setVisible(building);
	}
}

void BuildingInfoWidget::updateDisplay() {
	if (displayedBuilding_) {
		const QString &name = displayedBuilding_->name();
		ui->buildingNameLabel->setText(name);
		const QString &owner = displayedBuilding_->owner()->name();
		ui->buildingOwnerLabel->setText("Owner:\n\n" + owner);

		bool owned = (displayedBuilding_->owner() == CompanyManager::instance().playerCompany());
		const QString buttonText = owned ? tr("Sell") : tr("Buy");
		ui->buyOrSellpushButton->setCommand(owned ? GameConstants::SellBuilding : GameConstants::BuyBuilding);
		ui->buyOrSellpushButton->setText(buttonText);
	}
}