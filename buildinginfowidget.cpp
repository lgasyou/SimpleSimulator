#include "buildinginfowidget.h"
#include "ui_buildinginfowidget.h"
#include "basebuilding.h"
#include "company.h"
#include "companymanager.h"
#include "uimanager.h"

#include "buildingdetaildialog.h"
#include "mypushbutton.h"

#include <QString>

BuildingInfoWidget::BuildingInfoWidget(QWidget *parent) : QWidget(parent) {
	displayedBuilding_ = nullptr;
	detailWidget_ = nullptr;
	ui = new Ui::BuildingInfoWidget;
	ui->setupUi(this); 

	ui->buyOrSellpushButton->hide();
	ui->detailsPushButton->hide();

	connect(ui->detailsPushButton,		SIGNAL(clicked()),
			this,						SLOT(showBuildingDetail()));
	connect(ui->buyOrSellpushButton,	SIGNAL(sendPointer(MyPushButton*)),
			this,						SLOT(receiveOrder(MyPushButton*)));
}

BuildingInfoWidget::~BuildingInfoWidget() {
	delete ui;
}

void BuildingInfoWidget::setTarget(BaseBuilding *building) {
	this->displayedBuilding_ = building;
	if (detailWidget_)
		detailWidget_->setBuilding(building);
}

void BuildingInfoWidget::receiveOrder(MyPushButton *button) {
	emit sendOption(button->text(), displayedBuilding_);
}


void BuildingInfoWidget::showBuildingDetail() {
	if (displayedBuilding_ != nullptr) {
		detailWidget_ = UIManager::instance().buildingDetailDialog();
		detailWidget_->setBuilding(displayedBuilding_);

		detailWidget_->showAndRaise();
		detailWidget_->updateDisplay();
	}
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
		ui->buyOrSellpushButton->setText(buttonText);
	}
}