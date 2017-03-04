#include "setroutedialog.h"
#include "ui_setroutedialog.h"

#include "baseindustry.h"
#include "route.h"

#include <QLabel>
#include <QString>
#include "selecttablewidget.h"

SetRouteDialog::SetRouteDialog(QWidget *parent) :
	QDialog(parent),
	route_(nullptr),
	selectOrigTableWidget_(new SelectTableWidget),
	selectDestTableWidget_(new SelectTableWidget),
	ui(new Ui::SetRouteDialog)
{
	ui->setupUi(this); 
	setWindowTitle("Set Route");

	selectOrigTableWidget_->setParent(this);
	selectOrigTableWidget_->setSelector(SelectTableWidget::Mine | SelectTableWidget::Factory);
	connect(selectOrigTableWidget_, SIGNAL(sendBuilding(BaseBuilding*)),
			this,					SLOT(getOrig(BaseBuilding*)));

	selectDestTableWidget_->setParent(this);
	selectDestTableWidget_->setSelector(SelectTableWidget::Mine | SelectTableWidget::Factory);
	connect(selectDestTableWidget_, SIGNAL(sendBuilding(BaseBuilding*)),
			this,					SLOT(getDest(BaseBuilding*)));

	ui->layout->addWidget(ui->labelOrig);
	ui->layout->addWidget(selectOrigTableWidget_);
	ui->layout->addWidget(ui->labelDest);
	ui->layout->addWidget(selectDestTableWidget_);

	ui->labelGoodsName->setText(tr("Please select origin."));

	connect(ui->pushButton,			SIGNAL(clicked()),
			this,					SLOT(finishSetting()));

	connect(this,					SIGNAL(dataChanged()),
			this,					SLOT(updateDisplay()));

	route_ = new Route(Goods("", 0.0), nullptr, nullptr, false);
}

SetRouteDialog::~SetRouteDialog() {
	delete route_;
	delete ui;
}

void SetRouteDialog::createNewRoute() {
	if(route_->orig && route_->dest)
		route_ = new Route(Goods("", 0.0), nullptr, nullptr, false);
}

void SetRouteDialog::updateDisplay() {
	if (route_->orig && route_->orig->products().size()) {
		const QString &goodsName = route_->orig->products()[0].name;
		ui->labelGoodsName->setText(goodsName);
	}
	const QString &originName = route_->orig ? route_->orig->name() : "";
	ui->labelOrig->setText(tr("Origin:		") + originName);

	selectOrigTableWidget_->updateDisplay();

	const QString &destName = route_->dest ? route_->dest->name() : "";
	ui->labelDest->setText(tr("Destination:	") + destName);

	selectDestTableWidget_->updateDisplay();

	bool finishedSetting = (route_->orig && route_->dest);
	ui->pushButton->setEnabled(finishedSetting);
}

void SetRouteDialog::getGoodsName(const QString &goodsName) {
	route_->goods.name = goodsName;
	emit dataChanged();
}

void SetRouteDialog::getGoodsVolume(double eachVolume) {
	route_->goods.volume = eachVolume;
	emit dataChanged();
}

void SetRouteDialog::getOrig(BaseBuilding *origin) {
	route_->orig = (BaseIndustry *)origin;
	emit dataChanged();
}

void SetRouteDialog::getDest(BaseBuilding *dest) {
	route_->dest = (BaseIndustry *)dest;
	emit dataChanged();
}

void SetRouteDialog::finishSetting() {
	if (ui->checkBox->isChecked())
		route_->repeated = true;
	route_->goods.name = ui->labelGoodsName->text();
	route_->goods.volume = ui->spinBoxEachVolume->value();

	ui->checkBox->setChecked(false);
	emit sendRoute(route_);
	accept();
}
