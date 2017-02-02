#include "CompanyDetailDialog.h"
#include "Company.h"
#include "ui_CompanyDetailDialog.h"

CompanyDetailDialog::CompanyDetailDialog(QWidget *parent) :
    QDialog(parent),
    company_(nullptr),
    ui(new Ui::CompanyDetailDialog)
{
    ui->setupUi(this);

    connect(parent, SIGNAL(dataChanged(bool)),
            this, SLOT(updateDisplay()));
}

CompanyDetailDialog::~CompanyDetailDialog() {
    delete ui;
}

QString CompanyDetailDialog::toString(double value) {
	return QString::number(value, 10, 2);
}

void CompanyDetailDialog::updateDisplay() {
	// Return if this window isn't showing.
    if (this->isHidden())	return;

	const QString &name = company_->name();
	const QString &cash = toString(company_->cash());
	const QString &totalValue = toString(company_->totalValue());
	const QString &liability = toString(company_->liability());
    setWindowTitle(name);
    ui->label_Name->setText(tr("Name:        ") + name);
    ui->label_Cash->setText(tr("Cash:        $") + cash);
    ui->label_TotalValue->setText(tr("Total Value: $") + totalValue);
    ui->label_Liability->setText(tr("Liability:   $") + liability);
}
