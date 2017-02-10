#include "setroutedialog.h"
#include "ui_setroutedialog.h"

#include "baseindustry.h"
#include "order.h"

#include <QLabel>
#include "selecttablewidget.h"

SetRouteDialog::SetRouteDialog(QWidget *parent) :
	QDialog(parent),
	order_(nullptr),
	selectOriginTableWidget_(new SelectTableWidget),
	selectDestTableWidget_(new SelectTableWidget),
	ui(new Ui::SetRouteDialog)
{
	ui->setupUi(this); 
	setWindowTitle("Set Route");

	QLabel *labelOrigin = new QLabel(tr("Origin:"));

	selectOriginTableWidget_->setParent(this);
	selectOriginTableWidget_->setSelector(SelectTableWidget::Mine | SelectTableWidget::Factory);
	selectOriginTableWidget_->updateDisplay();
	connect(selectOriginTableWidget_, SIGNAL(sendBuilding(BaseBuilding*)),
		this, SLOT(getOrigin(BaseBuilding*)));

	QLabel *labelDest = new QLabel(tr("Destination:"));

	selectDestTableWidget_->setParent(this);
	selectDestTableWidget_->setSelector(SelectTableWidget::Mine | SelectTableWidget::Factory);
	selectDestTableWidget_->updateDisplay();
	connect(selectDestTableWidget_, SIGNAL(sendBuilding(BaseBuilding*)),
		this, SLOT(getDest(BaseBuilding*)));

	ui->layout->addWidget(labelOrigin);
	ui->layout->addWidget(selectOriginTableWidget_);
	ui->layout->addWidget(labelDest);
	ui->layout->addWidget(selectDestTableWidget_);

	connect(ui->pushButton, SIGNAL(clicked()),
		this, SLOT(finishSetting()));

	order_ = new Order(Goods("", 0.0), nullptr, nullptr, false);
}

SetRouteDialog::~SetRouteDialog() {
	delete order_;
	delete ui;
}

void SetRouteDialog::updateDisplay() {
	selectOriginTableWidget_->updateDisplay();
}

void SetRouteDialog::getOrigin(BaseBuilding *origin) {
	order_->src = (BaseIndustry *)origin;
}

void SetRouteDialog::getDest(BaseBuilding *dest) {
	order_->dest = (BaseIndustry *)dest;
}

void SetRouteDialog::finishSetting() {
	if (order_->dest && order_->src) {
		if (ui->checkBox->isChecked())
			order_->repeated = true;
		emit sendOrder(order_);
		accept();
	}
}
